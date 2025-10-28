/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:35 by cereais           #+#    #+#             */
/*   Updated: 2025/09/24 14:28:29 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  HTTPPARSER_HPP
#define  HTTPPARSER_HPP
#include <config/debug.hpp>

#include <exception>
#include <string>
#include <vector>
#include <iostream>


#if  DEBUG_HTTP
    #define HTTP_MSG(x) std::cerr << "HTTP: " << x << std::endl;
#else
    #define HTTP_MSG(x) /* nada */
#endif



class HttpParser
{
	protected: 
	        static std::vector<std::string> env;
		static std::string mensage;
		static bool 	    _request;
	private:
		static void parsing_env(std::string buffer);
		static void parsing_request_line(std::string buffer);
		HttpParser();
	       ~HttpParser();
		HttpParser(const HttpParser &vuale);
	      	HttpParser& operator=(const HttpParser &vuale);
	public:   
	      static std::string _type;
	      static std::string _pach_info; 
	      static	int _http_page_error;
		static std::string _host;

	      static void new_request(std::string buffer); 
	      static std::string get_request_msg();
	      static std::vector<char *> get_request_env();		
};


#endif

 
