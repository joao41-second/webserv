/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:04:44 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/26 14:38:22 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CGI_HPP
#define CGI_HPP

#include "http/HttpParser.hpp"
#include <config/debug.hpp>
#include <core/Server.hpp>
#include <string>


class Cgi
{
	private:
		std::vector<char *> _envs;
		std::string _request;
		
	public:
		Cgi();
		Cgi(const Cgi &copy);
		~Cgi();
		Cgi &operator=(const Cgi &copy);		
		bool chek_program(std::string porgram);
		void create_env(char **env,std::vector<char *> env_request, int argc);
		std::string execute(std::string _request);
};

#endif
