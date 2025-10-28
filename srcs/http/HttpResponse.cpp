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

#include "cgi/cgi.hpp"
#include "config/Config.hpp"
#include "config/LocationConfig.hpp"
#include "config/ServerConfig.hpp"
#include "config/color.hpp"
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
int HttpResponse::size_max = 50000;
char ** HttpResponse::_env;
std::string HttpResponse::_pg = "";

std::vector<ServerConfig> HttpResponse::_configs;
std::map<std::string,std::string> HttpResponse::_types;

void HttpResponse::set_config(std::vector<ServerConfig> &conf, char  **env)
{
	HttpResponse::_env = env;
	HttpResponse::_configs = conf;
  	_types[".html"] = "text/html";
        _types[".htm"]  = "text/html";
        _types[".css"]  = "text/css";
        _types[".js"]   = "application/javascript";
        _types[".json"] = "application/json";
        _types[".png"]  = "image/png";
        _types[".jpg"]  = "image/jpeg";
        _types[".jpeg"] = "image/jpeg";
        _types[".gif"]  = "image/gif";
        _types[".ico"]  = "image/x-icon";
        _types[".svg"]  = "image/svg+xml";
        _types[".txt"]  = "text/plain";
        _types[".cgi"]  = "text/html;charset=UTF-8";
        _types[".py"]   = "text/html;charset=UTF-8";
        _types[".php"]  = "text/html;charset=UTF-8";

	//TODO add the get cgi and create type of cgi 
}

std::string HttpResponse::open_static_file(std::string file)
{
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
	if(!_types[type_file].empty())
	{

		request += "Content-Type: " + _types[type_file] +"\n";
		
	}else
	{
		//TODO this vereficasion no finic
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

	for( std::map<std::string, LocationConfig>::iterator  it = _locations.begin();  it != _locations.end();++it)
	{
		HTTP_MSG( " loc-> " << it->first)
	}
	size = file_path.rfind('/'); 
	file = file_path.substr(size, file_path.size());
	path = file_path.substr(0,size+1);
	return (search_folder_file(file, path, _locations));
}



std::string HttpResponse::search_folder_file(std::string file ,std::string path , std::map<std::string, LocationConfig> loc)
{
	std::string real_path = "";
	int size = 0;

	if( loc[path+file].getRoot() != "")
			return loc[path+file].getRoot();	
	while (path.rfind('/') != std::string::npos) {
		if( loc[path+file].getRoot() != "")
			return loc[path+file].getRoot() ;
	
		if(loc[path].getRoot() != "" )
		{
			return( loc[path].getRoot() + file);
		}
		size =path.rfind('/');
		file = path.substr(size,path.size()-1) + file;
		path = path.substr(0,size);

		//TODO duble alias not work
	}

	return("./index.html");
}

 ServerConfig HttpResponse::get_config(int port )
{
	int i = -1 ;
	while (++i < (int)_configs.size())
	{

		if( port == (int) _configs[i].getPort())
			break;
	}

	if( i == (int) _configs.size() )	
		 throw Not_found_404();
	return _configs[i];
}


bool HttpResponse::chek_cig_or_static(std::string file, ServerConfig server)
{

	int size = file.find('.');
	if( file.rfind('.') == std::string::npos)
		throw Not_found_404();
	std::string type =  file.substr(size,file.size()); 
	size = file.rfind('/');
	if(  file.rfind('/') == std::string::npos)	
		throw Not_found_404();
	std::string path = file.substr(0,size);	
	if(path.rfind('/') != std::string::npos )
		path +=	"/";
	path += "*"+type;
	T_MSG(file << ":" <<  path, YELLOW);
	if(server.getLocMap()[path]._cgi_pass != "" )
	{
		_pg =  server.getLocMap()[path]._cgi_pass;
		return true;	
	}
	return (false);
}

std::string HttpResponse::get_folder_index( ServerConfig conf, Cgi &cgi)
{

	std::map<std::string, LocationConfig>	_locations = conf.getLocMap();
	std::map<std::string , LocationConfig>::iterator it = _locations.begin();
	std::string file = "";
	while (it != _locations.end()) 
	{	
		try
		{

			if(it->second._cgi_pass != "")
			{
			   file = "HTTP/1.1 200 OK\r\n";
			   return (file  += cgi.execute( HttpParser::get_request_msg(), it->second._cgi_pass));
			}
			else if(  it->second.getRoot().find('.') == std::string::npos || it->second.getRoot().rfind('.') < it->second.getRoot().rfind('/'))
			{		
			   return (file = HttpResponse::open_static_file(it->second.getRoot() + "/index.html"));	
			}
		}
		catch(std::exception &e)
		{
		  	
		}
		++it;
	}
	throw  Not_found_404();
	return "";	
}

std::string HttpResponse::request_and_response(std::string request)
{
	int error;
	std::string response;
	std::string path = "";
	HttpParser::_http_page_error = 0;
	ServerConfig config;
	Cgi cgi;
	_pg = "";
	

	T_MSG("Start request", YELLOW)
	try
	{
		config = get_config(8022);
		HttpParser::new_request(request);
		cgi.create_env(_env, HttpParser::get_request_env());

		T_MSG(  "_pach is = "<< HttpParser::_pach_info, YELLOW);
		if( HttpParser::_pach_info == "/")
		{
			response = get_folder_index(config,cgi);
		}
		else if (chek_cig_or_static(HttpParser::_pach_info, config))
		{
			// execute in exeve		
			response = "HTTP/1.1 200 OK\r\n";
			response += cgi.execute( HttpParser::get_request_msg(), _pg);
		}
		else
		{
			// open static file
			path = rediect_path(HttpParser::_pach_info);
			response = HttpResponse::open_static_file(path);
		}
	}
	catch (std::exception &e)
	{
		error = std::atoi(e.what());

		T_MSG("Finich request - error:"  << e.what()  , RED);

		try
		{
			if(!config.getErrorPage(error).empty())
				return  response = HttpResponse::open_static_file(config.getErrorPage(error));
		}
		catch(std::exception &d)
		{

			return (gener_erro_page(HttpParser::_http_page_error, d.what()));
		}		
	}

	T_MSG("Finich request \n\n", GREEN)
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
