#include "Server.h"

shared_ptr<Server> Server::instance = 0;
shared_ptr<thread> Server::p_serverThread = 0;