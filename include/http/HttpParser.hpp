/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:35 by cereais           #+#    #+#             */
/*   Updated: 2025/09/22 15:23:25 by jperpct          ###   ########.fr       */
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
		int _http_page_error;
	private:
		std::vector<std::string> env;
		std::string mensage;
		bool 	    _request;
		void parsing_env(std::string buffer);
		void parsing_request_line(std::string buffer);
	public: 
	      HttpParser();
	      HttpParser(const HttpParser &vuale);
	      ~HttpParser();
	      HttpParser& operator=(const HttpParser &vuale);
	      void new_request(std::string buffer); 
	      std::string get_request_msg();

	class   Badd_Request_400 : public std::exception 
	{
		public:
			virtual const char *what()const throw();
	};

	class   Not_Implemented_501 : public std::exception
	{
		public:
			virtual const char *what()const throw();
	};
	class   Version_Not_Supported_505 : public std::exception
	{
		public:
			virtual const char *what()const throw();
	};
		
};

#endif

 
