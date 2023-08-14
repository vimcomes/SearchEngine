//
// Created by vimcomes
//

#include "CustomExceptions.h"

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
