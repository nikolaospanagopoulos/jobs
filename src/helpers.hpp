#pragma once
#include "json.hpp"
#include <string>

nlohmann::json createProperErrorMessage(const std::string message,
                                        const int statusCode);
