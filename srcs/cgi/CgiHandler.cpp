/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:03:03 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/18 17:17:08 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/color.hpp"
#include "http/HttpParser.hpp"
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <http/Http_throw.hpp>
#include "http/HttpParser.hpp"
#include "http/HttpResponse.hpp"
#include <config/color.hpp>
#include <config/LocationConfig.hpp>
#include <core/Server.hpp>
#include <http/HttpParser.hpp>
#include <cgi/cgi.hpp>
#include <ostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

void  create_var( HttpParser *par,HttpResponse *var ,Cgi *cgi)
{
	var->cgi = cgi;
	var->_parser = par;
	par->_request_c = var;
	cgi->_request_c = var;
	cgi->_parser = par;
	
}

Cgi::Cgi():_path(),_envs()
{
	_request = "" ;
	_file_name_out = "";
	_file_name = "";

}
Cgi::~Cgi(){}

Cgi & Cgi::operator=(const Cgi &copy)
{
	if(this != &copy)
	{

		 this->_request = copy._request;
		 this->_file_name = copy._file_name;
		 this->_file_name_out = copy._file_name;
		 this->_path = copy._path;
		 this->_request_c = copy._request_c;
		 this->_parser = copy._parser;
		this->_envs = copy._envs;
		return  *this;
	}
	return  *this;
}	

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

				 if (access((_path[i] +"/"+name_program_dir).c_str(), X_OK) == 0)
				 {
					closedir(dir);
					return (_path[i]);
				 }
				 else
				 {
					 // tenho que chekar que error por aqui 
					 throw Not_found_404();
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
	for (int e = 0; e < (int)env_request.size();e++) 
	{
		//HTTP_MSG(env_request[e]);
	}
}

int Cgi::save_chunk_fd(std::string str)
{
	static int fd=  -1;


	HTTP_MSG("paser is chunk status" <<  _parser->_is_chunk);
	std::stringstream port;
	port << _parser->_port << _request_c->fd;
	_file_name =  "/tmp/saida_"+ port.str() + ".txt";


	if( _parser->_is_chunk == HTTP_CONTENT || _parser->_is_chunk == HTTP_EMPTY )
	{

			fd = open(_file_name.c_str(),O_RDWR | O_CREAT , 0644);
			if(fd == -1)
			{
				throw Not_found_404();
			}
			write(fd,str.c_str(),str.size());
			close(fd);
			return (open(_file_name.c_str(),O_RDWR | O_CREAT , 0644));
		
	}


	if(_parser->_is_chunk == HTTP_CHUNKS)
	{
		if(str.empty())
		{
			return (-1);
		}
		if(str == "0\r\n\r\n")
			return (open(_file_name.c_str(),O_RDWR | O_CREAT , 0644));
		fd = open(_file_name.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
		if(fd == -1)
			throw Not_found_404(); //TODO nao e este o error  

		int size =  str.find('\r');
		if(size == (int)std::string::npos)
			throw Not_found_404(); //TODO nao e este o error  
		int bits;
		std::string nb = str.substr(0,size);
		std::string al = str.substr(size+2,str.rfind('\r'));
		std::stringstream ss(str);
		ss >> bits;
		if(ss.fail())
			throw Not_found_404(); //TODO nao e este o error  
		write(fd,al.c_str(),bits);
		close(fd);
	}

	return -1;
}
#include <http/HttpResponse.hpp>

std::string 	Cgi::chek_and_return_chunks(std::string file_name)
{
	int 			size= 100000;
	static int 		fd_out = -1;
	int 			read_bits = 0;
	char			buffer[1024];
	std::string 		response = "";
	static std::string 	save = "";
	std::stringstream 	value ;
	static int 		status = 0;

	HTTP_MSG("var check is true" << _request_c->_request_status)
	if(_request_c->_request_status == true)
	{
		return (_request_c->open_static_file("NULL"));
	}
	
	if(file_name != "NULL")
		fd_out = open(_file_name_out.c_str(),O_RDWR | O_CREAT , 0644);
	response = save;
	while ((read_bits = read(fd_out,buffer,1024)) > 0 || save.size() > 0)
	{
		
		T_MSG("read loop  =" << read_bits , RED);
		response.append(buffer,read_bits);
		if((int)response.find("\n\n")  != -1 && status == 0)
		{
			status =  response.find("\n\n");
		}
		else  if((int)response.find("\r\n\r\n")  != -1 && status == 0)
		{
			status =  response.find("\r\n\r\n");
		}
		else if(status == 0)
		{
			//TODO errorr;
		}
		if(status == 0)
		{
			continue;
		}
		else if(status != -1 && status != 0 && _parser->_is_chunk != HTTP_EMPTY)
		{
			save = response.substr(status,response.size());
			response = response.substr(0,status);
			response.append("\r\n\r\n");
			_request_c->_new_response = true;
			if(read_bits == 0)
				_request_c->_new_response = false;
			status = -1;
			return ( response);
		}
		if((int )response.size()-status > size  || (read_bits == 0 && save.size() != 0))
		{
			if(read_bits != 0)
			{
				save = response.substr(size,response.size());
				response = response.substr(0,size);
			}
			else if( (int)save.size() > size) 
			{

				response = save.substr(0,size);
				save = save.substr(size,save.size());
			}
			else 
			{
				response = save;
				save = "";
			}
			if(read_bits == 0)
				_request_c->_new_response = false;
			else
				_request_c->_new_response = true;
			value << response.size();	
			response = value.str() + "\r\n"+response+"\r\n";
			return (response);
		}
	}
	_request_c->_new_response = false;
	save = "";
	response.append("\r\n\r\n");
	close(fd_out);
	return (response);


}

std::string Cgi::execute(std::string _request, std::string porgram, bool *request)
{
	int 		pid ;
	int 		fd_in;
	int 		fd_out;
	int 		status;
	std::string  	response = "";
	char 		**end = NULL;
	int 		fd =-1;

	HTTP_MSG("start _ cgi and :" << _request);

	if(_request_c->_new_response == false)
			std::remove(_file_name_out.c_str());	

	_envs.push_back(NULL);		
	if((fd = save_chunk_fd(_request)) == -1)
	{
		*request = _request_c->_new_request;
		return "";
	}

	fd_in = fd;	
	HTTP_MSG("chage_type")
	_request_c->_new_request = false;

	std::stringstream port;
	port << _parser->_port << _request_c->fd;
	_file_name_out =  "/tmp/out_"+  port.str() + ".txt";
	fd_out = open(_file_name_out.c_str(),O_RDWR | O_CREAT , 0644);

	pid = fork();
	if(pid == -1)
		exit(1);	

	if(pid == 0)
	{	

		dup2(fd_in,0);
		dup2(fd_out,1);	
		close(fd_in);
		close(fd_out);
		int i  = execve( porgram.c_str(),end,_envs.data());
		HTTP_MSG("merda = " << i)
		perror("execve");
		exit(33);
	}
	else
	{
		close(fd_out);
		close(fd_in);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status)) {
   		 int exit_code = WEXITSTATUS(status);
		
		response = chek_and_return_chunks(_file_name_out);
		if(  _request_c->_new_response == true && 
				(_parser->_is_chunk ==  HTTP_EMPTY ||   _parser->_is_chunk ==  HTTP_CONTENT ))
		{
		 response += chek_and_return_chunks(_file_name_out);
		}
		std::remove(_file_name.c_str());

		if(exit_code == 33) // TODO change this value for 0 
			throw Not_found_404();
		} 
	}

	return response;
}
