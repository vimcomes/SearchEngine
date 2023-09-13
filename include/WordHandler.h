//
// Created by vimcomes.
//

#pragma once

#ifndef SEARCH_ENGINE_WORDHANDLER_H
#define SEARCH_ENGINE_WORDHANDLER_H

class WordHandler {
public:
    /**
    * method to replace cap letters
    */
    static void replaceCapitalLetters(std::string &word);

    /**
    * @brief This method chooses the unique words from the given document.
    * @param doc The document to choose the unique words from.
    * @return A vector of the unique words in the document.
    */
    static std::vector<std::string> chooseUniqueWords(const std::string &doc);

    /**
    * @brief This method gets the words from the given document.
    * @param doc The document to get the words from.
    * @return A vector of the words in the document.
    */
    static std::vector<std::string> getWords(const std::string &doc);

    /**
    * @brief This method returns the position number in a string, with leading zeros if necessary.
    * @param number The position number to convert.
    * @return A string representation of the position number.
    */
    static std::string getPositionNumber(int number);
};

#endif //SEARCH_ENGINE_WORDHANDLER_H
