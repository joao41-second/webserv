#include "../include/config/Config.hpp"
#include "../include/config/ServerConfig.hpp"
#include "../include/config/LocationConfig.hpp"
#include "../include/net/Socket.hpp"

static void	print_methods_loc(LocationConfig const location)
{
	const std::string method_name[] = 
	{
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"OPTIONS",
		"PATCH",
		"TRACE",
		"CONNECT"
	};

	unsigned int method_num = sizeof(method_name) / sizeof(method_name[0]);
	for (unsigned int i = 0; i < method_num ; i++)
	{
		if (location.hasMethod(static_cast<t_methods>(i)))
		{
			std::cout << method_name[i] << ' ';
		}
	}
	std::cout << '$' << std::endl;
}

static void	print_methods_serv(ServerConfig const serv)
{
	const std::string method_name[] = 
	{
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"OPTIONS",
		"PATCH",
		"TRACE",
		"CONNECT"
	};

	unsigned int method_num = sizeof(method_name) / sizeof(method_name[0]);
	for (unsigned int i = 0; i < method_num ; i++)
	{
		if (serv.hasMethod(static_cast<t_methods>(i)))
		{
			std::cout << method_name[i] << ' ';
		}
	}
	std::cout << '$' << std::endl;
}

int	main(int argc, char **argv, char **envp)
{
try
{
	if (argc != 2)
	{
		throw InputException("The program should use the template './webserv [configuration file]'");
	}

	Config test(argv[1], envp);

	int a = 10;
	std::stringstream ss;
	ss << a;
	std::string str = ss.str();
	for (unsigned int i = 8000; i < test.getServNum() + 8000; i++)
	{
		std::cout << "Server " << (i - 8000) << ":" << std::endl;
		std::cout << "\tName: " << test.getServerConfig(static_cast<uint16_t>(i)).getName() << "$" << std::endl;
		std::cout << "\tPort: " << test.getServerConfig(static_cast<uint16_t>(i)).getPort() << "$" << std::endl;
		std::cout << "\tInterface: " << test.getServerConfig(static_cast<uint16_t>(i)).getInterface() << "$" << std::endl;
		std::cout << "\tRoot: " << test.getServerConfig(static_cast<uint16_t>(i)).getRoot() << "$" << std::endl;
		std::cout << "\tIndex: " << test.getServerConfig(static_cast<uint16_t>(i)).getIndex() << "$" << std::endl;
		std::cout << "\tMethods: ";
		print_methods_serv(test.getServerConfig(static_cast<uint16_t>(i)));
		std::cout << "\tSocket (fd): " << test.getSocketVector()[i - 8000]->getFd() << "$" << std::endl;
		std::cout << "\tSocket (addr): " << std::endl;
		std::cout << "\t\taddr Family: " << test.getSocketVector()[i - 8000]->getAddr().sin_family << "$" << std::endl;
		std::cout << "\t\taddr Address: " << inet_ntoa(test.getSocketVector()[i - 8000]->getAddr().sin_addr) << "$" << std::endl;
		// Note: inet_ntoa() is likely not allowed!
		std::cout << "\t\taddr Port: " << test.getSocketVector()[i - 8000]->getAddrPort() << "$" << std::endl;
		std::cout << "\tClient max body size: " << test.getServerConfig(static_cast<uint16_t>(i)).getClientMaxSize() << "$" << std::endl;
		for (unsigned int j = 400; j < 403; j++)
		{
			std::cout << "\tError page " << j << ": " << test.getServerConfig(static_cast<uint16_t>(i)).getErrorPage(j) << "$" << std::endl;
		}
		std::cout << std::endl;
		for (unsigned int j = 0; j < test.getServerConfig(static_cast<uint16_t>(i)).getLocNum(); j++)
		{
			std::cout << "\tLocation " << j << ":" << std::endl;
			std::cout << "\t\tName: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getName() << "$" << std::endl;
			std::cout << "\t\tRoot: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getRoot() << "$" << std::endl;
			std::cout << "\t\tIndex: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getIndex() << "$" << std::endl;
			std::cout << "\t\tCGI Pass: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getPass() << "$" << std::endl;
			std::cout << "\t\tClient body buffer size: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getClientBuffSize() << "$" << std::endl;
			std::cout << "\t\tAlias: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getAlias() << "$" << std::endl;
			std::cout << "\t\tMethods: ";
			print_methods_loc(test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j));

			for (unsigned int k = 0; k < test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocationMap().size(); k++)
			{
				std::cout << "\n\t\tSub-Location:" << std::endl;
				std::cout << "\t\t\tName: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k).getName() << "$" << std::endl;
				std::cout << "\t\t\tRoot: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k).getRoot() << "$" << std::endl;
				std::cout << "\t\t\tIndex: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k).getIndex() << "$" << std::endl;
				std::cout << "\t\t\tCGI Pass: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k).getPass() << "$" << std::endl;
				std::cout << "\t\t\tClient body buffer size: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k).getClientBuffSize() << "$" << std::endl;
				std::cout << "\t\t\tAlias: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k).getAlias() << "$" << std::endl;
				std::cout << "\t\t\tMethods: ";
				print_methods_loc(test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation(k));
			}
			std::cout << std::endl;
		}
	}
}
catch (std::exception &e)
{
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
	return 0;
}


