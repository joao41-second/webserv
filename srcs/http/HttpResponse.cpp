/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:38 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/24 15:54:12 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HttpResponse.hpp>
#include <http/HttpParser.hpp>
#include <http/Http_thow.hpp>
#include <core/Server.hpp>
#include <iostream>
#include <net/Socket.hpp>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>

HttpResponse::HttpResponse(){}

HttpResponse::~HttpResponse(){}


std::string HttpResponse::open_static_file(std::string file)
{
	size_max = 500;
	std::string request = "HTTP/1.1 200 OK\r\n";
	std::vector<char> temp(size_max);

	// adicionar data  info do server 
	std::ifstream file_fd(file.c_str());
	if(!file_fd.is_open())
	{
		throw Not_found_404();
	}
	request += "Content-Type: application/" + file.substr(file.size()-4,file.size()) + ";\r\n"; 
	file_fd.read(&temp[0], this->size_max);
	std::string data;
	for(int i = 0; i < (int)temp.size() && temp[i] != '\0';i++  )
		data += temp[i];
	std::stringstream ss;
    	ss <<  (int)data.size();
	request +=  "Content-Length: " + ss.str() + "\r\n";
	if(file_fd.eof())
	{
		request += "Connection: close\r\n";
	}
	else 
	{		
		request += "Connection: keep-alive\r\n";
	}
	request += "\r\n" + data + "\r\n";
	return (request);
}

std::string HttpResponse::request_and_response(std::string request)
{
	std::string response;

	HttpParser::new_request(request);

	if(true)
	{
		// execute in exeve 
	}
	else 
	{
		// open and send file 
	}	
	return (response);
}



