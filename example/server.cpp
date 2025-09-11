/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:53:00 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/10 11:52:33 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <asm-generic/socket.h>
#include <iostream>
#include <memory_resource>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 10000


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

	int opt = 1;
	if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)) < 0)
	{
		
		std::cout << "error: the restor the port not setd" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if(bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0 )
	{
		std::cout << "error: not conect for port" << std::endl;
		exit(1);
	}

	// cria file para conessoes pendentes
	if(listen(server_fd,3))
	{
		std::cout << "error: client not conect" << std::endl;

		exit(1);
	}

	 std::cout << "Servidor esperando na porta " << PORT << "...\n";

	 new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addr_len);
	 if(new_socket < 0)
	 {
		std::cout << "error: not work accept" << std::endl;
		exit(1);
	 }

	 read(new_socket, buffer, 1024);

		std::cout << "mensagem recebida: " << buffer  << std::endl;


    	std::string resposta_http =
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 11 Sep 2025 14:23:00 GMT\n"
        "Server: Apache/2.4.54 (Ubuntu)\n"
        "Content-Type: text/html; charset=UTF-8\n"
        "Content-Length: 137\n"
        "\n"
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "    <title>Exemplo</title>\n"
        "</head>\n"
        "<body>\n"
        "    <h1>Olá, mundo!</h1>\n"
        "    <h1>Olá, mundo!</h1>\n"
	" olas "
        "</body>\n"
        "</html>\n";
	
	send(new_socket,resposta_http.c_str(),resposta_http.size(),0);

	close(new_socket);
	close(server_fd);


}
