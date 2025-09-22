/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:35 by cereais           #+#    #+#             */
/*   Updated: 2025/09/22 14:00:33 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  HTTPPARSER_HPP
#define  HTTPPARSER_HPP
#include <config/debug.hpp>

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
	private:
		std::vector<std::string> env;
		std::string mensage;
	public: 
	      HttpParser();
	      HttpParser(const HttpParser &vuale);
	      ~HttpParser();
	      HttpParser& operator=(const HttpParser &vuale);
	      void new_request(std::string buffer); 
	      std::string get_request_msg();
		
};

#endif

 
