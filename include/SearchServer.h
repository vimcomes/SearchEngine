//
// Created by vimcomes.
//

#pragma once

#include "InvertedIndex.h"

struct RelativeIndex {
    size_t docId;
    float rank;

    bool operator==(const RelativeIndex &other) const;
};

class SearchServer {
public:
    SearchServer(const std::vector<std::string> &inputDocs, const int &inputResponsesLimit);

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &inputRequests);

private:
    InvertedIndex index;
    int responsesLimit;

    std::vector<size_t> getListDocContainingWords(const std::vector<std::string> &request);

    std::vector<RelativeIndex> calculateRelevance(
            const std::vector<size_t> &docList,
            const std::vector<std::string> &request);
};
