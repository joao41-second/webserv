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
#include <unistd.h>


int 		HttpResponse::size_max 		= 50000;
char ** 	HttpResponse::_env;
std::vector<ServerConfig> 		HttpResponse::_configs;
std::map<std::string,std::string> 	HttpResponse::_types;

HttpResponse::HttpResponse():_parser(this),cgi(this,&_parser)
{
		this->_new_request = false;
		this->_new_response = false;
		this->_new_request = false;
		this->_pg = "";
	//	this->_new_response = "";
		this->_request_status = "";

}
HttpResponse::~HttpResponse()
{

		this->_new_request = false;
		this->_new_response = false;
		this->_new_request = false;
		this->_pg = "";
	//	this->_new_response = "";
		this->_request_status = "";
}


HttpResponse & HttpResponse::operator=(const HttpResponse & var)
{
	if(this != &var )
	{
		this->_new_request = var._new_request;
		this->_pg = var._pg;
		this->_parser = var._parser;
		this->cgi = var.cgi;
		this->_new_response = var._new_response;
		this->_request_status = var._request_status;

		return  *this;
	}
	return *this;
}
bool HttpResponse::get_chunks_status()
{
	return(_new_request);
}


bool HttpResponse::get_chunks_status_response()
{
	HTTP_MSG("BODY REQUEST IS =" << _new_request);
	return(_new_response);
}

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
	std::string 		request = "HTTP/1.1 200 OK\r\n";
	size_t 			size_  = file.rfind('.');
	std::string 		type_file = "";
	char 			buffer[1024];
	int 			read_bits;
	int 			size = 100000;
	static int 		fd = -1;
	std::string 		body = "";
	static std::string 	temp;
	static bool 		loop = true;

	T_MSG("start_open_file = " << file, YELLOW);

	if(size_ != std::string::npos)
	 		type_file = file.substr(size_,file.size());		 
	_request_status = false;	

	if(HttpResponse::_new_response == false)
	{
		HTTP_MSG("id is " << fd);
		if((fd = open(file.c_str(),O_RDWR , 0644) )== -1)
			throw Not_found_404();
	}

	body = temp;

	while ((read_bits = read(fd,buffer,1024)) > 0)
	{
		body.append(buffer,read_bits);
		if((int)body.size() > size)
			break;
	}
	if(read_bits != 0 && loop == true)
	{
		_request_status = true;	
		loop = false;
		HttpResponse::_new_response = true;
		request += "Transfer-Encoding: chunked\r\n";
		temp = body;
		body = "";
	}
	else if(read_bits == 0 && loop == true )
	{
		std::stringstream ss;
		ss << body.size();
		request += "Content-Length: " + ss.str() + "\r\n";
	}
	else 
	{
		request = "0/r/n/r/n";
		if(body.size() == 0)
		{
			_request_status = false;
			close(fd);
			fd = -1;
			HttpResponse::_new_response = false;
			return (request);
		}
		_request_status = true;	
		HttpResponse::_new_response = true;
		request = body.substr(0,size);
		if((int)body.size() > size)
			temp = body.substr(size,body.size());
		else
			temp = "";
		std::stringstream ss;
		ss << request.size();
		request = ss.str() + "\r\n" +request + "\r\n";
		return (request);
	}
		
	if(!_types[type_file].empty())

		request += "Content-Type: " + _types[type_file] +"\n";
	else
	{
		//TODO this vereficasion no finic
		request += "Content-Disposition: attachment; filename= " +   file+ '\n' ;
		request += "Content-Type: application/" + file.substr(file.size() - 4, file.size()) + ";\r\n";
	}	
	request += "Connection: keep-alive\r\n\n";

	if(read_bits == 0)
	{
		request += body+ "\r\n\r\n";
		close(fd);
		fd = -1;
	}
	T_MSG("end_open_file", YELLOW);
	return (request);
}

std::string HttpResponse::rediect_path(std::string file_path,int port)
{
	std::string 	file;
	std::string 	path;
	int 		size;	
	int 		i = -1;

	_parser._host.find(':');
	if(port == 0)
		throw Not_found_404();
	while (++i < (int)_configs.size())
		if( port == (int) _configs[i].getPort())
			break;
	std::map<std::string, LocationConfig>	_locations = _configs[i].getLocMap();
	size = file_path.rfind('/'); 
	file = file_path.substr(size, file_path.size());
	path = file_path.substr(0,size+1);
	return (search_folder_file(file, path, _locations));
}



