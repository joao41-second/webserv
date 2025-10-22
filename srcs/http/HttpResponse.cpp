/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:34:38 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/18 17:18:27 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/Config.hpp"
#include "config/ServerConfig.hpp"
#include <cstddef>
#include <cstdlib>
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


bool   HttpResponse::_request_status = false;
int HttpResponse::size_max = 500;

std::vector<ServerConfig> HttpResponse::_configs;

void HttpResponse::set_config(std::vector<ServerConfig> &conf)
{
	HttpResponse::_configs = conf;
}

std::string HttpResponse::open_static_file(std::string file)
{
	size_max = 500; // var do jota
	std::string request = "HTTP/1.1 200 OK\r\n";
	size_t size  = file.rfind('.');
	std::string type_file = file.substr(size,file.size());
	
	std::vector<char> temp(size_max);
	

	// adicionar data  info do server
	static std::ifstream file_fd(file.c_str());
	static bool status = false;
	static bool index = false;
	if (status == true)
	{
		index = false;
		file_fd.open(file.c_str());
	}
	if (!file_fd.is_open())
	{
		status = true;
		index = false;
		throw Not_found_404();
	}

	
	// TODO not correct use de .css and .js

	if(type_file == ".js" || type_file == ".css" || type_file == ".html")
	{

		request += "Content-Type: text/html; charset=UTF-8 \n";
		
	}else
	{
		//TODO do not check is wor

		request += "Content-Disposition: attachment; filename= " +   file+ '\n' ;
		request += "Content-Type: application/" + file.substr(file.size() - 4, file.size()) + ";\r\n";
	}
	file_fd.read(&temp[0], size_max);
	std::string data;
	for (int i = 0; i < (int)temp.size() && temp[i] != '\0'; i++)
		data += temp[i];
	if (data[data.size() - 1] == '\n')
		data[data.size() - 1] = '\n';
	std::stringstream ss;
	ss << (int)data.size();
	request += "Content-Length: " + ss.str() + "\r\n";
	// request += "Connection: close\r\n";
	request += "Connection: keep-alive\r\n\n";
	if (index == true)
		request = "";
	if (index == false)
	{
		index = true;
	}

	if (file_fd.eof())
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
	request += data;
	return (request);
}

std::string HttpResponse::rediect_path(std::string file_path)
{
	std::string file;
	std::string path;
	int size;	
	HttpParser::_host.find(':');
	int port = std::atoi(HttpParser::_host.substr(HttpParser::_host.find(':')+1,HttpParser::_host.size()).c_str());
	if(port == 0)
		throw Not_found_404();
	int i = -1;
	while (++i < (int)_configs.size())

		if( port == (int) _configs[i].getPort())
			break;
	std::map<std::string, LocationConfig>	_locations = _configs[i].getLocMap();
	if(file_path == "")	
		return "index.html"; // todo cireate find index
	
	size = file_path.rfind('/'); // TODO  if not 1 not good parsing
	file = file_path.substr(size, file_path.size());
	path = file_path.substr(0,size);

	HTTP_MSG(path <<  " oi " <<   file <<  "file  " << file_path << "end" << std::endl);	
	HTTP_MSG(_locations[path].getRoot()  <<  "locla");


	return (search_folder_file(file, path, _locations));
}



std::string HttpResponse::search_folder_file(std::string file ,std::string path , std::map<std::string, LocationConfig> loc)
{
	std::string real_path;
	int size;


		HTTP_MSG("st_aaaaaa");
	while (path.rfind('/') != std::string::npos) {
	
	
		if(loc[path].getRoot() != "" )
		{

			HTTP_MSG(loc[path].getRoot() + file)
			return( loc[path].getRoot() + file);
		}
		HTTP_MSG(path);
		size =path.rfind('/');
		file = path.substr(size,path.size()-1) + file;
		path = path.substr(0,size);

		//TODO duble alias not work

	}


	return("./index.html");
}


bool HttpResponse::chek_cig_or_static(std::string)
{

	// TODO  implemtn the check string execute cig or no
	return (false);
}

std::string HttpResponse::request_and_response(std::string request)
{
	int error;
	std::string response;
	std::string path = "";
	try
	{
		HttpParser::new_request(request);
		if (chek_cig_or_static(HttpParser::_pach_info))
		{

			// execute in exeve
		}
		else
		{
			// open and send file j
		
			path = rediect_path(HttpParser::_pach_info);
			HTTP_MSG("ola ");
			response = HttpResponse::open_static_file(path);
			HTTP_MSG("ola ");
		}
	}
	catch (std::exception &e)
	{
		error = std::atoi(e.what());
		(void)error;
		//TODO not inplemente use paths setd in config
		//error = std::atoi(e.what());
		// TODO not inplemente use paths setd in config
		return (gener_erro_page(HttpParser::_http_page_error, e.what()));
		std::cout << RED << "error: " << e.what() << RESET << std::endl;
	}
	HTTP_MSG("ola ");
	return (response);
}

std::string HttpResponse::gener_erro_page(int error, std::string status)
{
	std::string response, mens;
	std::stringstream ok;
	std::stringstream size;
	ok << error;

	response = "HTTP/1.1 " + ok.str() + " " + status + "\n";
	response += "Content-Type: text/html; charset=UTF-8 \n";
	// response = TODO add host the server
	mens =
		"<!DOCTYPE html>\n"
		"<html>\n"
		"<head><title>" +
		ok.str() + status + "</title></head>\n"
							"<body>\n"
							"<h1>" +
		status + "</h1>\n"
				 "<hr>\n"
				 "</body>\n"
				 "</html>\n";
	size << mens.size();
	response += "Content-Length: " + size.str() + "\n\n";
	response += mens;
	return response;
}
