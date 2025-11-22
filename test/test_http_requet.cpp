#include "test.hpp"
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

void test_httprespons()
{
	std::string  request;
	HttpResponse ok;	
	try
	{	
	  while (ok._request_status == false)
	  {	 
 		request += ok.open_static_file("./HTTP_request_files/index.html");
	  }
	  T_MSG(request,GREEN);
	  request = "";
	  ok._request_status = false;
	  while (ok._request_status == false)
	  {
		  request += ok.open_static_file("./HTTP_request_files/index_simple.html");
	  }
	  T_MSG(request,GREEN);
	}
	catch(std::exception &e)
	{
		std::cout << RED << "error: "<< e.what() << RESET << std::endl;
	}
}


void execute(char **env)
{
	Cgi ok;

	std::vector<char *> _env;
	ok.create_env(env,_env );
 	ok.execute("ola.chg");

	T_MSG( ok.execute("ola.chg"),GREEN);
}

