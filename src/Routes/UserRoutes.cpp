#include "UserRoutes.hpp"
#include "../CustomException.hpp"
#include "../Models/User.hpp"
#include "../helpers.hpp"
#include <exception>
void userRoutes(crow::App<> &app, Database &db) {

  CROW_ROUTE(app, "/registeruser")
      .methods("POST"_method)([&db](const crow::request &req) {
        try {
          auto jsonBody = crow::json::load(req.body);
          if (!jsonBody)
            return crow::response(
                crow::status::BAD_REQUEST); // same as crow::response(400)

          std::string username = (std::string)jsonBody["username"];
          std::map<std::string, std::string> *foundUserData =
              db.findUser(username);

          if (foundUserData) {
            delete foundUserData;
            throw CustomException((char *)"User already exists");
          }
          // todo: test email
          // todo: set json data to create new user;

          return crow::response(crow::json::wvalue(jsonBody));
        } catch (CustomException &e) {
          nlohmann::json errorMessage = createProperErrorMessage(e.what(), 401);
          // todo: ad status code
          return crow::response((errorMessage.dump()));
        } catch (const std::exception &ex) {
          return crow::response(crow::json::wvalue(ex.what()));
        } catch (...) {
          return crow::response(crow::json::wvalue("There was a problem"));
        }
      });
}
