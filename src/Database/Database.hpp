#pragma once
#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/DriverManager.hpp>
#include <memory>

class Database {
  sql::Driver *driver;
  std::unique_ptr<sql::Connection> conn;

  void createDatabase();
  void creteUsersTable() const;

public:
  void saveUser(const std::string &passwordHash, const std::string salt,
                const std::string &username) const;
  std::map<std::string, std::string> *
  findUser(const std::string &username) const;
  Database();
  ~Database();
};
