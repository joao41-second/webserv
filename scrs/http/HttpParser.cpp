/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:16:35 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/22 16:18:58 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstddef>
#include <http/HttpParser.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

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

void HttpParser::parsing_env(std::string buffer)
{
	static bool get = false;
	size_t size = buffer.find('\n');
	std::string line = buffer.substr(0,size + 1);
	std::string buffer_new = buffer.substr(size+1,buffer.size()); 


	if( size == std::string::npos || line == "\n" )
		return;
	else
	{
		line = buffer.substr(0,size );
		size = 	line.find(':');
		if(size == std::string::npos && get == false)
		{
			get = true;
			// treat the get our poust line 
			parsing_env(buffer_new);
			return;
		}
		else if(size == std::string::npos || size == 0)
			throw Badd_Request_400();

		if(size == 0)
			throw Badd_Request_400();
		std::string var = line.substr(0,size);	
		std::string content = line.substr(size+1,line.size());
		std::replace(var.begin(), var.end(), '-', '_');
		this->env.push_back("HTTP_"+var+"='"+ content+"'");
		parsing_env(buffer_new);
	}
}
void HttpParser::new_request(std::string buffer)
{
	HTTP_MSG("Parse the new request");
	parsing_env(buffer);
	for (int i = 0; i < (int)this->env.size(); i++) 
	{
		HTTP_MSG(this->env[i]);
	}
	
	
}

