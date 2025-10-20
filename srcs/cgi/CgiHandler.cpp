/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:03:03 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/03 16:20:05 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/color.hpp"
#include "config/LocationConfig.hpp"
#include "core/Server.hpp"
#include "http/HttpParser.hpp"
#include <cgi/cgi.hpp>
#include <ostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

Cgi::Cgi(){}
Cgi::~Cgi(){}


std::string Cgi::chek_program_pach(std::string porgram)
{
	T_MSG("error" << _path.size(),BWHITE )	;

	if(!(_path.size() >= 1))
	{
		int i = -1;
		while(++i < (int)_envs.size())
		{
			if(std::strncmp("PATH=",_envs[i],5) == 0)
			{
				break;	 // ver error a for 
			}
		}
		std::stringstream ss(_envs[i]);
		std::string path;
		
		while (std::getline(ss,path,':'))
		{
			_path.push_back(path);	
		}	
	}
	T_MSG("pache size " << _path.size(),BWHITE );
	struct dirent *name_dir;
	std::string name_program_dir;
	for(int i=0;(int)_path.size() > i; i++)
	{
		if(i == 0)
		{
			_path[i] = _path[i].substr(5,_path[i].size());
		}
 		DIR* dir = opendir(_path[i].c_str());
		if(dir == NULL)
		{
			continue;
		}
		name_dir = readdir(dir);
		while ( name_dir != NULL) 
		{
			name_program_dir = name_dir->d_name;
			if(name_program_dir == porgram)
			{

				HTTP_MSG("path for porgram use is" <<_path[i] <<" " <<name_program_dir);
				 if (access((_path[i] +"/"+name_program_dir).c_str(), X_OK) == 0)
				 {
					closedir(dir);
					return (_path[i]);
				 }
				 else
				 {
					 // tenho que chekar que error por aqui 
				 }
			}
			name_dir = readdir(dir);
		}

		closedir(dir);
	}
	T_MSG("error",BWHITE )	;
	return NULL;
}

void Cgi::create_env( char **env,std::vector<char *> env_request)
{
	int i = 0;
	_envs = env_request;
	while (env[i] != NULL)
	{
		_envs.push_back(env[i]);
		i++;
	} 
	Cgi::chek_program_pach("python3");
}

std::string Cgi::execute(std::string _request)
{
	int pid ;
	int fd_in[2];
	int fd_out[2];
	int status,read_bits;
	char buffer[1024];
	std::string response = "";	
	
	if(pipe(fd_in) == -1)
		exit(1);
	if(pipe(fd_out) == -1)
		exit(1);

	pid = fork();
	if(pid == -1)
		exit(1);	

	if(pid == 0)
	{

		dup2(fd_in[0],0);
		dup2(fd_out[1],1);	
		close(fd_in[1]);
		close(fd_out[0]);
		execlp("cat", "cat" , NULL);
		exit(1);
	}
	else
	{
		close(fd_in[0]);
		close(fd_out[1]);
		write(fd_in[1],_request.c_str(),_request.size());
		close(fd_in[1]);
		while ((read_bits = read(fd_out[0],buffer,1024)) > 0)
		{
			response.append(buffer,read_bits);
		}
		close(fd_out[0]);
		waitpid(pid, &status, 0);
	}	
	return response;
}
