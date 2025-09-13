/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:32 by cereais           #+#    #+#             */
/*   Updated: 2025/09/13 19:19:43 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
transform a raw HTTP request:

GET /index.html HTTP/1.1\r\n
HOST: localhost:8080\r\n
User-Agent: curl/7.68.0\r\n
Accept: * / * \r\n
\r\n

into this variables in this class:

method					= "Get"
uri						= "/index.html"
version					= "HTTP/1.1"
(map<string, string> of headers)
headers[host]			= "localhost:8080"
headers["user-Agent"]	= "curl/7.68.0"
hearders["Accept"]		= "* / *"
body					= ""

*/