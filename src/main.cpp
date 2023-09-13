/**
 * Created by vimcomes
 * @file main.cpp
 *
 * @brief It is the final work of the course "C++ Developer" from Skillbox
 */

#include <iostream>
#include <string>

#include "nlohmann/json.hpp"
#include "SearchServer.h"
#include "ConverterJSON.h"
#include "CheckOut.h"


int main() {
    //check and start
    if (isReadyToStart()) {
        SearchServer searchServer(ConverterJSON::GetTextDocuments(), ConverterJSON::GetResponsesLimit());

        std::vector<std::vector<RelativeIndex>> answers = searchServer.search(ConverterJSON::GetRequests());

        ConverterJSON::putAnswers(answers);
        //Output result of work
        printResult(answers);
    }

    std::string command;
    while (command != "exit") {
        std::cout << "Enter \"exit\" to exit the program: ";
        std::cin >> command;
    }

    return 0;
}
