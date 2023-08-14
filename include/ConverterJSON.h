//
// Created by vimcomes
//

#pragma once

#include "SearchServer.h"

class ConverterJSON {
public:
    ConverterJSON() = default;

    static std::vector<std::string> GetTextDocuments();

    static std::vector<std::string> GetRequests();

    static int GetResponsesLimit();

    static void putAnswers(const std::vector<std::vector<RelativeIndex>> &answers);

private:
    static void GetFileAddresses(std::vector<std::string> &list);
};
