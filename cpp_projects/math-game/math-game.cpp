#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

#include "libraries/input.h"
#include "libraries/process.h"
#include "libraries/output.h"

using namespace std;

enum enQuestionsLevel{ 
    Easy = 1,
    Medium = 2,
    Hard = 3,
    MixLevel = 4
};

enum enOperationType {
    Add = 1,
    Subtract = 2,
    Multiply = 3,
    Divide = 4,
    MixOp = 5
};

struct stRoundInfo {
    int questionNumber;
    enQuestionsLevel questionLevel;
    enOperationType operationType;
    int number1;
    int number2;
    int userAnswer;
    int correctAnswer;
    bool isCorrectAnswer;
};

struct stGameInfo {
    int totalQuestions;
    int numberOfCorrectAnswers;
    int numberOfWrongAnswers;
    bool isPass;
};

bool doYouWantToPlay() {
    return input::readBool("Do you want to play again 1. Yes, 0. No? ");
}

int readNumberOfQuestions() {
    return input::readNumberInRange("How many questions do you want to answer? ", 1, 100);
}

enQuestionsLevel readQuestionLevel() {
    return (enQuestionsLevel)input::readNumberInRange("Choose the level of questions (1: Easy, 2: Medium, 3: Hard, 4: Mix): ", 1, 4);
}

enOperationType readOperationType() {
    return (enOperationType)input::readNumberInRange("Choose the type of operation (1: Add, 2: Subtract, 3: Multiply, 4: Divide, 5: Mix): ", 1, 5);
}

int getGeneratedNumber(enQuestionsLevel questionLevel) {
    switch (questionLevel) {
        case Easy:
            return process::getRandomNumber(1, 10);

        case Medium:
            return process::getRandomNumber(10, 50);

        case Hard:
            return process::getRandomNumber(50, 100);

        case MixLevel: {
            enQuestionsLevel level = (enQuestionsLevel)process::getRandomNumber(1, 3);
            return getGeneratedNumber(level);
        }

        default:
            return 0;
    }

    return 0;
}

int calculateCorrectAnswer(stRoundInfo roundInfo) {
    switch (roundInfo.operationType) {
        case Add:
            return roundInfo.number1 + roundInfo.number2;

        case Subtract:
            return roundInfo.number1 - roundInfo.number2;

        case Multiply:
            return roundInfo.number1 * roundInfo.number2;

        case Divide:{
            if (roundInfo.number2 == 0) {
                return 0;
            }

            return roundInfo.number1 / roundInfo.number2;
        }

        case MixOp: {
            roundInfo.operationType = (enOperationType)process::getRandomNumber(1, 4);

            return calculateCorrectAnswer(roundInfo);
        }

        default:
            return 0;
    }

    return 0;
}

string getOperationSymbol(enOperationType operationType) {
    switch (operationType) {
        case Add:
            return "+";

        case Subtract:
            return "-";

        case Multiply:
            return "*";

        case Divide:
            return "/";

        default:
            return "";
    }
}

void printMinuUserAnswer(stRoundInfo roundInfo) {
    cout << "Question " << roundInfo.questionNumber << ": " << process::lines(1) 
         << roundInfo.number1 << process::lines(1)
         << process::spaces(3) << getOperationSymbol(roundInfo.operationType) << process::lines(1) 
         << roundInfo.number2 << process::lines(1) 
         << "---------------------" << process::lines(1);
}

int readUserAnswer(stRoundInfo roundInfo) {
    printMinuUserAnswer(roundInfo);

    return input::readNumber("Enter your answer: ");
}

bool isCorrectAnswer(int userAnswer, int correctAnswer) {
    return userAnswer == correctAnswer;
}

void updateGameInfo(stGameInfo& gameInfo, bool isCorrect) {
    if (isCorrect) {
        gameInfo.numberOfCorrectAnswers++;
    } else {
        gameInfo.numberOfWrongAnswers++;
    }
}

