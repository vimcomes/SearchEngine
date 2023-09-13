//
// Created by vimcomes
//

#include <string>
#include <vector>

#include "WordHandler.h"

    /**
     * @brief method to replace cap letters
    */

void WordHandler::replaceCapitalLetters(std::string &word) {
    for (char &i: word)
        if (i >= 'A' && i <= 'Z') i += 32;
}
/**
 * @brief This method chooses the unique words from the given document.
 * @param doc The document to choose the unique words from.
 * @return A vector of the unique words in the document.
 */
std::vector<std::string> WordHandler::chooseUniqueWords(const std::string &doc) {
    // Create a vector to store the unique words.
    std::vector<std::string> result;
    // Create string to store the current word being processed
    std::string word;
    // Iterate over the characters in the document.
    for (int i = 0; i < doc.size(); ++i) {
        // If the current character is a lowercase or uppercase letter, we add it to the word.
        if (doc[i] >= 'a' && doc[i] <= 'z' || doc[i] >= 'A' && doc[i] <= 'Z')
            word += doc[i];

        // If the current character is a space or newline, or if we have reached the end of the document,
        // and the word is not empty, we add the word to the list of unique words.
        if ((i == doc.size() - 1 || (doc[i] == ' ' || doc[i] == '\n')) && !word.empty()) {
            // We convert all uppercase letters in the word to lowercase.
            replaceCapitalLetters(word);

            if (result.empty())
                result.push_back(word);
            else {
                bool wordIsFind = false;

                for (int j = 0; j < result.size() && !wordIsFind; ++j)
                    if (result[j] == word)
                        wordIsFind = true;
                // If the word is not already in the list of unique words, we add it.
                if (!wordIsFind)
                    result.push_back(word);
            }
            // Clear the word.
            word.clear();
        }
    }
    return result;
}

/**
 * @brief This method gets the words from the given document.
 * @param doc The document to get the words from.
 * @return A vector of the words in the document.
 */
std::vector<std::string> WordHandler::getWords(const std::string &doc) {
    std::vector<std::string> result;
    std::string word;
    // If the current character is a lowercase or uppercase letter, we add it to the word.
    for (int i = 0; i < doc.size(); ++i) {
        if (doc[i] >= 'a' && doc[i] <= 'z' || doc[i] >= 'A' && doc[i] <= 'Z')
            word += doc[i];

        // If the current character is a space or newline, or if we have reached the end of the document,
        // and the word is not empty, add the word to the list of words.
        if ((i == doc.size() - 1 || (doc[i] == ' ' || doc[i] == '\n')) && !word.empty()) {
            replaceCapitalLetters(word);
            result.push_back(word);
            word.clear();
        }
    }

    return result;
}

/**
 * @brief This function returns the position number in a string, with leading zeros if necessary.
 * @param number The position number to convert.
 * @return A string representation of the position number.
 */
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

