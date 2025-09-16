//#include "./include/*.hpp" TODO header names
#include "./include/*.hpp"

int	main(int argc, char **argv)
{
try TODO write exception
{
	if (argc != 2)
	{
		throw InputException("The program should use the template './webserv [configuration file]'");
	}
}
catch (std::exception &e)
{
	std::cerr << "Error" << e.what() << std::endl;
	return 1;
}
	return 0;
}


