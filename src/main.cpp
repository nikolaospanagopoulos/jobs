#include "./Database/Database.hpp"
#include "./Routes/UserRoutes.hpp"
#include "CustomException.hpp"
#include "Models/User.hpp"
#include <crow.h>
#include <iostream>

int main() {

  try {
    Database db;

    db.findUser("panaras254");
  } catch (CustomException &err) {
    std::cerr << err.what() << std::endl;
  }

  //  crow::App<> app{};

  // userRoutes(app);

  // app.port(5000).multithreaded().run();
  return 0;
}
