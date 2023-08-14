//
// Created by vimcomes
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "SearchServer.h"
#include "WordHandler.h"

bool RelativeIndex::operator==(const RelativeIndex &other) const {
    return (docId == other.docId &&
            rank == other.rank);
}

SearchServer::SearchServer(const std::vector<std::string> &inputDocs, const int &inputResponsesLimit)
        : responsesLimit(inputResponsesLimit) {
    index.UpdateDocumentBase(inputDocs);
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &inputRequests) {
    std::vector<std::vector<std::string>> uniqueWordsInRequests;
    uniqueWordsInRequests.reserve(inputRequests.size());

    for (const auto &request: inputRequests)
        uniqueWordsInRequests.push_back(WordHandler::chooseUniqueWords(request));

    std::vector<std::vector<RelativeIndex>> result;

    for (auto &request: uniqueWordsInRequests) {
        std::vector<size_t> docList = getListDocContainingWords(request);
        std::vector<RelativeIndex> requestResult;

        if (!docList.empty())
            requestResult = calculateRelevance(docList, request);

        result.push_back(requestResult);
    }
    return result;
}

std::vector<size_t> SearchServer::getListDocContainingWords(const std::vector<std::string> &request) {
    std::vector<size_t> result;

    for (const auto &word: request) {
        std::map<size_t, size_t> comparedDocList(index.GetWordCount(word));

        for (auto &i: comparedDocList) {
            bool docIsFound = false;

            for (int j = 0; j < result.size() && !docIsFound; ++j) {
                if (result[j] == i.first)
                    docIsFound = true;
            }

            if (!docIsFound)
                result.push_back(i.first);
        }
    }
    return result;
}

std::vector<RelativeIndex>
SearchServer::calculateRelevance(const std::vector<size_t> &docList,
                                 const std::vector<std::string> &request) {
    std::vector<RelativeIndex> result;
    size_t absoluteRelevance = 0;

    for (auto &i: docList) {
        size_t relevance = 0.0f;

        for (auto &word: request) {
            std::map<size_t, size_t> temp = index.GetWordCount(word);

            if (temp.find(i) != temp.end())
                relevance += temp[i];
        }

        if (relevance > absoluteRelevance)
            absoluteRelevance = relevance;

        RelativeIndex currentDoc = {i, (float) relevance};
        result.push_back(currentDoc);
    }

    for (auto &doc: result)
        doc.rank /= (float) absoluteRelevance;

    std::sort(result.begin(), result.end(), [](const RelativeIndex &first, const RelativeIndex &second) {
        if (first.rank == second.rank)
            return first.docId < second.docId;
        else
            return first.rank > second.rank;
    });

    if (result.size() > responsesLimit)
        result.resize(responsesLimit);

    return result;
}


