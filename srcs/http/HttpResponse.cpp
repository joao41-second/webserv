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
#include <atomic>
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

	request += "Content-Type: application/" + file.substr(file.size() - 4, file.size()) + ";\r\n";

	//TODO add config for set if file for download
	/request += "Content-Type: text/html; charset=UTF-8 \n";
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

std::string HttpResponse::rediect_path(std::string path)
{
	std::string file;
	int size;
	size = path.find('/'); // TODO  if not 1 not good parsing
	file = path.substr(size, path.size());
	size = path.find('/');
//	if (size == (int)std::string::npos)
//		return "ola" + file; // TODO the check the local file not implemtn

	// this funsicon is recorsive;

	return ("ola/index.html");
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
	std::string path;
	try
	{
		HttpParser::new_request(request);
		HTTP_MSG( "ola o error e "<< HttpParser::_host)
		if (chek_cig_or_static(HttpParser::_pach_info))
		{

			// execute in exeve
		}
		else
		{
			// open and send file j
		
			path = rediect_path(HttpParser::_pach_info);
			HTTP_MSG("_pach_info: " << path << std::endl);
			response = HttpResponse::open_static_file(path);
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
	HTTP_MSG(response);
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
