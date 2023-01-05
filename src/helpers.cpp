#include "helpers.hpp"
using json = nlohmann::json;
json createProperErrorMessage(const std::string message, const int statusCode) {
  json errorJson{};
  errorJson["status"] = statusCode;
  errorJson["Error"]["message"] = message;
  return errorJson;
}
