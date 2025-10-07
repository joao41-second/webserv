/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:38 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/26 13:33:19 by jperpct          ###   ########.fr       */
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
		status = true;
		index = false; 
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
	request += data ;
	HTTP_MSG("ola");
	return (request);
}


std::string HttpResponse::rediect_path(std::string path)
{
	std::string file;
	int size;
	size = path.find('/'); //TODO  if not 1 not good parsing
	file = path.substr(size,path.size());
	size = path.find('/'); 
	if(size == (int)std::string::npos)
		return "ola" + file; //TODO the check the local file not implemtn
	

	// this funsicon is recorsive;

	

	return "ola" + file;
}

bool HttpResponse::chek_cig_or_static(std::string)
{

	//TODO  implemtn the check string execute cig or no
	return (false);
}

std::string HttpResponse::request_and_response(std::string request)
{
	int error;
	std::string response;
	std::string path;
	try
	{
	HttpParser::new_request(request);
	}
	catch(std::exception &e)
	{
		error = std::atoi(e.what());
		std::cout << RED << "error: "<< e.what() << RESET << std::endl;
	}
	if(chek_cig_or_static(HttpParser::_pach_info))
	{
		// execute in exeve 
	}
	else 
	{
		// open and send file j
		path =  rediect_path(HttpParser::_pach_info);
		HTTP_MSG( "_pach_info: "<< path << std::endl);
			
		response = HttpResponse::open_static_file(path);
		HTTP_MSG("what" << response);

	}	
	return (response);
}



