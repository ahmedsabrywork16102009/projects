#pragma once

#include <string>
#include <string_view>


namespace process
{
    std::string tabs(int numberOfTabs);
    std::string lines(int numberOfLines);
    std::string spaces(int numberOfSpaces);
    int getRandomNumber(int from, int to);



    std::string tabs(int numberOfTabs) {
        std::string result = "";

        result.reserve(numberOfTabs * 4);

        for (int i = 0; i < numberOfTabs; i++) {
            result.append("    ");
        }

        return result;
    }
    std::string lines(int numberOfLines) {
        std::string result = "";

        result.reserve(numberOfLines * 2);

        for (int i = 0; i < numberOfLines; i++) {
            result.append("\n");
        }

        return result;
    }
    std::string spaces(int numberOfSpaces) {
        std::string result = "";

        result.reserve(numberOfSpaces);

        for (int i = 0; i < numberOfSpaces; i++) {
            result.append(" ");
        }

        return result;
    }
    int getRandomNumber(int from, int to) {
        return rand() % (to - from + 1) + from;
    }
}