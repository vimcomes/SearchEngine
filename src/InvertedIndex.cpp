/**
 * Created by vimcomes
 * @file InvertedIndex.cpp
 * @brief This file contains the implementation of the `InvertedIndex` class.
 */


#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include "InvertedIndex.h"
#include "WordHandler.h"

/**
 * This method updates the document base in a multithreaded way.
 * @param inputDocs
 */
void InvertedIndex::UpdateDocumentBase(const std::vector<std::string> &inputDocs) {
    // Create a vector to store the thread objects.
    std::vector<std::thread *> concurrentProcessing;
    std::thread *fileProcessing;

    // Create a thread object for each document.
    for (size_t docId = 0; docId < inputDocs.size(); ++docId) {
        fileProcessing = new std::thread(&InvertedIndex::documentIndexing, this, docId, inputDocs[docId]);
        concurrentProcessing.push_back(fileProcessing);
    }

    // Join the threads.
    for (size_t docId = 0; docId < inputDocs.size(); ++docId) {
        concurrentProcessing[docId]->join();
        delete concurrentProcessing[docId];
    }
}

/**
 * This method gets the word count for a given word.
 * @param word
 * @return result
 */
std::map<size_t, size_t> InvertedIndex::GetWordCount(std::string word) {
    // Get a lock on the frequency dictionary.
    const std::lock_guard<std::mutex> lock(freqDictionaryAccess);

    std::map<size_t, size_t> result;
    // Convert all uppercase letters in the word to lowercase letters.
    WordHandler::replaceCapitalLetters(word);

    // Check if the word exists in the `freqDictionary` object.
    if (freqDictionary.find(word) != freqDictionary.end())
        // If the word exists, then return its word count.
        result = freqDictionary[word];

    return result;
    // Otherwise, return an empty map.
}

/**
 * This method indexes a document.
 * @param docId
 * @param doc
 */
void InvertedIndex::documentIndexing(size_t docId, const std::string &doc) {
    // Get the words in the document.
    std::vector<std::string> words(WordHandler::getWords(doc));

    // Get a lock on the frequency dictionary.
    const std::lock_guard<std::mutex> lock(freqDictionaryAccess);

    // Iterate over the words in the document.
    for (auto &word: words) {
        bool entryIsFind = false;
        // Check if the word is already in the frequency dictionary.
        bool wordIsFind = freqDictionary.find(word) != freqDictionary.end();

        // If the word is in the frequency dictionary, then check if the document ID is already in the word's entry.
        if (wordIsFind) {
            if (freqDictionary[word].find(docId) != freqDictionary[word].end()) {
                // If the document ID is in the word's entry, then increment the word count for the document ID.
                ++freqDictionary[word][docId];
                entryIsFind = true;
            }
        }

        // If the word is not in the frequency dictionary, then add the word to the dictionary with a word count of 1 for the document ID.
        if (!wordIsFind || !entryIsFind)
            freqDictionary[word][docId] = 1;
    }
}






