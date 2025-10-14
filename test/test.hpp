#include <config/color.hpp>
#include <http/HttpResponse.hpp>
#include <core/Server.hpp>
#include <config/serverconfig.hpp>
#include <net/Socket.hpp>
#include <http/HttpParser.hpp>
#include <dirent.h>
#include <config/debug.hpp>
#include <cgi/cgi.hpp>
#include <config/config.hpp>
#include <string>

void HTTP_test_parser();

void test_httprespons();

void execute(char **env);
