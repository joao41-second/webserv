/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:16:35 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/18 17:18:00 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <config/color.hpp>
#include <core/Server.hpp>
#include <cstdlib>
#include <http/HttpParser.hpp>
#include <config/debug.hpp>
#include <http/Http_throw.hpp>
#include <string>
#include <sys/ucontext.h>

std::vector<std::string> HttpParser::env;
bool HttpParser::_request = false;
std::string HttpParser::mensage = "";
std::string HttpParser::_pach_info = "";
std::string HttpParser::_type = "";
int HttpParser::_http_page_error = 0;
std::string HttpParser::_host = "";

HttpParser::HttpParser(void)
{
	HTTP_MSG("start_parser");
}

HttpParser::HttpParser(const HttpParser &value)
{
	HTTP_MSG("start_parser_used_privios_HttpParser");
	(void) value;
}

HttpParser& HttpParser::operator=(const HttpParser &value)
{
	HTTP_MSG("iqual operator used");
	if(&value == this)
		return (*this);
	return (*this);
}

HttpParser::~HttpParser()
{
	HTTP_MSG("end parser");
}


static std::string trim(const std::string &s)
{
    std::string::size_type start = s.find_first_not_of(" \t\r\n");
    std::string::size_type end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

void HttpParser::parsing_request_line(std::string buffer)
{
	bool query_string = true;
	//set request method
	size_t size = buffer.find(' ');
	std::string method = buffer.substr(0,size);
	if (size == std::string::npos || size == 0)
		throw  Badd_Request_400();
	if(method != "GET" && method != "POST" && method != "DELETE")
		throw Not_Implemented_501();
	env.push_back("REQUEST_METHOD='" + method + "'");	
	buffer = buffer.substr(size+1,buffer.size());
	// set paht info
	size = buffer.find('?');
	if (size == std::string::npos || size == 0)
	{
		query_string = false;
		size = buffer.find(' ');
		if(size == std::string::npos || size == 0)
		 throw  Badd_Request_400();
	}
	method = buffer.substr(0,size);
	buffer = buffer.substr(size+1,buffer.size());
	HttpParser::_pach_info = method;
	T_MSG(_pach_info, REG_CR2);

	env.push_back("PATH_INFO='" + method + "'");
	// set query_string if true
	if(query_string == true)
	{
		size = buffer.find(' ');
		if (size == std::string::npos || size == 0)
			throw  Badd_Request_400();
		method = buffer.substr(0,size);
		env.push_back("QUERY_STRING='" + method + "'");
		buffer = buffer.substr(size+1,buffer.size());
	}
	//set protocl
	HTTP_MSG(buffer);
	method = buffer.substr(0,5);

	HTTP_MSG(method);
	if(method != "HTTP/")
	   throw Version_Not_Supported_505();

	method = buffer.substr(5,buffer.size());
	buffer = method; 

	if(std::atof(buffer.c_str()) == 1.1)
	{

		env.push_back("SERVER_PROTOCOL='HTTP/"+trim (buffer)+ "'\r");}
	else
	   throw Version_Not_Supported_505();
	
	
}



void HttpParser::parsing_env(std::string buffer)
{
	size_t size = buffer.find('\n');
	std::string line = buffer.substr(0,size + 1);
	std::string buffer_new = buffer.substr(size+1,buffer.size()); 
	std::string var;
	std::string content;

	if( size == std::string::npos || line == "\n" || size == 1 )
	{
		mensage = buffer_new;
		return;
	}
	else
	{
		line = buffer.substr(0,size );
		size = 	line.find(':');
		if(size == std::string::npos && _request == false)
		{
			_request = true;
			parsing_request_line(line);
			parsing_env(buffer_new);
			return;
		}
		if (size == std::string::npos || size == 0)
			throw Badd_Request_400();	
		var = line.substr(0,size);	
		content = line.substr(size+1,line.size()-2);
		std::replace(var.begin(), var.end(), '-', '_');
		if(var == "Host")
			_host = content;
		for (int i =0; i < (int)var.size(); ++i) {
			int char_ = var[i];
			var[i] = std::toupper(char_);
		}
		env.push_back("HTTP_"+trim(var)+"='"+trim( content)+"'");
		parsing_env(buffer_new);
	}

}

void HttpParser::new_request(std::string buffer)
{

	env.clear();
	mensage = "";
	_pach_info = "";
	_type = "";
	_host = "";
	_request = false;
	T_MSG("Parse the new request" << std::endl << std::endl << buffer, BLUE);
	parsing_env(buffer);
	T_MSG("ok",GREEN);

}


std::string HttpParser::get_request_msg()
{
	return (mensage);
}

std::vector <char *> HttpParser::get_request_env()
{
	std::vector<char *> envp;

	for (int i = 0; i < (int) env.size(); i++)
	{
	  envp.push_back((char *)env[i].c_str());
	}
	
      return (envp);
}

