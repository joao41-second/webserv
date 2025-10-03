/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:03:54 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/03 16:36:30 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/config.hpp"
#include "test.hpp"


void config_and_http_implemente( int argc ,char ** argv,char**env)
{
	(void)argc;
	(void)argv;
	(void)env;
	std::string conf = "_configtest/youpi.conf";
	Config config("_configtest/youpi.conf");
}


int main(int argc ,char ** argv,char**env) 
{
//	HTTP_test_parser();	
// 	test_httprespons();
	(void)argv;
	(void)argc;
	//execute(env);
	config_and_http_implemente(argc,argv,env);
        return 0;
}



