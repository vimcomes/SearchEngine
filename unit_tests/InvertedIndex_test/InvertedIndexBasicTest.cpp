//
// Created by Vimcomes.
//

#include <vector>

#include "gtest/gtest.h"
#include "InvertedIndex.h"

void TestInvertedIndexFunctionality(
        const std::vector<std::string> &docs,
        const std::vector<std::string> &requests,
        const std::vector<std::map<size_t, size_t>> &expected) {
    std::vector<std::map<size_t, size_t>> result;
    InvertedIndex index;

    index.UpdateDocumentBase(docs);

    for (auto &request: requests) {
        std::map<size_t, size_t> wordCount = index.GetWordCount(request);
        result.push_back(wordCount);
    }

    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, BasicTest) {
    const std::vector<std::string> docs = {
            " london is the capital of great britain ",
            " big ben is the nickname for the Great bell of the striking clock "
    };
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::map<size_t, size_t>> expected = {
            {{0, 1}},
            {{0, 1}, {1, 3}}
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, BasicTest2) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
    const std::vector<std::map<size_t, size_t>> expected = {
            {{0, 4}, {1, 1}, {2, 5}},
            {{0, 3}, {1, 2}, {2, 5}},
            {{3, 1}}
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, InvertedIndexMissingWordTest) {
    const std::vector<std::string> docs = {
            "a b c d e f g h i j l",
            "statement"
    };
    const std::vector<std::string> requests = {"m", "statement"};
    const std::vector<std::map<size_t, size_t>> expected = {
            {},
            {{1, 1}}
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, LetterCaseTestInvertedIndex) {
    const std::vector<std::string> docs = {
            "Milk milk MIlk WATER",
            "Water milk milK water wateR"
    };
    const std::vector<std::string> requests = {"Milk", "milk", "WATER"};
    const std::vector<std::map<size_t, size_t>> expected = {
            {{0, 3}, {1, 2}},
            {{0, 3}, {1, 2}},
            {{0, 1}, {1, 3}}
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}

