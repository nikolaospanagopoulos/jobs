#include "../Database/Database.hpp"
int main() {

  Database db;

  db.findUser("nikos");

  //  crow::App<> app{};

  // userRoutes(app);

  // app.port(5000).multithreaded().run();
  return 0;
}
