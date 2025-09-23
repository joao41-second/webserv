/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser_thorw.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:24:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/22 15:26:41 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HttpParser.hpp>


const char *HttpParser::Badd_Request_400::what(void) const throw()
{
	return "400";
};

const char *HttpParser::Not_Implemented_501::what(void) const throw()
{
	return "501";
};

const char *HttpParser::Version_Not_Supported_505::what(void) const throw()
{
	return "505";
};
