/**
 * Created by vimcomes
 * @file ConverterJSON.h
 * @brief This file contains the implementation of the `ConverterJSON` class (header file).
 */

#pragma once

#include "SearchServer.h"

/**
 * @brief This class serve to operate with JSON files
 */
class ConverterJSON {
public:
    //default constructor
    ConverterJSON() = default;

    /**
	* @brief Get content of files
	* @return list of file with their content described
	* in config.json
	*/
    static std::vector<std::string> GetTextDocuments();

    /**
     * Read request data from request.json
     * @return contents of request.json of json datatype
    */
    static std::vector<std::string> GetRequests();

    /**
     * read max_responses value from config.json
     * @return max_responses value of config.json of json datatype
     * @return "5" if value is not specified
    */
    static int GetResponsesLimit();

    /**
     * method write search results into the answer file
     * @param answers
    */

    static void putAnswers(const std::vector<std::vector<RelativeIndex>> &answers);


private:
    /**
    * method read file addresses with some checks
    * @param list
    */
    static void GetFileAddresses(std::vector<std::string> &list);
};
