//#include "./_config_include/*.hpp" TODO header names
#include "../_config_include/config.hpp"
#include "../_config_include/serverconfig.hpp"
#include "../_config_include/locationconfig.hpp"

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

int	main(int argc, char **argv)
{
try // TODO write general exceptions?
{
	if (argc != 2)
	{
		throw InputException("The program should use the template './webserv [configuration file]'");
	}

	Config test(argv[1]);

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

			if (test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).checkSubLocation())
			{
				std::cout << "\n\t\tSub-Location:" << std::endl;
				std::cout << "\t\t\tName: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation().getName() << "$" << std::endl;
				std::cout << "\t\t\tRoot: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation().getRoot() << "$" << std::endl;
				std::cout << "\t\t\tIndex: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation().getIndex() << "$" << std::endl;
				std::cout << "\t\t\tCGI Pass: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation().getPass() << "$" << std::endl;
				std::cout << "\t\t\tClient body buffer size: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation().getClientBuffSize() << "$" << std::endl;
				std::cout << "\t\t\tAlias: " << test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation().getAlias() << "$" << std::endl;
				std::cout << "\t\t\tMethods: ";
				print_methods_loc(test.getServerConfig(static_cast<uint16_t>(i)).getLocationConfig(j).getSubLocation());
			}
			std::cout << std::endl;
		}
	}

	// Create a socket: int socket(int domain, int type, int protocol);
	// AF_INET → IPv4 (addresses like 192.168.1.10)
	// SOCK_STREAM → TCP (reliable, connection-oriented byte stream)
	/*int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		throw InputException("Could not create socket");
	}*/

	
	/*pollfd	serverFD;

	serverFD.fd = socket(AF_INET, SOCK_STREAM, 0); // TODO meter dentro de um simples int

	if ( serverFD.fd < 0 )
		throw std::runtime_error( "Error creating socket." );
	
	// F_GETFL → get socket's status flags
	int curr_flags = fcntl(sock, F_GETFL, 0); // int fcntl(int fd, int cmd, ... (arg) );
	if (curr_flags == -1)
	{
		throw std::runtime_error("Could not get socket's flags");
	}
	// F_SETFL → set socket's status flags ; O_NONBLOCK → Set socket's flag to non-blocking
	if (fcntl(serverFD.fd, F_SETFL, curr_flags | O_NONBLOCK) == -1) // Getting current flags ensures that nothing is overwritten
	{
		throw fcntlError("Could not set socket to non-blocking");
	}*/
	

	// Listen to port 8000 on any address
	/*sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(test.getServerConfig(8000).getPort()); // TODO Which server gets priority?

	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		throw InputException("Failed to bind to the port");
	}

	// Start listening. Hold at most 10 connections in the queue
	if (listen(sockfd, 10) < 0)
	{
		throw InputException("Failed to listen on socket");
	}*/

	// Close the connections
	//close(connection);
	//close(sockfd);
}
catch (std::exception &e)
{
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
	return 0;
}


