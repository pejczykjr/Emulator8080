#include<iostream>
#include "registers.h"

int main() {
	using namespace RegistersNamespace;

	Registers test;

	test.setAllFlags(0b00010101);

	std::cout << test.getReg<Reg::A>() << std::endl;
	std::cout << test.getFlag<Flag::AC>() << std::endl;

	return 0;
}