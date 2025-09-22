/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:16:35 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/22 14:06:07 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HttpParser.hpp>

HttpParser::HttpParser(void)
{
	HTTP_MSG("start_parser");
	this->mensage = "";
}

HttpParser::HttpParser(const HttpParser &value)
{
	HTTP_MSG("start_parser_used_privios_HttpParser");
	this->mensage =  value.mensage;
	this->env =  value.env;
}

HttpParser& HttpParser::operator=(const HttpParser &value)
{
	HTTP_MSG("iqual operator used");
	if(&value == this)
		return (*this);
	this->mensage =  value.mensage;
	this->env =  value.env;
	return (*this);
}

HttpParser::~HttpParser()
{
	HTTP_MSG("end parser");
}

