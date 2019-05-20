#ifndef ASSIGNMENT_2_MENU
#define ASSIGNMENT_2_MENU

#include "GameEngine.h"

class Menu{

public:

    Menu();
    void runProgram();
    void playGame();
    void loadGame();

    void printMenu();
    void showStudentInformation();
    bool checkForNameInput(std::string name);

    bool checkFileExist(std::string& fileName);
    bool validateFormat(std::string& fileName);
    bool checkFormatForPlayerHand(std::string& playerHand);

    void keepRecordFileInSyncWithSavingFile(std::string& fileName);
private:
    GameEngine gameEngine;



};

#endif //ASSIGNMENT_2_MENU
