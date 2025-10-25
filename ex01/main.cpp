#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <sstream>

int main ( void )
{
	{
		Data * lmcd = new Data;
		Data * dser ;
		uintptr_t raw ;
		lmcd->nom = "Luis Miguel";
		lmcd->ape = "Casado Diaz";
		lmcd->age = 59 ;

		raw = Serializer::serialize( lmcd ) ;
		dser = Serializer::deserialize( raw ) ;
		std::cout << "Nom >" << dser->nom << std::endl;
		std::cout << "Ape >" << dser->ape << std::endl;
		std::cout << "Age >" << dser->age << std::endl;
		delete lmcd;
	}
	{
		std::cout << "Network programming (byte order conversion)" << std::endl;
		// Receive 4 bytes from network
		char buffer[4] = {0x12, 0x34, 0x56, 0x78};

		// Interpret as 32-bit integer
		uint32_t* value = reinterpret_cast<uint32_t*>(buffer);
		std::cout << std::hex << *value << std::endl;  // 0x78563412 (little-endian)
	}
	{
		std::cout << "Reading raw bytes of any object" << std::endl;
		struct Data_ {
			int x;
			float y;
		};

		Data_ d = {42, 3.14f};

		// Treat the object as raw bytes
		unsigned char* bytes = reinterpret_cast<unsigned char*>(&d);

		// Now you can save/send these bytes over network, to file, etc.
		for (size_t i = 0; i < sizeof(Data_); i++) {
			std::cout << std::hex << (int)bytes[i] << " ";
		}
		std::cout << std::endl;
		// Simulate bytes travelling in the network as a stream
		std::stringstream ss;
		for (size_t i = 0; i < sizeof(Data_); i++) {
			ss << bytes[i];
		}
		std::cout << ss.str();
		//const unsigned char * received = static_cast<const unsigned char *>(ss.str().c_str());
		Data_ r = reinterpret_cast<Data_>(ss.str().c_str()) ;
		std::cout << "x=" << r.x << ", y=" << r.y << std::endl; 

	}
	return 0;
}