std::string HttpResponse::search_folder_file(std::string file ,std::string path , std::map<std::string, LocationConfig> loc)
{
	std::string 	real_path = "";
	int 		size = 0;

	if( loc[path+file].getRoot() != "")
			return loc[path+file].getRoot();	
	while (path.rfind('/') != std::string::npos) {
		if( loc[path+file].getRoot() != "")
			return loc[path+file].getRoot() ;
	
		if(loc[path].getRoot() != "" )
		{
			if(_parser._methods ==  "GET")
				size = 0; 
			else  if(_parser._methods ==  "POST")
				size = 2; 
			else  if(_parser._methods ==  "DELETE")
				size = 4; 
			for(int i =0 ; i < (int)loc[path].getMethods().size();i++)
			{
				HTTP_MSG( "_methods" << loc[path].getMethods()[i] )
				if(loc[path].getMethods()[i] ==  size) 
					return( loc[path].getRoot() + file);
			}
			throw Not_Implemented_501();
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

	// TODO impemente check the path
	HTTP_MSG(file) 
	int size = file.find('.');


	if( file.rfind('.') == std::string::npos)
		throw Badd_Request_400();

	std::string type =  file.substr(size,file.size()); 
	_parser._type = type;

	size = file.rfind('/');
	if(  file.rfind('/') == std::string::npos)	
		throw Not_found_404();

	std::string path = file.substr(0,size);	

//	if(path.rfind('/') != std::string::npos )
//		path +=	"/";
	path += "/*"+type;

	HTTP_MSG("cgi " << path );

	std::map<std::string, LocationConfig>::iterator it = server.getLocMap().find(path);
	if(it != server.getLocMap().end())
	{
		_pg =  server.getLocMap()[path]._cgi_pass;
		return true;	
	}
	it = server.getLocMap().find("*"+type);
	if(!server.getLocMap()["*"+type]._cgi_pass.empty())
	{

		HTTP_MSG("cgi ---------------" );
		_pg =  server.getLocMap()[ "*"+type]._cgi_pass;
		return true;	
	}
	return (false);
}

std::string HttpResponse::get_folder_index( ServerConfig conf)
{
	//TODO lembrar de remover tambem

	std::map<std::string, LocationConfig>	_locations = conf.getLocMap();
	std::map<std::string , LocationConfig>::iterator it = _locations.begin();
	std::string file = "";
	while (it != _locations.end()) 
	{	
		try
		{

			if(it->second._cgi_pass != "")
			{
			   return ( _parser.chek_and_add_header(cgi.execute( _parser.get_request_msg(), it->second._cgi_pass),""));
			}
			else if(it->second.getRoot().find('.') == std::string::npos
					|| it->second.getRoot().rfind('.') < it->second.getRoot().rfind('/'))
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


std::string HttpResponse::Delete(std::string file)
{
    if (access(file.c_str(), F_OK) != 0) {
	    throw Not_found_404(); 
    }
    if (access(file.c_str(), W_OK) != 0) {
		throw Forbidden_403();
    }
    if (std::remove(file.c_str()) == 0) {
	return ("HTTP/1.1 204 No Content\r\n\r\n");
    } else {
	    throw Not_found_404();
    }
}


std::string HttpResponse::request_and_response(std::string request, int port)
{
	int 		error;
	std::string 	response;
	std::string 	path = "";
	ServerConfig 	config;



	_parser._http_page_error = 0;
	_pg = "";
	_parser._port = port;
	
	T_MSG("Start request\n", YELLOW)
	try
	{	

	if(HttpResponse::_new_response == true)
	{
		HTTP_MSG("raiva");
		response =  cgi.chek_and_return_chunks("NULL");
		if(_new_response == false && _new_response == false)
		{
			_parser._http_page_error = 0;
		}
			

		return (response);
	}
	
		int port_ = std::atoi(_parser._host.substr(_parser._host.find(':')+1,_parser._host.size()).c_str());

		if(port != port_)
		{
		//TODO	throw Badd_Request_400();
		}

		if(_new_request != true)
			_parser.new_request(request);
		else 
			_parser.set_request_msg(request);
		cgi._parser = &_parser;

		cgi.create_env(_env, _parser.get_request_env());
		config = get_config(port);		

		T_MSG(  "_pach is = " << _parser._pach_info << " type is =" << _parser._type  , YELLOW);

		if( _parser._pach_info == "/")
			response = get_folder_index(config);
		else if (chek_cig_or_static(_parser._pach_info, config))
		{
			_new_request = true;
			response =  _parser.chek_and_add_header(cgi.execute( _parser.get_request_msg(), _pg),"");
		}
		else
		{
			// open static file
			path = rediect_path(_parser._pach_info,port);
			if(_parser._methods == "DELETE")
				response = Delete(path);
			else
				response = HttpResponse::open_static_file(path);
		}
	}
	catch (std::exception &e)
	{
		error = _parser._http_page_error;

		T_MSG("Finich request - error: "  << e.what() << "->" <<_parser._http_page_error  , RED);

		try

		{
			if(!config.getErrorPage(error).empty())
			{
			   response = HttpResponse::open_static_file(config.getErrorPage(error));

			}
			else {
				HTTP_MSG("saida");
				return (gener_erro_page(error, e.what()));
			}

		}
		catch(std::exception &d)
		{

			
			HTTP_MSG("saida");
			try 
			{
				if(!config.getErrorPage(error).empty())
				{
				chek_cig_or_static( config.getErrorPage(error),config);
				_new_request = true;
				_parser._is_chunk = 0;
					
					return (response = _parser.chek_and_add_header(
								cgi.execute( config.getErrorPage(error), _pg),  e.what()));
				}
			}
			catch(std::exception &f)
			{
				return (gener_erro_page(error, e.what()));

			}
			}	
			return (gener_erro_page(error, e.what()));

		}		
	

	T_MSG("Finich request \n", GREEN)
	_parser._http_page_error = 0;
	return (response);
}

std::string HttpResponse::gener_erro_page(int error, std::string status)
{
	std::string response, mens;
	std::stringstream ok;
	std::stringstream size;
	ok << error;
	_new_request = false;
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
				 "<p> " + ok.str() +"</p>"
				 "</body>\n"
				 "</html>\n";
	size << mens.size();
	response += "Content-Length: " + size.str() + "\n\n";
	response += mens;
	return response;
}
