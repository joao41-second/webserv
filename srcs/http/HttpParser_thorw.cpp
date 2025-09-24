/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpParser_thorw.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:24:36 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/24 14:30:22 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <http/Http_thow.hpp>


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
