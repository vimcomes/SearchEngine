/**
 * Created by vimcomes
 * @file CustomException.cpp
 * @brief This file contains the implementation of the custom exception classes.
 */

#include "CustomExceptions.h"

/**
 * custom exception classes - 'missing file' and 'empty file' errors parsing for the 'config.json' and 'request.json' files
 *@return error text via exception
*/

const char *ConfigFileIsMissing::what() const noexcept {
    return "Config file is missing.";
}

const char *ConfigFileIsEmpty::what() const noexcept {
    return "Config file is empty.";
}

const char *RequestsFileIsMissing::what() const noexcept {
    return "Requests file is missing.";
}

const char *RequestsFileIsEmpty::what() const noexcept {
    return "Requests file is empty.";
}
