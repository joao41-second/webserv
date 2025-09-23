/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:04:44 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/23 16:10:40 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CGI_HPP
#define CGI_HPP

#include "http/HttpParser.hpp"
#include <config/debug.hpp>
#include <core/Server.hpp>


class Cgi
{
	private:

	public:
		Cgi();
		Cgi(const Cgi &copy);
		~Cgi();
		Cgi &operator=(const Cgi &copy);
		bool chek_program(std::string porgram);
		bool execute(HttpParser request);

};

#endif
