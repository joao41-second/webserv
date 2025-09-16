/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:23:40 by joseoliv          #+#    #+#             */
/*   Updated: 2025/09/16 13:45:42 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Quando um request é recebido e parseado:
O servidor olha para a URI do request
Procura dentro das locations uma LocationConfig cujo path combine ou seja prefixo da URI.
Aplica as regras dessa location, por exemplo:
Sobrescreve o root global para aquela rota.
Decide se é CGI ou ficheiro estático.
Define o index se for diretório.

*/