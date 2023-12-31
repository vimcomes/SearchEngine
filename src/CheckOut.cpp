//
// Created by vimcomes on 12.09.2023.
//

#include "CheckOut.h"
#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "SearchServer.h"
#include "CustomExceptions.h"
#include "WordHandler.h"




// Print program name, version and max_responses value
void printProgramName(nlohmann::json &config) {
    std::cout << "Started execution ";

    if (config["config"].contains("name")) {
        std::cout << config["config"]["name"].get<std::string>();
    }

    if (config["config"].contains("version")) {
        std::cout << " v" << config["config"]["version"];
    }
    std::cout << std::endl;

    if (config["config"].contains("max_responses")) {
        std::cout << "Max responses: " << config["config"]["max_responses"] << std::endl;
    }
}

// Checking config
void checkConfig(const std::string &configPath) {
    std::ifstream inFile(configPath);

    if (!inFile.is_open()) {
        throw ConfigFileIsMissing();
    }

    nlohmann::json inConfig = nlohmann::json::parse(inFile);
    inFile.close();

    if (!inConfig.contains("config")) {
        throw ConfigFileIsEmpty();
    }

    printProgramName(inConfig);
}

// Checking request file
void checkRequests(const std::string &requestsPath) {
    std::ifstream inFile(requestsPath);

    if (!inFile.is_open()) {
        throw RequestsFileIsMissing();
    }

    nlohmann::json inRequests = nlohmann::json::parse(inFile);
    inFile.close();

    if (!inRequests.contains("requests") || inRequests["requests"].empty()) {
        throw RequestsFileIsEmpty();
    }
}


// Main check
bool isReadyToStart() {
    try {
        checkConfig("..\\config.json");
        checkRequests("..\\requests.json");
        return true;
    }
    catch (const ConfigFileIsMissing &exception) {
        std::cerr << exception.what() << std::endl;
        return false;
    }
    catch (const ConfigFileIsEmpty &exception) {
        std::cerr << exception.what() << std::endl;
        return false;
    }
    catch (const RequestsFileIsMissing &exception) {
        std::cerr << exception.what() << std::endl;
        return false;
    }
    catch (const RequestsFileIsEmpty &exception) {
        std::cerr << exception.what() << std::endl;
        return false;
    }
}

// Output
void printResult(const std::vector<std::vector<RelativeIndex>> &answers) {
    std::cout << std::endl;

    for (int i = 0; i < answers.size(); ++i) {
        std::cout << "request" << WordHandler::getPositionNumber(i + 1) << ":" << std::endl;

        if (answers[i].empty())
            std::cout << "  result: false" << std::endl;
        else {
            std::cout << "  result: true" << std::endl;
            std::cout << "  relevance:" << std::endl;
        }

        for (auto j : answers[i])
            std::cout << "    docID: " << j.docId << ", rank: " << j.rank << std::endl;

        std::cout << std::endl;
    }
}
