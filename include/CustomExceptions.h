/**
 * Created by vimcomes
 * @file CustomException.h
 * @brief This file contains the implementation of the custom exception classes.
 */
#pragma once

#include <exception>

/**
 *@brief custom exception classes - 'missing file' and 'empty file' errors parsing for the 'config.json' and 'request.json' files
 *@return error text via exception
*/

//no comments;-) its clear to understand
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