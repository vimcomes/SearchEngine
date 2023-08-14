//
// Created by Vimcomes.
//

#include <vector>

#include "gtest/gtest.h"
#include "WordHandler.h"

TEST(TestCaseWordHandler, LetterCaseTest) {
    std::vector<std::string> words{
            "milk", "Water", "LONDON"
    };

    for (auto &word: words) {
        WordHandler::replaceCapitalLetters(word);
    }

    std::vector<std::string> expected{
            "milk", "water", "london"
    };

    ASSERT_EQ(words, expected);
}

TEST(TestCaseWordHandler, WordsTest) {
    std::string doc = "Milk water WATER milk word";

    std::vector<std::string> result = WordHandler::getWords(doc);

    std::vector<std::string> expected{
            "milk", "water", "water", "milk", "word"
    };

    ASSERT_EQ(result, expected);
}

TEST(TestCaseWordHandler, UniqueWordsTest) {
    std::string doc = "Milk water WATER milk, word";

    std::vector<std::string> result = WordHandler::chooseUniqueWords(doc);

    std::vector<std::string> expected{
            "milk", "water", "word"
    };

    ASSERT_EQ(result, expected);
}