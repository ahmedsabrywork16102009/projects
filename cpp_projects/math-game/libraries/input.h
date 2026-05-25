#pragma once

#include <iostream>
#include <string>
#include <string_view>

namespace input
{
    // define function prototypes
    int readNumberInRange(std::string_view message, int from, int to, std::string_view errorMessage = "Invalid input. Please try again.");
    int readPositiveNumber(std::string_view message, std::string_view errorMessage = "Invalid input. Please try again.");
    int readNegativeNumber(std::string_view message, std::string_view errorMessage = "Invalid input. Please try again.");
    int readNumber(std::string_view message);
    bool readBool(std::string_view message, std::string_view errorMessage = "Invalid input. Please try again.");


    // define function implementations
    int readNumberInRange(std::string_view message, int from, int to, std::string_view errorMessage) {
        int number;

        do {
            std::cout << message;
            std::cin >> number;

            if (number < from || number > to) {
                std::cout << errorMessage << std::endl;
            }
        } while (number < from || number > to);

        return number;
    }
    int readPositiveNumber(std::string_view message, std::string_view errorMessage) {
        int number;

        do {
            std::cout << message;
            std::cin >> number;

            if (number <= 0) {
                std::cout << errorMessage << std::endl;
            }
        } while (number <= 0);

        return number;
    }
    int readNegativeNumber(std::string_view message, std::string_view errorMessage) {
        int number;

        do {
            std::cout << message;
            std::cin >> number;

            if (number >= 0) {
                std::cout << errorMessage << std::endl;
            }
        } while (number >= 0);

        return number;
    }
    int readNumber(std::string_view message) {
        int number;

        std::cout << message;
        std::cin >> number;

        return number;
    }
    bool readBool(std::string_view message, std::string_view errorMessage) {
        return readNumberInRange(message, 0, 1, errorMessage) == 1;
    }





}