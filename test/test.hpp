#include <config/color.hpp>
#include <http/HttpResponse.hpp>
#include <core/Server.hpp>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>
#include <dirent.h>
#include <config/debug.hpp>
#include <cgi/cgi.hpp>
#include <config/Config.hpp>
#include <string>
#include <config/color.hpp>

#define TESTER 1



void HTTP_test_parser();

void test_httprespons();

void execute(char **env);

#if  TESTER 
    #define MSG_T(x,color) std::cerr << color  << x << RESET <<  std::endl;
#else
#endif
