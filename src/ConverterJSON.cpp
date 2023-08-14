//
// Created by vimcomes
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "nlohmann/json.hpp"

#include "ConverterJSON.h"
#include "WordHandler.h"

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> result;
    std::vector<std::string> addressList;
    GetFileAddresses(addressList);

    for (auto &address: addressList) {
        std::ifstream inFile(address);

        if (!inFile.is_open())
            std::cerr << "Text file missing: " << address << std::endl;
        else {
            std::stringstream text;
            text << inFile.rdbuf();
            inFile.close();
            result.push_back(text.str());
        }
    }

    return result;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> result;
    std::ifstream inFile("requests.json");

    if (inFile.is_open()) {
        nlohmann::json inRequests;
        inFile >> inRequests;
        inFile.close();

        for (auto i = inRequests.find("requests")->begin(); i != inRequests.find("requests")->end(); ++i)
            result.push_back(i.value());
    }

    return result;
}


int ConverterJSON::GetResponsesLimit() {
    std::ifstream inFile("config.json");

    nlohmann::json inConfig = nlohmann::json::parse(inFile);
    inFile.close();

    if (inConfig["config"].contains("max_responses"))
        return inConfig["config"]["max_responses"];
    else
        return 5;
}

void ConverterJSON::GetFileAddresses(std::vector<std::string> &list) {
    std::ifstream inFile("config.json");

    if (inFile.is_open()) {
        nlohmann::json inConfig = nlohmann::json::parse(inFile);
        inFile.close();

        if (!inConfig["config"].contains("files")) {
            std::cerr << "Missing field \"files\" in config.json." << std::endl;
            return;
        }

        if (inConfig["config"]["files"].empty()) {
            std::cerr << "The field \"files\" is empty. There are no addresses to documents." << std::endl;
            return;
        }

        for (auto i = inConfig["config"].find("files")->begin(); i != inConfig["config"].find("files")->end(); ++i)
            list.push_back(i.value());
    }
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>> &answers) {
    std::ofstream outFile("answers.json");
    nlohmann::json outAnswers;

    for (int i = 0; i < answers.size(); ++i) {
        std::string request = "request" + WordHandler::getPositionNumber(i + 1);

        if (answers[i].empty())
            outAnswers["answers"][request]["result"] = false;
        else
            outAnswers["answers"][request]["result"] = true;

        for (int j = 0; j < answers[i].size(); ++j) {
            std::string position = "position" + WordHandler::getPositionNumber(j + 1);
            outAnswers["answers"][request]["relevance"][position]["docID"] = answers[i][j].docId;
            outAnswers["answers"][request]["relevance"][position]["rank"] = answers[i][j].rank;
        }
    }

    outFile << outAnswers.dump(4);

    outFile.close();
}



