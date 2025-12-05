/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:37 by cereais           #+#    #+#             */
/*   Updated: 2025/10/28 20:48:29 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// works with HttpStatus

#include "config/LocationConfig.hpp"
#include "config/ServerConfig.hpp"
#include <fcntl.h>
#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <config/Config.hpp>
#include <string>
#include <config/debug.hpp>


class Cgi;
class HttpParser;
class HttpResponse
{

private:
	static int size_max;
	static char **_env;
	static std::vector<ServerConfig> _configs;
	static ServerConfig get_config(int port);
	std::string _pg;


		std::string search_folder_file(std::string file, std::string path, std::map<std::string, LocationConfig> loc);
		std::string get_folder_index(ServerConfig);
		std::string Delete(std::string file);
		std::string gener_erro_page(int error, std::string status);
		std::string rediect_path(std::string,int);
		std::string return_path_use();
		bool	   chek_cig_or_static(std::string, ServerConfig);
		bool is_path;

public:
	HttpParser *_parser;
	Cgi 		*cgi;
	HttpResponse();
	~HttpResponse();
	HttpResponse & operator=(const HttpResponse &);
	 bool _new_request;
	 bool _new_response;
	 bool _request_status;
	 int fd;

	static	std::map<std::string, std::string> _types;

	static void set_config(std::vector<ServerConfig> &conf, char **env);


	void set_fd(int fd);
	std::string request_and_response(std::string request, int port);
	void chek_valid_request_methods(std::string);
	bool get_chunks_status();
 	bool get_chunks_in_response();
	bool get_chunks_status_response();

	std::string open_static_file(std::string feile );
	std::string open_static_path(std::string patc);
};

#endif
