//
// Created by vimcomes.
//

#pragma once

#include <map>
#include <mutex>

class InvertedIndex {
public:
    InvertedIndex() = default;

    InvertedIndex(const InvertedIndex &index) = delete;

    void operator=(const InvertedIndex &index) = delete;

    void UpdateDocumentBase(const std::vector<std::string> &inputDocs);

    std::map<size_t, size_t> GetWordCount(std::string word);

private:
    std::map<std::string, std::map<size_t, size_t>> freqDictionary;
    std::mutex freqDictionaryAccess;

    void documentIndexing(size_t docId, const std::string &doc);
};
