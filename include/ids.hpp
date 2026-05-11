#pragma once
#include <string>
#include "logger.hpp"

class IDS {
public:
    void detect(const std::string& state, const std::string& action);
};
