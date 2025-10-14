#include "../../include/net/Socket.hpp"
<<<<<<< HEAD
#include "../../include/config/Config.hpp"
#include "../../include/config/ServerConfig.hpp"
#include "../../include/config/LocationConfig.hpp"
=======
#include "../../include/config/config.hpp"
>>>>>>> Parser_request_http

// |----------------------
// | HELPER FUNCTIONS
// |----------------------

// |----------------------
// | MEMBER FUNCTIONS
// |----------------------

// |----------------------
// | GETTERS & SETTERS
// |----------------------

<<<<<<< HEAD
uint16_t	Socket::getAddrPort() const
{
	return(ntohs(this->_addr.sin_port));
}

=======
>>>>>>> Parser_request_http
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
<<<<<<< HEAD
		if (this->_fd >= 0)
		{
			close(this->_fd);
		}
		this->_fd = orig._fd;
		this->_addr = orig._addr;
		orig._fd = -1;
=======
		this->_fd = orig._fd;
		this->_addr = orig._addr;
>>>>>>> Parser_request_http
	}
	//std::cout << "Socket assignment copy-constructed." << std::endl;
	return (*this);
}

Socket::Socket(const Socket &orig): _fd(orig._fd), _addr(orig._addr)
{
<<<<<<< HEAD
	orig._fd = -1;
=======
>>>>>>> Parser_request_http
	//std::cout << "Socket copy-constructed." << std::endl;
}*/

Socket::Socket(uint16_t port)
{
<<<<<<< HEAD
	// Create socket
=======
    // Create socket
>>>>>>> Parser_request_http
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd < 0)
	{
		throw InputException("Could not create socket");
	}

	// F_SETFL → set socket's status flags ; O_NONBLOCK → Set socket's flag to non-blocking
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw InputException("Could not set socket to non-blocking");
	}

<<<<<<< HEAD
	// Listen to port on the address
=======
    // Listen to port on any address
>>>>>>> Parser_request_http
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_addr.s_addr = INADDR_ANY;
	this->_addr.sin_port = htons(port);

<<<<<<< HEAD
	// Bind port to socket
	if (bind(this->_fd, (struct sockaddr*)&this->_addr, sizeof(this->_addr)) < 0)
=======
    // Bind port to socket
	if (bind(this->_fd, (struct sockaddr*)&this->_addr, sizeof(sockaddr)) < 0)
>>>>>>> Parser_request_http
	{
		throw InputException("Failed to bind to the port");
	}

	// Start listening. Hold at most 10 connections in the queue
	if (listen(this->_fd, 10) < 0) // TODO only 10 connections? Or 1024?
	{
		throw InputException("Failed to listen on socket");
	}
	//std::cout << "Socket constructed." << std::endl;
}

<<<<<<< HEAD
/*Socket::Socket(void)
{
	//std::cout << "Socket constructed." << std::endl;
}*/

Socket::~Socket(void)
{
	if (this->_fd >= 0)
		close(this->_fd);
=======
Socket::Socket(void)
{
	//std::cout << "Socket constructed." << std::endl;
}

Socket::~Socket(void)
{
    // close(this->fd); // TODO confirmar se e necessario
>>>>>>> Parser_request_http
	//std::cout << "Socket destructed." << std::endl;
}

// |----------------------
// | OVERLOAD OPERATIONS
// |----------------------

// |----------------------
// | EXCEPTIONS
// |----------------------
