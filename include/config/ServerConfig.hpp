/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:49:50 by joseoliv          #+#    #+#             */
/*   Updated: 2025/09/15 19:28:21 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>

class ServerConfig {
	
};

/*

Quando o servidor inicia:
O parser lê o ficheiro .conf e cria objetos ServerConfig

A Connection ou o Server usa ServerConfig para:
Saber qual root usar para ficheiros estáticos.
Saber qual server name corresponde ao header Host: do request (virtual host).
Aplicar limites globais (client_max_body_size).
Escolher error_pages personalizadas.

example:

loc1.path = "/";
loc1.index = "index.html";

||

loc2.path = "/cgi-bin/";
loc2.cgi_pass = "/usr/bin/python3";
*/