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
    #define HTTP_MSG(x) std::cerr << "HTTP:" << x << std::endl;
#else
    #define HTTP_MSG(x) /* nada */
#endif

#define HTTP_CHUNKS 2
#define HTTP_CONTENT 1
#define HTTP_EMPTY 0


class HttpResponse;

class HttpParser
{
	protected: 
	        std::vector<std::string> env;
		std::string  mensage;
		bool 	    _request;
	private:
		void parsing_env(std::string buffer);
		void parsing_request_line(std::string buffer);	
		HttpResponse 	* _request_c;
	
	public:   
		HttpParser(HttpResponse *);
		HttpParser();
	       ~HttpParser();
		HttpParser(const HttpParser &vuale);
	      	HttpParser& operator=(const HttpParser &vuale);

	       int 	 _is_chunk;
	       std::string _type;
	       std::string _methods;
	       static std::string _pach_info; 
	       static int 	 _http_page_error;
	       std::string _host;
	       int 	 _port;
		
	      std::string 		chek_and_add_header(std::string response,std::string error);
	      void        		new_request(std::string buffer); 
	      std::string        	get_request_msg();
	      std::vector<char *>	get_request_env();
	      void 			set_request_msg(std::string);
};


#endif

 
