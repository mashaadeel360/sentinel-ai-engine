#pragma once
#include <string>

class IDS {
public:
    IDS();
    bool detectAnomaly(const std::string& state);
};
