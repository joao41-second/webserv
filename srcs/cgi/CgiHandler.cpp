/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:03:03 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/26 14:41:12 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/color.hpp"
#include "core/Server.hpp"
#include "http/HttpParser.hpp"
#include <cgi/cgi.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

//not tested
//

Cgi::Cgi(){}
Cgi::~Cgi(){}
void Cgi::create_env( char **env,std::vector<char *> env_request,int argc)
{
	int i = 0;
	_envs = env_request;
	while (i < argc)
	{
		_envs.push_back(env[i]);
		i++;
	} 
}

std::string Cgi::execute(std::string _request)
{
	int pid ;
	int fd[2];
	int status,read_bits;
	char buffer[1024];
	std::string response = "";	
	
	if(pipe(fd) == -1)
		exit(1);

	dup2(fd[0],0);	
	close(fd[0]);
	write(0,_request.c_str(),_request.size());
	pid = fork();
	if(pid == -1)
		exit(1);	

	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execlp("echo", "echo", "ola mundo", NULL);
		exit(1);
	}
	else
	{

		close(fd[1]);
		while ((read_bits = read(0,buffer,1024)) > 0)
		{
			response.append(buffer,read_bits);
		}
		waitpid(pid, &status, 0);
	
	}	
	return response;
}
