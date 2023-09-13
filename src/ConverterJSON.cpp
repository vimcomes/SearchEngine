/**
 * Created by vimcomes
 * @file ConverterJSON.cpp
 * @brief This file contains the implementation of the `ConverterJSON` class.
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "nlohmann/json.hpp"

#include "ConverterJSON.h"
#include "WordHandler.h"

/**
 * @brief Method to get content of files in config.json
 *
 * @return result
 */
std::vector<std::string> ConverterJSON::GetTextDocuments() {
    // Create a vector to store the text documents.
    std::vector<std::string> result;

    // Create a vector to store the addresses of the text documents.
    std::vector<std::string> addressList;

    // Get the addresses of the text documents.
    GetFileAddresses(addressList);

    // Iterate over the addresses in the addressList vector.
    for (auto &address: addressList) {
        // Open a file stream for the address.
        std::ifstream inFile(address);

        // Check if the file stream is open.
        if (!inFile.is_open())

            // If the file stream is not open, then drop an error message.
            std::cerr << "Text file missing: " << address << std::endl;
        else {
            // Read the contents of the file into a string stream.
            std::stringstream text;
            text << inFile.rdbuf();

            //close the file stream.
            inFile.close();

            // Add the string stream to the result vector.
            result.push_back(text.str());
        }
    }
    // Return the result vector.
    return result;
}

/**
 * @brief read data from request.json file into the vector
 *
 * @return result
 */
std::vector<std::string> ConverterJSON::GetRequests() {
    //Create vector to store the request.
    std::vector<std::string> result;
    //Open the JSON file.
    std::ifstream inFile("..\\requests.json");

    //Check if the file is open
    if (inFile.is_open()) {
        //Parse the JSON data.
        nlohmann::json inRequests;
        inFile >> inRequests;
        inFile.close();
        // Iterate over the elements of the `requests` and add each element to the vector.
        for (auto i = inRequests.find("requests")->begin(); i != inRequests.find("requests")->end(); ++i)
            result.push_back(i.value());
    }
    // Return the vector of requests.
    return result;
}

/**
 *@brief read max_responses value from config.json
 *
 * @return max_responses value of config.json of json datatype
 * @return "5" if value is not specified
 */
int ConverterJSON::GetResponsesLimit() {
    // Open the JSON file.
    std::ifstream inFile("..\\config.json");
    //Parse JSON
    nlohmann::json inConfig = nlohmann::json::parse(inFile);
    //close file
    inFile.close();
    //fork
    if (inConfig["config"].contains("max_responses"))
        return inConfig["config"]["max_responses"];
    else
        return 5;
}

/**
 *@brief method read file addresses from config.json with some checks
 *
 * @param list
 */
void ConverterJSON::GetFileAddresses(std::vector<std::string> &list) {
    // Open the JSON file.
    std::ifstream inFile("..\\config.json");

    // Check if the file is open.
    if (inFile.is_open()) {

        // Parse the JSON data.
        nlohmann::json inConfig = nlohmann::json::parse(inFile);
        inFile.close();
        // Check if the JSON data contains the `files` field.
        if (!inConfig["config"].contains("files")) {
            std::cerr << "Missing field \"files\" in config.json." << std::endl;
            return;
        }
        // Check if the `files` field is empty.
        if (inConfig["config"]["files"].empty()) {
            std::cerr << "The field \"files\" is empty. There are no addresses to documents." << std::endl;
            return;
        }
        // Iterate over the elements of the `files` field and add each element to the vector.
        for (auto i = inConfig["config"].find("files")->begin(); i != inConfig["config"].find("files")->end(); ++i)
            list.push_back(i.value());
    }
}

/**
 * brief method write search results into the answer.json file
 *
 * @param answers
 */
void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>> &answers) {
    // Create an output file stream for the answers.
    std::ofstream outFile("..\\answers.json");
    // Create a JSON object to store the answers.
    nlohmann::json outAnswers;
    // Iterate over the requests.
    for (int i = 0; i < answers.size(); ++i) {
        // Get the request number.
        std::string request = "request" + WordHandler::getPositionNumber(i + 1);
        // If the request has no answers, then set the `result` field to false.
        if (answers[i].empty())
            outAnswers["answers"][request]["result"] = false;
        else
            // If the request has answers, then set the `result` field to true.
            outAnswers["answers"][request]["result"] = true;
        // Iterate over the answers for the request.
        for (int j = 0; j < answers[i].size(); ++j) {
            // Get the position number.
            std::string position = "position" + WordHandler::getPositionNumber(j + 1);
            // Set the fields for the answer.
            outAnswers["answers"][request]["relevance"][position]["docID"] = answers[i][j].docId;
            outAnswers["answers"][request]["relevance"][position]["rank"] = answers[i][j].rank;
        }
    }
    // Write the JSON object to the output file stream.
    outFile << outAnswers.dump(4);
    // Close the output file stream.
    outFile.close();
}



