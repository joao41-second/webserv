//#include "./include/*.hpp" TODO header names

int	main(int argc, char **argv)
{
//try TODO write exception
//{
	if (argc != 2)
	{
		std::cout << "The program should use the template './webserv [configuration file]'";
		return 1;
	}
//}
/*catch (std::exception &e)
{
	std::cerr << "Error" << e.what() << std::endl;
}*/
	return 0;
}


