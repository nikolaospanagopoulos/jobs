#include "Database.hpp"
#include "../CustomException.hpp"
#include <iostream>

void Database::createDatabase() {
  std::string query{"CREATE DATABASE IF NOT EXISTS linkdinClone;"};
  std::unique_ptr<sql::Statement> stmt(conn->createStatement());
  std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
  std::cout << "nikos";
}

Database::Database() {
  driver = sql::mariadb::get_driver_instance();

  conn.reset(driver->connect("tcp://127.0.0.1:3306", "root", ""));
  // todo: throw exception
  conn->setSchema("linkdinClone");

  createDatabase();
  creteUsersTable();
}
Database::~Database() { conn->close(); }
void Database::creteUsersTable() const {
  std::string query{"CREATE TABLE IF NOT EXISTS users(userId INT NOT NULL "
                    "AUTO_INCREMENT, name "
                    "VARCHAR(100) NOT NULL, surname VARCHAR(100) NOT NULL ,"
                    "username VARCHAR (100) NOT NULL,"
                    "hashedPassword VARCHAR(60), salt "
                    "VARCHAR (60), PRIMARY KEY(userId))"};
  std::unique_ptr<sql::Statement> stmt(conn->createStatement());
  std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
}

void Database::saveUser(const std::string &passwordHash, const std::string salt,
                        const std::string &username) const {
  try {
    std::string query{

        "INSERT INTO users (name,passwordHash,saltHash) VALUES"

    };

    query.append("("
                 "\"" +
                 username + "\"" + "," + "\"" + passwordHash +
                 "\""
                 "," +
                 "\"" + salt + "\" );");

    std::cout << query << std::endl;
    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
  } catch (sql::SQLException &e) {
    throw CustomException((char *)e.what());
  }
}
std::map<std::string, std::string> *
Database::findUser(const std::string &username) const {
  std::map<std::string, std::string> *userMap = nullptr;
  try {
    std::string query{"SELECT * FROM users WHERE username="};
    query.append("\"" + username + "\"");

    std::unique_ptr<sql::Statement> stmt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
    userMap = new std::map<std::string, std::string>{};
    if (res->next()) {
      userMap->at("name") = res->getString("name");
      userMap->at("hashedPassword") = res->getString("hashedPassword");
      userMap->at("salt") = res->getString("salt");
      userMap->at("surname") = res->getString("surname");
      userMap->at("username") = res->getString("username");
    }
    return userMap;
  } catch (sql::SQLException &e) {
    if (userMap) {
      delete userMap;
    }
    throw CustomException((char *)e.what());
  }
}
