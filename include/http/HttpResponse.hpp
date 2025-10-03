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


#include <string>
#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <config/debug.hpp>
#include <http/HttpParser.hpp>


class HttpResponse
{

	private:
		int size_max;
	public:
		bool _request_status;
		HttpResponse();
		~HttpResponse();
		std::string request_and_response(std::string request);
		std::string open_static_file(std::string feile);
};


#endif


