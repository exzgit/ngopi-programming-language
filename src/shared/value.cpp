#include "value.hpp"

bool canConvertToInt(const std::string& str) {
    std::istringstream iss(str);
    int value;
    char c;
    if (!(iss >> value)) return false;
    if (iss >> c) return false;
    return true;
}

int strToInt(const std::string& str) {
    if (canConvertToInt(str)) {
        return std::stoi(str);
    } else {
        throw std::invalid_argument("Cannot convert to int: " + str);
    }
}

float strToFloat(const std::string& str) {
    try {
        return std::stof(str);
    } catch (const std::exception&) {
        throw std::invalid_argument("Cannot convert to float: " + str);
    }
}