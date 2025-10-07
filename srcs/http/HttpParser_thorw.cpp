/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser_thorw.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:24:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/24 15:40:38 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <http/Http_thow.hpp>
#include <http/HttpParser.hpp>


const char *Badd_Request_400::what(void) const throw()
{
	HttpParser::_pach_info = "/400.html";
	return "400";
};

const char *Not_Implemented_501::what(void) const throw()
{
	HttpParser::_pach_info = "/501.html";
	return "501";
};

const char *Version_Not_Supported_505::what(void) const throw()
{
	HttpParser::_pach_info = "/505.html";
	return "505";
};
const char *Not_found_404::what(void) const throw()
{
	HttpParser::_pach_info = "/404.html";
	return "404";
}
