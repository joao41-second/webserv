/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:37 by cereais           #+#    #+#             */
/*   Updated: 2025/10/18 17:19:33 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//works with HttpStatus


#include "config/LocationConfig.hpp"
#include "config/ServerConfig.hpp"
#include <fcntl.h>
#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <config/Config.hpp>
#include <string>
#include <config/debug.hpp>
#include <cgi/cgi.hpp>
#include "HttpParser.hpp"


class HttpResponse
{

	private:
	  static int size_max;
	  static char **_env;
	  static std::vector<ServerConfig> _configs;
	  static ServerConfig get_config(int port);
	  static std::string _pg;
	HttpResponse();
	~HttpResponse();
	static std::string  search_folder_file(std::string file ,std::string path , std::map<std::string, LocationConfig> loc);
	static std::string  get_folder_index(ServerConfig,Cgi &cgi);
		 
	public:
		static bool _request_status;
	  	static std::map<std::string ,std::string> _types;
	 	static	void set_config(std::vector<ServerConfig>& conf, char** env);
		static bool chek_cig_or_static(std::string, ServerConfig);
		static std::string return_path_use();
		static std::string rediect_path(std::string);
		static std::string request_and_response(std::string request);
		static std::string open_static_file(std::string feile);
		static std::string gener_erro_page(int error,std::string status);
};


#endif