void printRoundResult(stRoundInfo roundInfo, stGameInfo gameInfo) {
    cout << "==============================\n";
    cout << "         Question " << roundInfo.questionNumber << "/" << gameInfo.totalQuestions;
    cout << "\n==============================\n";
    cout << "Your answer: " << roundInfo.userAnswer << "\n";
    cout << "Correct answer: " << roundInfo.correctAnswer << "\n";

    if (roundInfo.isCorrectAnswer) {
        cout << "\nCongratulations! Your answer is correct.\n";
    } else {
        cout << "Sorry! Your answer is wrong.\n";
        cout << "\a"; // Beep sound
    }

    cout << "==============================" << process::lines(3);
}

void showGameOverScreen() {
    cout << process::lines(3) << 
            "==============================\n";
    cout << "         Game Over\n";
    cout << "==============================\n";
}

void printGameResult(stGameInfo gameInfo) {
    showGameOverScreen();
    cout << "Total Questions: " << gameInfo.totalQuestions << "\n";
    cout << "Correct Answers: " << gameInfo.numberOfCorrectAnswers << "\n";
    cout << "Wrong Answers: " << gameInfo.numberOfWrongAnswers << "\n";

    if (gameInfo.isPass) {
        cout << "Congratulations! You passed the game.\n";
    } else {
        cout << "Sorry! You failed the game.\n";
    }

    cout << "==============================" << process::lines(3);
}

bool isPass(stGameInfo gameInfo) {
    return gameInfo.numberOfCorrectAnswers >= (gameInfo.totalQuestions / 2);
}

void setRoundInfo(stRoundInfo& roundInfo, enQuestionsLevel questionLevel) {
    if (questionLevel == MixLevel) {
        roundInfo.questionLevel = (enQuestionsLevel)process::getRandomNumber(1, 3);
    } else {
        roundInfo.questionLevel = questionLevel;
    }
}

void setOperationInfo(stRoundInfo& roundInfo, enOperationType operationType) {
    if (operationType == MixOp) {
        roundInfo.operationType = (enOperationType)process::getRandomNumber(1, 4);
    } else {
        roundInfo.operationType = operationType;
    }
}

stGameInfo playGame(int numberOfQuestions, enQuestionsLevel questionLevel, enOperationType operationType) {
    stGameInfo gameInfo;

    gameInfo.totalQuestions = numberOfQuestions;
    gameInfo.numberOfCorrectAnswers = 0;
    gameInfo.numberOfWrongAnswers = 0;

    for (int i = 1; i <= numberOfQuestions; i++) {
        stRoundInfo roundInfo;

        roundInfo.questionNumber = i;

        setRoundInfo(roundInfo, questionLevel);
        setOperationInfo(roundInfo, operationType);

        roundInfo.number1 = getGeneratedNumber(questionLevel);
        roundInfo.number2 = getGeneratedNumber(questionLevel);
        roundInfo.correctAnswer = calculateCorrectAnswer(roundInfo);
        roundInfo.userAnswer = readUserAnswer(roundInfo);
        roundInfo.isCorrectAnswer = isCorrectAnswer(roundInfo.userAnswer, roundInfo.correctAnswer);
        
        updateGameInfo(gameInfo, roundInfo.isCorrectAnswer);
        
        printRoundResult(roundInfo, gameInfo);
    }

    gameInfo.isPass = isPass(gameInfo);

    return gameInfo;
}

void startGame() {
    bool playAgain = 1;

    do {
        int numberOfQuestions = readNumberOfQuestions();
        enQuestionsLevel questionLevel = readQuestionLevel();
        enOperationType operationType = readOperationType();

        stGameInfo gameInfo = playGame(numberOfQuestions, questionLevel, operationType);
        printGameResult(gameInfo);
        
        playAgain = doYouWantToPlay();
    } while (playAgain);
}

int main() {
    srand((unsigned)time(NULL));

    startGame();

    return 0;
}