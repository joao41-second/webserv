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

#include <dirent.h>


int 		HttpResponse::size_max 		= 50000;
char ** 	HttpResponse::_env;
std::vector<ServerConfig> 		HttpResponse::_configs;
std::map<std::string,std::string> 	HttpResponse::_types;

HttpResponse::HttpResponse() 
{
		this->_new_request = false;
		this->_new_response = false;
		this->_new_request = false;
		this->_pg = "";
	//	this->_new_response = "";
		this->_request_status = false;
		this->is_path = false;

}
HttpResponse::~HttpResponse()
{

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

void HttpResponse::set_fd(int i)
{
 fd = i;
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



std::string HttpResponse::rediect_path(std::string file_path,int port)
{
	std::string 	file;
	std::string 	path;
	int 		size;	
	int 		i = -1;

	_parser->_host.find(':');
	if(port == 0)
		throw Not_found_404();
	while (++i < (int)_configs.size())
		if( port == (int) _configs[i].getPort())
			break;
	std::map<std::string, LocationConfig>	_locations = _configs[i].getLocMap();
	size = file_path.rfind('/'); 
	HTTP_MSG("find pat  = " << file_path );
	file = file_path.substr(size+1, file_path.size());
	path = file_path.substr(0,size);
	return (search_folder_file(file, path, _locations));
}



std::string HttpResponse::search_folder_file(std::string file ,std::string path , std::map<std::string, LocationConfig> loc)
{
	std::string 	real_path = "";
	int 		size = 0;
	
	if (path == "")
		path ="/";
	if(file[0] != '/')
		file = "/" + file; 
	if( loc[path+file].getRoot() != "")
			return loc[path+file].getRoot();	
	while (path.rfind('/') != std::string::npos) {
		if( loc[path+file].getRoot() != "")
			return loc[path+file].getRoot() ;
	
		if(loc[path].getRoot() != "" )
		{
			if(_parser->_methods ==  "GET")
				size = 0; 
			else  if(_parser->_methods ==  "POST")
				size = 2; 
			else  if(_parser->_methods ==  "DELETE")
				size = 4; 
			else  if(_parser->_methods ==  "HEAD")
				size = HEAD; 
			for(int i =0 ; i < (int)loc[path].getMethods().size();i++)
			{
				HTTP_MSG( "_methods = " << loc[path].getMethods()[i]  << " path= "<< path << " file = "<< file )
				//if(is_path == true)
					//if(loc[path].getMethods()[i] ==  size) 
					//	return( loc[path].getRoot() );
				if(loc[path].getMethods()[i] ==  size) 
				{
					return( loc[path].getRoot() + file);
				}
			}
			throw Method_Not_Allowed_405();
		}
		size = path.rfind('/');
		file = path.substr(size,path.size()-1) + file;
		path = path.substr(0,size);

		//TODO duble alias not work
	}


	return("./index.html");
}

 ServerConfig HttpResponse::get_config(int port )
{
	int i = -1 ;
	bool not_port = true;
	while (++i < (int)_configs.size())
	{
		if( port == (int) _configs[i].getPort())\
		{
			not_port = false;		
			break;
		}
	}
	HTTP_MSG("index of config is " << i );
	if( not_port == true)	
		 throw Not_found_404();
	return _configs[i];
}


bool HttpResponse::chek_cig_or_static(std::string file, ServerConfig server)
{

	// TODO impemente check the path
	HTTP_MSG(file) 
	 if(server.getLocMap().find(file) != server.getLocMap().end())
	 {
		 is_path = true;
		 return false;	
	 }

	int size = file.find('.');


	if( file.rfind('.') == std::string::npos)
	{
		 is_path = true;
		 return false;	

	}

	std::string type =  file.substr(size,file.size()); 
	_parser->_type = type;

	size = file.rfind('/');
	if(  file.rfind('/') == std::string::npos)	
		throw Not_found_404();

	std::string path = file.substr(0,size);	
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

		_pg =  server.getLocMap()[ "*"+type]._cgi_pass;
		return true;	
	}
	return (false);
}


void HttpResponse::chek_valid_request_methods(std::string path)
{
	int i= -1;
	int size = 0;
	while (++i < (int)_configs.size())
		if(_parser->_port  == (int) _configs[i].getPort())
			break;
	std::map<std::string, LocationConfig>	loc = _configs[i].getLocMap();

			if(_parser->_methods ==  "GET")
				size = 0; 
			else  if(_parser->_methods ==  "POST")
				size = 2; 
			else  if(_parser->_methods ==  "DELETE")
				size = 4; 
			else  if(_parser->_methods ==  "HEAD")
				size = HEAD; 			
			else 
				throw Method_Not_Allowed_405();
				
			for(int i =0 ; i < (int)loc[path].getMethods().size();i++)
			{
				HTTP_MSG( "_methods" << loc[path].getMethods()[i] )
				if(loc[path].getMethods()[i] ==  size) 
					return;
			}

			_parser->_methods_allow = loc[path].getMethods();
			throw Method_Not_Allowed_405();


}

std::string HttpResponse::get_folder_index( ServerConfig conf)
{
	//TODO lembrar de remover tambem
	std::map<std::string, LocationConfig>	_locations = conf.getLocMap();
	std::map<std::string , LocationConfig>::iterator it = _locations.begin();
	std::string file = "";

	chek_valid_request_methods("/");

	while (it != _locations.end()) 
	{	
		try
		{
			if(it->second._cgi_pass != "")
			{
			   return ( _parser->chek_and_add_header(cgi->execute( _parser->get_request_msg(), it->second._cgi_pass,&_new_request),""));
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
	throw Director_Open_200();
	
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


	T_MSG("Start request\n", YELLOW)


	HttpParser::_http_page_error = 0;
	_pg = "";
	_parser->_port = port;

	
	try
	{	
		 ServerConfig config = get_config(port);		

	if(_new_response == true)
	{
		HTTP_MSG( "_new_response is true")

		response =  cgi->chek_and_return_chunks("NULL");

		if(_new_response == false && _new_response == false)
		{
		}
		return (response);
	}	
		if(_new_request != true)
		{
			_parser->new_request(request);
		}
		else {
			HTTP_MSG( "_new_request is false")
			_parser->set_request_msg(request);
		}
	
		cgi->create_env(_env, _parser->get_request_env());

		T_MSG(  "_pach is = " << _parser->_pach_info << " type is =" << _parser->_type  , YELLOW);

		if( _parser->_pach_info == "/")
			response = get_folder_index(config);

		else if (chek_cig_or_static(_parser->_pach_info, config))
		{
			_new_request = true;
			
			response =  _parser->chek_and_add_header(cgi->execute( _parser->get_request_msg(), _pg,&_new_request),"");
		}
		else
		{
			// open static file
			HTTP_MSG("open static file ")
			path = rediect_path(_parser->_pach_info,port);
			if(is_path == true)
				response = HttpResponse::open_static_path(path);
			else if(_parser->_methods == "DELETE")
				response = Delete(path);
			else if(_parser->_methods == "POST")
				save_file_post(path, _parser->get_request_msg());
			else
				response = HttpResponse::open_static_file(path);
		}
	}
	catch (std::exception &e)
	{

		e.what();
		error = HttpParser::_http_page_error;

		T_MSG("Finich request - error: "  << e.what() << "->" << error  , RED);

		try
		{

			ServerConfig config = get_config(port);		
			if( !config.getErrorPage(error).empty())
			{
			  return( response = HttpResponse::open_static_file(config.getErrorPage(error)));
			}
			else {
				
				return (gener_erro_page(error, e.what()));
			}
		}
		catch(std::exception &d)
		{

			try 
			{
				ServerConfig config = get_config(port);		
				if(!config.getErrorPage(error).empty())
				{
				chek_cig_or_static( config.getErrorPage(error),config);
				_new_request = true;
				_parser->_is_chunk = 0;	
					return (response = _parser->chek_and_add_header(
								cgi->execute( config.getErrorPage(error), _pg,&_new_request),  e.what()));
				}
			}
			catch(std::exception &f)
			{

				return (gener_erro_page(error, e.what()));

			}
			}	
			return (gener_erro_page(error, e.what()));

		}		
	

	T_MSG("Finich request _new_request  = " << _new_request << " _new_response = " << _new_response , GREEN)
	return (response);
}

