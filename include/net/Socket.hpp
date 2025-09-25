/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:58:14 by joseoliv          #+#    #+#             */
/*   Updated: 2025/09/25 19:22:43 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>

class Socket {
	
public:
	Socket();
	~Socket();
	Socket(const Socket& copy);
	Socket& operator=(const Socket& src);

	void	close();
};