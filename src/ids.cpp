#include "ids.hpp"

void IDS::detect(const std::string& state, const std::string& action) {
    Logger::log(Logger::INFO, "IDS analyzing state/action pair...");

    // Placeholder logic
    if (action == "turn_left") {
        Logger::log(Logger::WARNING, "Potential anomaly detected: unusual action pattern.");
    } else {
        Logger::log(Logger::INFO, "No anomalies detected.");
    }
}
