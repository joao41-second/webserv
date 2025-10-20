/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:30:05 by cereais           #+#    #+#             */
/*   Updated: 2025/10/19 18:23:00 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <config/Config.hpp>
#include <net/Socket.hpp>
#include <signal.h>
#include <termios.h>

static void disable_ctrlc_echo() {

    struct termios	t;
    if (tcgetattr(STDIN_FILENO, &t) == 0)
    {
        t.c_lflag &= ~ECHOCTL;   //stop echoing ^C
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
    }
}

static void signalHandler(int) {
    std::cout << "Shutting down server..." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "..." << std::endl;
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 2)
	{
		throw InputException("The program should use the template './webserv [configuration file]'");
	}

	disable_ctrlc_echo();
    signal(SIGINT, signalHandler);

	Config conf_info(argv[1], envp);

	std::vector<ServerConfig>	configs = conf_info.getServerConfigVector();
	std::vector<Socket*>		sockets = conf_info.getSocketVector();

	Server server(configs, sockets);
	server.launch();

	return (0);
}
