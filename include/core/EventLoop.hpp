/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:44:16 by cereais           #+#    #+#             */
/*   Updated: 2025/09/15 18:53:18 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*

LOOP PRINCIPAL

Recebe uma lista de listening sockets (fd)

Cria estruturas internas para acompanhar:

fds de leitura

fds de escrita

fds de erro (exception)



Monitora fds usando select() / poll() / epoll().

Quando um listening socket fica pronto chama Server::acceptConnection() -> cria uma nova Connection.

Quando um client socket fica pronto para leitura chama Connection::handleRead() -> acumula dados e parseia request.

Quando um client socket fica pronto para escrita chama Connection::handleWrite()-> envia resposta parcial ou completa.

Repete tudo até o servidor ser encerrado.
*/