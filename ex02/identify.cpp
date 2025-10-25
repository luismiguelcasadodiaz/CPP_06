#include "identify.hpp"
#include <cstdlib>
#include <iostream>
#include <exception>

Base * generate ( void )
{
	int rnd_0_2 = std::rand() % 3 ;

	if (rnd_0_2 == 0)
	{
		std::cout << "Class generated is A" << std::endl;
		return new A();
	} else if ( rnd_0_2 == 1 )
	{
		std::cout << "Class generated is B" << std::endl;
		return new B();
	} else {
		std::cout << "Class generated is C" << std::endl;
		return new C();
	}
}
void identify (Base * p)
{
	A * obj_a = dynamic_cast<A *>(p);
	if (obj_a != NULL)
	{
		std::cout << "A" << std::endl;
		return ;
	}
	B * obj_b = dynamic_cast<B *>(p);
	if (obj_b != NULL)
	{
		std::cout << "B" << std::endl;
		return ;
	}
	C * obj_c = dynamic_cast<C *>(p);
	if (obj_c != NULL)
	{
		std::cout << "C" << std::endl;
		return ;
	}
}

void identify (Base & p)
{
	try
	{
		A & obj_a = dynamic_cast<A &>(p);
		(void)obj_a;
		std::cout << "A" << std::endl;
		return ;
	} catch (std::exception &bc) {}
	try
	{
		B & obj_b = dynamic_cast<B &>(p);
		(void)obj_b;
		std::cout << "B" << std::endl;
		return ;
	} catch (std::exception &bc) {}
	try
	{
		C & obj_c = dynamic_cast<C &>(p);
		(void)obj_c;
		std::cout << "C" << std::endl;
		return ;
	} catch (std::exception &bc) {}
}
