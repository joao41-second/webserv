/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:38 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/14 14:08:25 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HttpResponse.hpp>
#include <http/HttpParser.hpp>
#include <http/Http_throw.hpp>
#include <core/Server.hpp>
#include <iostream>
#include <net/Socket.hpp>
#include <ostream>
#include <string>
#include <sstream>
#include <vector>

HttpResponse::HttpResponse():_request_status(false){}

HttpResponse::~HttpResponse(){}


std::string HttpResponse::open_static_file(std::string file)
{
	size_max = 500; // var do jota
	std::string request = "HTTP/1.1 200 OK\r\n";
	std::vector<char> temp(size_max);

	// adicionar data  info do server 
	static std::ifstream file_fd(file.c_str());	
	static bool status = false;
	static bool index = false; 
	if(status == true)
	{
		index = false;
		file_fd.open(file.c_str());
	}
	if(!file_fd.is_open())
	{
		throw Not_found_404();
	}
	request += "Content-Type: application/" + file.substr(file.size()-4,file.size()) + ";\r\n"; 
	file_fd.read(&temp[0], this->size_max);
	std::string data;
	for(int i = 0; i < (int)temp.size() && temp[i] != '\0';i++  )
		data += temp[i];
	if(data[data.size()-1] == '\n')
		data[data.size()-1] = '\n';
	std::stringstream ss;
    	ss <<  (int)data.size();
	request +=  "Content-Length: " + ss.str() + "\r\n";
	//request += "Connection: close\r\n";
	request += "Connection: keep-alive\r\n";
	if(index == true )
		request = "";
	if(index == false)
	{
	 T_MSG("oi", RED);
	 index = true;
	}
	
	if(file_fd.eof())
	{
		file_fd.close();
		status = true;
		_request_status = true;
	 	index = false;
	}
	else 
	{		
		_request_status = false;
		status = false;
	}
	request +=   data ;
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



