/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:16:35 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/23 15:42:08 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/color.hpp"
#include <algorithm>
#include <core/Server.hpp>
#include <http/HttpParser.hpp>
#include <config/debug.hpp>

HttpParser::HttpParser(void)
{
	HTTP_MSG("start_parser");
	this->mensage = "";
}

HttpParser::HttpParser(const HttpParser &value)
{
	HTTP_MSG("start_parser_used_privios_HttpParser");
	this->mensage =  value.mensage;
	this->env =  value.env;
}

HttpParser& HttpParser::operator=(const HttpParser &value)
{
	HTTP_MSG("iqual operator used");
	if(&value == this)
		return (*this);
	this->mensage =  value.mensage;
	this->env =  value.env;
	return (*this);
}

HttpParser::~HttpParser()
{
	HTTP_MSG("end parser");
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
	this->env.push_back("REQUEST_METHOD='" + method + "'");	
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

	this->env.push_back("PATH_INFO='" + method + "'");
	// set query_string if true
	if(query_string == true)
	{
		size = buffer.find(' ');
		if (size == std::string::npos || size == 0)
			throw  Badd_Request_400();
		method = buffer.substr(0,size);
		this->env.push_back("QUERY_STRING='" + method + "'");
		buffer = buffer.substr(size+1,buffer.size());
	}
	//set protocl
	if(buffer == "HTTP/1.1")
		this->env.push_back("SERVER_PROTOCOL='" + buffer + "'");
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

	if( size == std::string::npos || line == "\n" )
	{
		this->mensage = buffer_new;
		return;
	}
	else
	{
		line = buffer.substr(0,size );
		size = 	line.find(':');
		if(size == std::string::npos && _header == false)
		{
			this->_header = true;
			parsing_request_line(line);
			parsing_env(buffer_new);
			return;
		}
		if (size == std::string::npos || size == 0)
			throw Badd_Request_400();	
		var = line.substr(0,size);	
		content = line.substr(size+1,line.size());
		std::replace(var.begin(), var.end(), '-', '_');
		this->env.push_back("HTTP_"+var+"='"+ content+"'");
		parsing_env(buffer_new);
	}

}
void HttpParser::new_request(std::string buffer)
{
	this->_header = false;
	this->env.clear();
	this->mensage = "";
	HTTP_MSG("Parse the new request");
	parsing_env(buffer);
	for (int i = 0; i < (int)this->env.size(); i++) 
		HTTP_MSG(this->env[i]);	
	HTTP_MSG(this->mensage);
	T_MSG("ok",GREEN);

}

