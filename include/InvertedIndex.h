/**
 * Created by vimcomes
 * @file InvertedIndex.h
 * @brief This file contains the implementation of the `InvertedIndex` class.
 */

#pragma once

#include <map>
#include <mutex>

/**
 * @brief The InvertedIndex class store document identifiers,
 * lists of unique words for each of the documents, as well as calculated search
 * indexes.
 */
class InvertedIndex {
public:
    //default constructor
    InvertedIndex() = default;

    // This constructor is deleted to prevent copying of InvertedIndex objects.
    InvertedIndex(const InvertedIndex &index) = delete;

    // This assignment operator is deleted to prevent copying of InvertedIndex objects.
    void operator=(const InvertedIndex &index) = delete;

    /**
     * This method updates the document base in a multithreaded way.
     * @param inputDocs
    */
    void UpdateDocumentBase(const std::vector<std::string> &inputDocs);

    /**
     * This method gets the word count for a given word.
     * @param word
     * @return result
    */
    std::map<size_t, size_t> GetWordCount(std::string word);

private:
    // This is a map from words to a map from document IDs to the number of times the word appears in the document.
    std::map<std::string, std::map<size_t, size_t>> freqDictionary;
    // This is a mutex to protect the freqDictionary map.
    std::mutex freqDictionaryAccess;

    /**
     * This method indexes a document.
     * @param docId The ID of the document to index.
     * @param doc The document to index.
     */
    void documentIndexing(size_t docId, const std::string &doc);
};
