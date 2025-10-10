/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:44:16 by cereais           #+#    #+#             */
/*   Updated: 2025/10/10 19:03:50 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Server.hpp"
#include "Connection.hpp"
#include <poll.h>
#include <unistd.h>

class Server;
class Connection;

class EventLoop {

public:
	EventLoop();
	~EventLoop();

	void	addListeningSocket(const Socket* socket, Server& server);
	void	run();

private:
	struct PollEntry {
		struct pollfd		pfd;
		struct sockaddr_in	socketAddr;
		Server*				server;		//probably a leak here
		Connection*			conn;
	};

	std::vector<PollEntry>	_pollEntries;

	void	handleNewConnection(PollEntry& entry);
	void	closeConnection(PollEntry& entry);
};
