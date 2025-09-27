//#include "./include/*.hpp" TODO header names
#include "../include/config.hpp"
#include "../include/server.hpp"
#include "../include/location.hpp"

int	main(int argc, char **argv)
{
try // TODO write general exceptions?
{
	if (argc != 2)
	{
		throw InputException("The program should use the template './webserv [configuration file]'");
	}

	Config test(argv[1]);
	for (unsigned int i = 0; i < test.getServNum(); i++)
	{
		std::cout << "Server " << i << ":" << std::endl;
		std::cout << "\tName: " << test.getServer(i).getName() << std::endl;
		std::cout << "\tPort: " << test.getServer(i).getPort() << std::endl;
		std::cout << "\tInterface: " << test.getServer(i).getInterface() << std::endl;
		std::cout << "\tRoot: " << test.getServer(i).getRoot() << std::endl;
		std::cout << "\tIndex: " << test.getServer(i).getIndex() << std::endl;
		//std::cout << "\tMethods: " << test.getServer(i).getMethods("all") << std::endl;
		std::cout << std::endl;
		for (unsigned int j = 0; j < test.getServer(i).getLocNum(); j++)
		{
			std::cout << "\tLocation " << j << ":" << std::endl;
			std::cout << "\t\tName: " << test.getServer(i).getLocation(j).getName() << std::endl;
			std::cout << "\t\tRoot: " << test.getServer(i).getLocation(j).getRoot() << std::endl;
			std::cout << "\t\tIndex: " << test.getServer(i).getLocation(j).getIndex() << std::endl;
			//std::cout << "\t\tCGI Pass: " << test.getServer(i).getLocation(j).getPass() << std::endl;
			//std::cout << "\t\tClient body buffer size: " << test.getServer(i).getLocation(j).getClientBuffSize() << std::endl;
			//std::cout << "\t\tAlias: " << test.getServer(i).getLocation(j).getAlias() << std::endl;
			//std::cout << "\t\tSub-Location: " << test.getServer(i).getLocation(j).getSubLocation() << std::endl;
			//std::cout << "\t\tMethods: " << test.getServer(i).getLocation(j).getMethods("all") << std::endl;
		}
	}

	/*// Create a socket (IPv4, TCP)
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); // int socket(int domain, int type, int protocol);
	if (sockfd == -1) {
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Listen to port 9999 on any address
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to network byte order

	if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Start listening. Hold at most 10 connections in the queue
	if (listen(sockfd, 10) < 0) {
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}*/
}
catch (std::exception &e)
{
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
	return 0;
}


