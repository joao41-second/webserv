/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:03:54 by jperpct           #+#    #+#             */
/*   Updated: 2025/10/09 12:06:39 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/config.hpp"
#include <http/HttpResponse.hpp>
#include "test.hpp"


void config_and_http_implemente( int argc ,char ** argv,char**env)
{
	(void)argc;
	(void)argv;
	(void)env;
	std::string conf = "_configtest/youpi.conf";
	Config config("_configtest/youpi.conf");
	
	
}


void HTTP_test_request()
{

	std::string pasta = "./HTTP_request_files";  // caminho da pasta
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(pasta.c_str())) == NULL) {
        perror("opendir");
        return; 
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        // Ignorar "." e ".."
        if (std::string(entry->d_name) == "." || std::string(entry->d_name) == "..")
            continue;

        std::string path = pasta + "/" + entry->d_name;

	 T_MSG( "Abrindo: " << path,BWHITE);

        std::ifstream file(path.c_str());
        if (!file.is_open()) {
            std::cerr << "Erro ao abrir: " << path << std::endl;
            continue;
        }

        std::string linha, conteudo;
        while (std::getline(file, linha))
            conteudo += linha + "\n";

        file.close();
	try{
		HttpResponse ok;

		HTTP_MSG("what" <<   ok.request_and_response(conteudo));
	}
	catch(std::exception &e)
	{
		std::cout << RED << "error: "<< e.what() << RESET << std::endl;
	}
    }
    closedir(dir);
}


int main(int argc ,char ** argv,char**env) 
{
	//HTTP_test_parser();	
 //	test_httprespons();
	(void)argv;
	(void)argc;
	(void)env;
	//execute(env);
	config_and_http_implemente(argc,argv,env);
	HTTP_test_request();
        return 0;
}



