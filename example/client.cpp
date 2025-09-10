/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:04:33 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/10 11:34:45 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080



int main()
{
	int server_fd,new_socket;
	struct sockaddr_in address;
	int addr_len = sizeof(address);
	char buffer[1024]= {0};
	std::string mens = "ola";

	server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_fd == 0)
	{
		std::cout << "error: not open socket" << std::endl;
		exit(1);
	}
	
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	if(inet_pton(AF_INET,"0.0.0.0",&address.sin_addr) <= 0)
	{
		std::cout << "error: not open socket" << std::endl;
		exit(1);
	}

	if (connect(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "Falha na conexão\n";
        return -1;
    }

	std::string hello = "ola";
    // Enviar mensagem
    send(server_fd, hello.c_str(), hello.size(), 0);
    std::cout << "Mensagem enviada ao servidor.\n";

    // Receber resposta
	

}
