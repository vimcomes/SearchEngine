/**
 * Created by vimcomes
 * @file SearchServer.cpp
 * @brief This file contains the implementation of the `SearchServer` class.
 */

#include <string>
#include <vector>
#include <algorithm>

#include "SearchServer.h"
#include "WordHandler.h"

/**
 * @brief Compares two `RelativeIndex` objects.
 *
 * @param other The other `RelativeIndex` object to compare with.
 * @return True if the two objects are equal, false otherwise.
*/
bool RelativeIndex::operator==(const RelativeIndex &other) const {
    return (docId == other.docId &&
            rank == other.rank);
}

/**
 * @brief Constructs a new `SearchServer` object.
 *
 * @param inputDocs The input documents.
 * @param inputResponsesLimit The maximum number of results to return.
*/
SearchServer::SearchServer(const std::vector<std::string> &inputDocs, const int &inputResponsesLimit)
        : responsesLimit(inputResponsesLimit) {
    index.UpdateDocumentBase(inputDocs);
}

/**
 * @brief Searches for documents that contain the given words.
 *
 * @param inputRequests The input requests.
 * @return The results of the search.
*/
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &inputRequests) {
    // Gets the unique words in each request.
    std::vector<std::vector<std::string>> uniqueWordsInRequests;
    uniqueWordsInRequests.reserve(inputRequests.size());

    for (const auto &request: inputRequests)
        uniqueWordsInRequests.push_back(WordHandler::chooseUniqueWords(request));

    // Gets the list of documents that contain the words for each request.

    // A vector of vectors of `RelativeIndex` objects. Each inner vector stores the search results for a request.
    std::vector<std::vector<RelativeIndex>> result;

    for (auto &request: uniqueWordsInRequests) {
        // Gets the list of documents that contain the words in the request.
        std::vector<size_t> docList = getListDocContainingWords(request);
        // A vector of `RelativeIndex` objects that stores the search results for the current request.
        std::vector<RelativeIndex> requestResult;

        // If the list of documents is not empty, then calculates the relevance scores for the documents.
        if (!docList.empty())
            requestResult = calculateRelevance(docList, request);

        // Adds the results for the current request to the `result` vector.
        result.push_back(requestResult);
    }
    // Returns the search results.
    return result;
}

/**
 * @brief This method gets the list of documents that contain the given words.
 *
 * @param request
 * @return result
*/
std::vector<size_t> SearchServer::getListDocContainingWords(const std::vector<std::string> &request) {
   /**
   * The first step is to iterate over the words in the request.
   * For each word, the function gets the list of documents that contain the word from the index.
   * then checks if the document is already in the `result` vector. If the document is not in the vector, then the function adds it to the vector.
   * returns the `result` vector.
   */

    // Creates a vector to store the document IDs of the documents that contain the words.
    std::vector<size_t> result;

    // Iterates over the words in the request.
    for (const auto &word: request) {
        // Gets the list of documents that contain the word from the index.
        std::map<size_t, size_t> comparedDocList(index.GetWordCount(word));

        // Iterates over the documents that contain the word.
        for (auto &i: comparedDocList) {
            // Checks if the document is already in the `result` vector.
            bool docIsFound = false;

            // Iterates over the `result` vector.
            for (int j = 0; j < result.size() && !docIsFound; ++j) {
                // If the document is found in the `result` vector, then set `docIsFound` to true.
                if (result[j] == i.first)
                    docIsFound = true;
            }
            // If the document is not found in the `result` vector, then add it to the vector.
            if (!docIsFound)
                result.push_back(i.first);
        }
    }
    // Returns the `result` vector.
    return result;
}

/**
 * @brief This method calculates the relevance of each document in the docList to the request.
 * @param docList A vector of document IDs.
 * @param request A vector of words.
 * @return A vector of RelativeIndex objects, where each object contains the document ID and the relevance score.
 */
std::vector<RelativeIndex>
SearchServer::calculateRelevance(const std::vector<size_t> &docList,
                                 const std::vector<std::string> &request) {

    // The first step is to initialize a vector of RelativeIndex objects, where each object
    // contains the document ID and the relevance score.
    std::vector<RelativeIndex> result;
    size_t absoluteRelevance = 0;

    // Next, iterate over the document IDs in docList.
    for (auto &i: docList) {
        size_t relevance = 0.0f;

        // Next, iterate over the words in the request.
        for (auto &word: request) {
            //Get the number of times the current word appears in the current document.
            std::map<size_t, size_t> temp = index.GetWordCount(word);

            // If the current document contains the word, add the word count to the relevance.
            if (temp.find(i) != temp.end())
                relevance += temp[i];
        }

        // If the relevance of the current document is greater than the absolute relevance,
        // update the absolute relevance.
        if (relevance > absoluteRelevance)
            absoluteRelevance = relevance;

        // Create a RelativeIndex object for the current document and add it to the result vector.
        RelativeIndex currentDoc = {i, (float) relevance};
        result.push_back(currentDoc);
    }

    // Next, iterate over the result vector and divide the relevance score of each document
    // by the absolute relevance. This ensures that the relevance scores are between 0 and 1.
    for (auto &doc: result)
        doc.rank /= (float) absoluteRelevance;

    // Finally, we sort the result vector by the relevance scores, in descending order.
    std::sort(result.begin(), result.end(), [](const RelativeIndex &first, const RelativeIndex &second) {
        if (first.rank == second.rank)
            return first.docId < second.docId;
        else
            return first.rank > second.rank;
    });

    // If the number of documents in the result vector is greater than the responsesLimit,
    // resize the result vector to the responsesLimit.
    if (result.size() > responsesLimit)
        result.resize(responsesLimit);

    // Return the result vector.
    return result;
}


