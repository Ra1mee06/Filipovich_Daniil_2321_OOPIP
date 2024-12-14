#pragma once
#include <exception>
#include <string>

class ExceptionHandler : public std::exception {
private:
    std::string message;

public:
    ExceptionHandler(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};
