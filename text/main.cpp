/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperpct <jperpect@student.42porto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:03:54 by jperpct           #+#    #+#             */
/*   Updated: 2025/09/24 11:19:36 by jperpct          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "config/color.hpp"
#include <core/Server.hpp>
#include <config/ServerConfig.hpp>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>
#include <dirent.h>
#include <config/debug.hpp>

void HTTP_test_parser()
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
		HttpParser::new_request(conteudo);
	}
	catch(std::exception &e)
	{
		std::cout << RED << "error: "<< e.what() << RESET << std::endl;
	}
    }
    closedir(dir);
}



int main() {
	HTTP_test_parser();	
        return 0;
}



