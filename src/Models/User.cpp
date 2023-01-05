#include "User.hpp"
#include <ctime>
#include <sstream>
#include <unistd.h>

std::string User::getUserName() {

  std::cout << username << std::endl;

  return username;
}
void User::saveUser(Database &db) {
  std::cout << "normal user save: " << std::endl;

  db.saveUser(hashedPassword, salt, username);
}

void User::hashPassword(const std::string &password) {

  std::time_t t = std::time(0);
  std::stringstream ss;
  ss << t;
  salt = ss.str();
  hashedPassword = crypt(password.c_str(), salt.c_str());
}
