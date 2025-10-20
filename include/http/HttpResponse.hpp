/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:37 by cereais           #+#    #+#             */
/*   Updated: 2025/10/18 17:19:33 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//works with HttpStatus


#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <config/Config.hpp>
#include <string>

#include <config/debug.hpp>
#include "HttpParser.hpp"


class HttpResponse
{

	private:
	  static int size_max;
	  static Config conf;
		HttpResponse();
		~HttpResponse();
	public:
		static bool _request_status;
	 	static	void set_config(Config);
		static bool chek_cig_or_static(std::string);
		static std::string return_path_use();
		static std::string rediect_path(std::string);
		static std::string request_and_response(std::string request);
		static std::string open_static_file(std::string feile);
		static std::string gener_erro_page(int error,std::string status);
};


#endif


