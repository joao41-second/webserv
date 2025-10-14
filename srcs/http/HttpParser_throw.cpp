/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser_throw.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:24:36 by jperpct           #+#    #+#             */
<<<<<<< HEAD:srcs/http/HttpParser_throw.cpp
/*   Updated: 2025/10/07 11:39:57 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
=======
/*   Updated: 2025/10/09 12:17:43 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <http/Http_thow.hpp>
#include <http/HttpParser.hpp>
>>>>>>> Parser_request_http:srcs/http/HttpParser_thorw.cpp

#include "../include/http/Http_throw.hpp"

const char *Badd_Request_400::what(void) const throw()
{
	HttpParser::_pach_info = "/400.html";
	HttpParser::_http_page_error = 400;
	return "Bad Request";
};

const char *Not_Implemented_501::what(void) const throw()
{
	HttpParser::_pach_info = "/501.html";
	HttpParser::_http_page_error = 501;
	return "Not Implemented";
};

const char *Version_Not_Supported_505::what(void) const throw()
{
	HttpParser::_pach_info = "/505.html";
	HttpParser::_http_page_error = 505;
	return "HTTP Version Not Supported";
};
const char *Not_found_404::what(void) const throw()
{
	HttpParser::_pach_info = "/404.html";
	HttpParser::_http_page_error = 404;
	return "Not Found";
}
