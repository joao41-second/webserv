/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cereais <cereais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:55:56 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/14 14:56:13 by cereais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.hpp"

#define TESTER 1

#define DEBUG_HTTP 1

#define DEBUG_CGI 1




#if  TESTER
    #define T_MSG(x,color) std::cerr << color  << x << RESET <<  std::endl;
#else
#endif
