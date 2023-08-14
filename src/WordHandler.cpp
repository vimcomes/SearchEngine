//
// Created by vimcomes
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "WordHandler.h"

void WordHandler::replaceCapitalLetters(std::string &word) {
    for (char &i: word)
        if (i >= 'A' && i <= 'Z') i += 32;
}

std::vector<std::string> WordHandler::chooseUniqueWords(const std::string &doc) {
    std::vector<std::string> result;
    std::string word;

    for (int i = 0; i < doc.size(); ++i) {
        if (doc[i] >= 'a' && doc[i] <= 'z' || doc[i] >= 'A' && doc[i] <= 'Z')
            word += doc[i];

        if ((i == doc.size() - 1 || (doc[i] == ' ' || doc[i] == '\n')) && !word.empty()) {
            replaceCapitalLetters(word);

            if (result.empty())
                result.push_back(word);
            else {
                bool wordIsFind = false;

                for (int j = 0; j < result.size() && !wordIsFind; ++j)
                    if (result[j] == word)
                        wordIsFind = true;

                if (!wordIsFind)
                    result.push_back(word);
            }
            word.clear();
        }
    }
    return result;
}

std::vector<std::string> WordHandler::getWords(const std::string &doc) {
    std::vector<std::string> result;
    std::string word;

    for (int i = 0; i < doc.size(); ++i) {
        if (doc[i] >= 'a' && doc[i] <= 'z' || doc[i] >= 'A' && doc[i] <= 'Z')
            word += doc[i];

        if ((i == doc.size() - 1 || (doc[i] == ' ' || doc[i] == '\n')) && !word.empty()) {
            replaceCapitalLetters(word);
            result.push_back(word);
            word.clear();
        }
    }

    return result;
}

std::string WordHandler::getPositionNumber(const int number) {
    std::string result;

    if (number < 10)
        result = "00" + std::to_string(number);
    else if (number < 100)
        result = "0" + std::to_string(number);
    else
        result = std::to_string(number);

    return result;
}

