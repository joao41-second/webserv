/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:38 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/24 15:28:58 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HttpResponse.hpp>
#include <http/HttpParser.hpp>
#include <http/Http_thow.hpp>
#include <core/Server.hpp>
#include <net/Socket.hpp>
#include <string>
#include <sstream>


std::string HttpResponse::open_static_file(std::string file)
{
	char *data;
	std::string request = "HTTP/1.1 200 OK\r\n";
	std::string temp;

	// adicionar data  info do server 
	std::ifstream file_fd(file.c_str());
	if(!file_fd.is_open())
	{
		throw Not_found_404();
	}
	request += "Content-Type: application/" + file.substr(file.size()-4,file.size()) + ";\r\n"; 
	file_fd.read(data, this->size_max);
	std::stringstream ss;
    	ss <<  std::atoi(data); 
	request +=  "Content-Length: " + ss.str() + "\r\n";
	if(file_fd.eof())
	{
		request += "Connection: close\r\n";
	}
	else 
	{		
		request += "Connection: keep-alive\r\n";
	}
	return (data);
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



