/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:23:40 by joseoliv          #+#    #+#             */
/*   Updated: 2025/09/15 19:29:20 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Quando um request é recebido e parseado:
O servidor olha para a URI do request
Procura dentro de ServerConfig.locations uma LocationConfig cujo path combine ou seja prefixo da URI.
Aplica as regras dessa location, por exemplo:
Sobrescreve o root global para aquela rota.
Decide se é CGI (cgi_pass) ou ficheiro estático.
Define o index se for diretório.

example:

server.host = "127.0.0.1";
server.port = 8080;
server.root = "./www";
server.server_name = "localhost";
*/