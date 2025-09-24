/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:55:56 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/24 11:32:47 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/color.hpp>

#define TESTER 1

#define DEBUG_HTTP 1

#define DEBUG_CGI 0




#if  TESTER
    #define T_MSG(x,color) std::cerr << color  << x << RESET <<  std::endl;
#else
#endif
