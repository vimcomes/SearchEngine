//
// Created by vimcomes
//

#pragma once

#include <exception>

class ConfigFileIsMissing : public std::exception {
public:
    const char *what() const noexcept override;
};

class ConfigFileIsEmpty : public std::exception {
public:
    const char *what() const noexcept override;
};

class RequestsFileIsMissing : public std::exception {
public:
    const char *what() const noexcept override;
};

class RequestsFileIsEmpty : public std::exception {
public:
    const char *what() const noexcept override;
};