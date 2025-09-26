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

#include "core/Server.hpp"
#include <cgi/cgi.hpp>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

//not tested
//

Cgi::Cgi(){}
Cgi::~Cgi(){}
void Cgi::create_env( char **env,std::vector<char *> env_request)
{
	int i = 0;
	_envs = env_request;
	while (env[i] != NULL)
	{
		_envs.push_back(env[i]);
		i++;
	} 
}

std::string Cgi::execute(std::string _request)
{
	int pid = fork();
	int fd[2];
	int status,read_bits;
	char buffer[1024];
	std::string response = "";	
	
	if(pipe(fd) == -1)
		exit(1);
	if(pid == -1)
		exit(1);	
	dup2(fd[0],0);	
	close(fd[0]);
	write(0,_request.c_str(),_request.size());
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],1);
		close(fd[1]);
		execlp("ls", "ls", "-l", NULL);
		exit(1);
	}
	else
	{
		close(fd[1]);
		while ((read_bits = read(1,buffer,1024)) > 0)
			response +=  buffer;
		waitpid(pid, &status, 0);
	}	
	return response;
}
