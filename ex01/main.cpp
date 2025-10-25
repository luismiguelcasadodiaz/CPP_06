#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <sstream>
#include <bitset>

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
		std::cout << std::endl << "Network programming (byte order conversion)" << std::endl;
		// Receive 4 bytes from network
		char buffer[4] = {0x12, 0x34, 0x56, 0x78};

		std::cout << std::endl << "char buffer[4] = {0x12, 0x34, 0x56, 0x78}; " << std::endl;
		// Interpret as 32-bit integer
		uint32_t* value = reinterpret_cast<uint32_t*>(&buffer);
		std::cout << std::hex << *value << std::endl;  // 0x78563412 (little-endian)
		std::cout << std::dec ;
	}
	{
		std::cout << std::endl << "Reading raw bytes of any object" << std::endl;
		struct Data_ {
			int x;
			float y;
		};

		Data_ d = {42, 3.14f};

		std::cout << "Original x=" << d.x << ", Original y=" << d.y << std::endl; 
		uint32_t bits = *reinterpret_cast<uint32_t *>(&d.y) ;
		std::cout << "Original x=" << std::bitset<32>(d.x) << ", Original y=" << std::bitset<32>(bits) << std::endl; 
		std::cout << "Original x=       .       .       .        , Original y=       .       .       ." <<  std::endl; 
		// Treat the object as raw bytes
		unsigned char* bytes = reinterpret_cast<unsigned char*>(&d);

		// Now you can save/send these bytes over network, to file, etc.
		for (size_t i = 0; i < sizeof(Data_); i++) {
			std::cout << std::dec << (int)bytes[i] << " ";
		}
		std::cout << std::endl;
		// Simulate bytes travelling in the network as a stream
		unsigned char received[sizeof(bytes)];
		for (size_t i = 0; i < sizeof(Data_); i++) {
			received[i] = bytes[i];
		}
		Data_ * r = reinterpret_cast<Data_ *>(&received) ;
		std::cout << "Received x=" << r->x << ", Received  y=" << r->y << std::endl; 

	}
	return 0;
}
