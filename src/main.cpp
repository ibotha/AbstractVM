#include "Parser.hpp"
#include <iostream>
#include <fstream>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		Parser p;
		p.Run();
	}
	else
	{
		std::ifstream s(av[1]);
		if (!s)
		{
			std::cout << "Invalid Filename" << std::endl;
			return 0;
		}
		Parser p(s);
		p.Run();
	}
}