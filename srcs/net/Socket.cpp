#include "../../include/net/Socket.hpp"
#include "../../include/config/Config.hpp"
#include "../../include/config/ServerConfig.hpp"
#include "../../include/config/LocationConfig.hpp"

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

// |----------------------
// | GETTERS & SETTERS
// |----------------------

uint16_t	Socket::getAddrPort() const
{
	return(ntohs(this->_addr.sin_port));
}

struct sockaddr_in const	&Socket::getAddr() const
{
	return(this->_addr);
}

int		Socket::getFd() const
{
	return(this->_fd);
}

// |----------------------
// | CONSTRUCTORS & DESTRUCTORS
// |----------------------

/*Socket &Socket::operator = (const Socket &orig)
{
	if (this != &orig)
	{
		if (this->_fd >= 0)
		{
			close(this->_fd);
		}
		this->_fd = orig._fd;
		this->_addr = orig._addr;
		orig._fd = -1;
	}
	//std::cout << "Socket assignment copy-constructed." << std::endl;
	return (*this);
}

Socket::Socket(const Socket &orig): _fd(orig._fd), _addr(orig._addr)
{
	orig._fd = -1;
	//std::cout << "Socket copy-constructed." << std::endl;
}*/

Socket::Socket(uint16_t port) // TODO Os throws agora apagam o server... mas o fd ainda precisa de ser fechado?
{
	// Create socket
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd < 0)
	{
		throw Config::BadPortException("Could not create socket: Port ", port);
	}

	// Set SO_REUSEADDR to allow immediate reuse of the port
	int opt = 1;
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		throw Config::BadPortException("Could not set SO_REUSEADDR: Port ", port);
	}

	// F_SETFL → set socket's status flags ; O_NONBLOCK → Set socket's flag to non-blocking
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw Config::BadPortException("Could not set socket to non-blocking: Port ", port);
	}

	// Listen to port on the address
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = INADDR_ANY;
	this->_addr.sin_port = htons(port);

	// Bind port to socket
	if (bind(this->_fd, (struct sockaddr*)&this->_addr, sizeof(this->_addr)) < 0)
	{
		throw Config::BadPortException("Failed to bind to the port: ", port);
	}

	if (listen(this->_fd, 1024) < 0)
	{
		throw Config::BadPortException("Failed to listen on socket: Port ", port);
	}
	//std::cout << "Socket constructed." << std::endl;
}

/*Socket::Socket(void)
{
	//std::cout << "Socket constructed." << std::endl;
}*/

Socket::~Socket(void) {
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------
