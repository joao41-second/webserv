/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:37 by cereais           #+#    #+#             */
/*   Updated: 2025/09/26 12:22:06 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//works with HttpStatus


#include "config/config.hpp"
#include <string>
#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <config/debug.hpp>
#include <http/HttpParser.hpp>


class HttpResponse
{

	private:
		int size_max;
		Config conf;
	public:
		bool _request_status;
		HttpResponse();
		~HttpResponse();
		void set_config(Config);
		bool chek_cig_or_static(std::string);
		std::string return_path_use();
		std::string rediect_path(std::string);
		std::string request_and_response(std::string request);
		std::string open_static_file(std::string feile);
		std::string gener_erro_page(int error,std::string status);
};


#endif


