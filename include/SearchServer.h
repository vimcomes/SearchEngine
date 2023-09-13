//
// Created by vimcomes.
//

#pragma once

#include "InvertedIndex.h"

// This struct represents a relative index of a document.
struct RelativeIndex {
    // The document ID.
    size_t docId;
    // The relevance score.
    float rank;
    // This operator compares two `RelativeIndex` objects.
    bool operator==(const RelativeIndex &other) const;
};

// This class implements a search server.
class SearchServer {
public:

    /** This constructor initializes the search server
     * @param inputDocs
     * @param inputResponsesLimit
     */
    SearchServer(const std::vector<std::string> &inputDocs, const int &inputResponsesLimit);

    /**
     * This method searches for documents that contain the given words.
     * @param inputRequests
     * @return
     */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &inputRequests);

private:
    // The inverted index.
    InvertedIndex index;

    // The maximum number of responses to return.
    int responsesLimit;

    /**
     * This method gets the list of documents that contain the given words.
     * @param request
     * @return
     */
    std::vector<size_t> getListDocContainingWords(const std::vector<std::string> &request);

    /**
     * This method calculates the relevance scores for the given documents and words.
     * @param docList
     * @param request
     * @return
     */
    std::vector<RelativeIndex> calculateRelevance(
            const std::vector<size_t> &docList,
            const std::vector<std::string> &request);
};
