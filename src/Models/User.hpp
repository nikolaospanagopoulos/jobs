#pragma once
#include "../Database/Database.hpp"
#include "../json.hpp"
#include <iostream>
#include <string>
class I_User {

private:
public:
  virtual void saveUser(Database &db) = 0;
};

class User : public I_User {

public:
  std::string username;
  std::string name;
  std::string surname;
  std::string salt;
  std::string email;
  std::string hashedPassword;
  void hashPassword(const std::string &password);
  void setUserInfo(nlohmann::json &json);
  std::string getUserName();
  void saveUser(Database &db);

  virtual ~User(){};
  User(std::string username)
      : username{username}, email{}, salt{},
        hashedPassword{}, name{}, surname{} {}
  User() : User{""} {};
};

class ElevetedUser : public User {
private:
  virtual ~ElevetedUser(){};
  // todo: ElevetedUser should have more
public:
  ElevetedUser(std::string username) : User(username){};
};
