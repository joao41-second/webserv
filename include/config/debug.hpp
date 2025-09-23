/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:55:56 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/23 15:30:38 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/color.hpp>

#define TESTER 1

#define DEBUG_HTTP 0

#define DEBUG_CGI 0




#if  TESTER
    #define T_MSG(x,color) std::cerr << color  << x << RESET <<  std::endl;
#else
#endif
