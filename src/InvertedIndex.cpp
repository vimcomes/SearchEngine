//
// Created by vimcomes
//

#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "InvertedIndex.h"
#include "WordHandler.h"

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string> &inputDocs) {
    std::vector<std::thread *> concurrentProcessing;
    std::thread *fileProcessing;

    for (size_t docId = 0; docId < inputDocs.size(); ++docId) {
        fileProcessing = new std::thread(&InvertedIndex::documentIndexing, this, docId, inputDocs[docId]);
        concurrentProcessing.push_back(fileProcessing);
    }

    for (size_t docId = 0; docId < inputDocs.size(); ++docId) {
        concurrentProcessing[docId]->join();
        delete concurrentProcessing[docId];
    }
}

std::map<size_t, size_t> InvertedIndex::GetWordCount(std::string word) {
    const std::lock_guard<std::mutex> lock(freqDictionaryAccess);

    std::map<size_t, size_t> result;
    WordHandler::replaceCapitalLetters(word);

    if (freqDictionary.find(word) != freqDictionary.end())
        result = freqDictionary[word];

    return result;
}

void InvertedIndex::documentIndexing(size_t docId, const std::string &doc) {
    std::vector<std::string> words(WordHandler::getWords(doc));

    const std::lock_guard<std::mutex> lock(freqDictionaryAccess);

    for (auto &word: words) {
        bool entryIsFind = false;
        bool wordIsFind = freqDictionary.find(word) != freqDictionary.end();

        if (wordIsFind) {
            if (freqDictionary[word].find(docId) != freqDictionary[word].end()) {
                ++freqDictionary[word][docId];
                entryIsFind = true;
            }
        }

        if (!wordIsFind || !entryIsFind)
            freqDictionary[word][docId] = 1;
    }
}






