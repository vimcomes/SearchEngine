//
// Created by vimcomes.
//

#pragma once

#ifndef SEARCH_ENGINE_WORDHANDLER_H
#define SEARCH_ENGINE_WORDHANDLER_H

class WordHandler {
public:
    static void replaceCapitalLetters(std::string &word);

    static std::vector<std::string> chooseUniqueWords(const std::string &doc);

    static std::vector<std::string> getWords(const std::string &doc);

    static std::string getPositionNumber(int number);
};

#endif //SEARCH_ENGINE_WORDHANDLER_H
