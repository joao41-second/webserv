/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:49:50 by joseoliv          #+#    #+#             */
/*   Updated: 2025/09/16 13:50:02 by cereais          ###   ########.fr       */
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

example of config file:

server {
    listen 127.0.0.1:8080;
    server_name localhost;

    root ./www;
    index index.html;

    client_max_body_size 10M;

    error_page 404 ./www/errors/404.html;
    error_page 500 ./www/errors/500.html;

    location / {
        root ./www/html;
        index index.html;
    }

    location /uploads {
        root ./www/uploads;
    }

    location /cgi-bin/ {
        cgi_pass /usr/bin/python3;
    }
}

*/
