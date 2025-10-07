/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser_throw.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:24:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/07 11:39:57 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/http/Http_throw.hpp"

const char *Badd_Request_400::what(void) const throw()
{
	return "400";
};

const char *Not_Implemented_501::what(void) const throw()
{
	return "501";
};

const char *Version_Not_Supported_505::what(void) const throw()
{
	return "505";
};
const char *Not_found_404::what(void) const throw()
{
	return "404";
}
