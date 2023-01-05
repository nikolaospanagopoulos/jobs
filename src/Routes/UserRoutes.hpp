#pragma once
#include "../Database/Database.hpp"
#include <crow.h>
void userRoutes(crow::App<> &app, Database &db);
