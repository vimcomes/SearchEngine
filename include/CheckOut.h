//
// Created by vimcomes on 12.09.2023.
//

#pragma once

#include "nlohmann/json.hpp"

#include "SearchServer.h"
#include "ConverterJSON.h"
#include "CustomExceptions.h"
#include "WordHandler.h"

#ifndef SEARCHENGINE_CHECKOUT_H
#define SEARCHENGINE_CHECKOUT_H

/**
 * @brief function to print Program name, version and max_responses value
 *
 * @param config
 */
void printProgramName (nlohmann::json &config);

/**
 * @brief function to check config.json file
 *
 * @param configPath
 */
void checkConfig(const std::string &configPath);

/**
 * @brief function to check request.json file
 *
 * @param requestsPath
 */
void checkRequests(const std::string &requestsPath);


/**
 * @brief Main check
 *
 * @return true or false
 */
bool isReadyToStart();

/**
 * @brief function for output the final results of work
 *
 * @param answers
 */
void printResult(const std::vector<std::vector<RelativeIndex>> &answers);

#endif //SEARCHENGINE_CHECKOUT_H
