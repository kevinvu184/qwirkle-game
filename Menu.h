#ifndef ASSIGNMENT_2_MENU
#define ASSIGNMENT_2_MENU

#include "GameEngine.h"

class Menu {

  public:

    Menu();
    void runProgram();
    void playGame();
    void loadGame();

    void printMenu();
    void showHighScore();
    void showStudentInformation();
    std::string inputPlayerNames(int player);
    bool validatePlayerName(std::string playerName);

    bool checkFileExist(std::string& fileName);
    bool validateFormat(std::string& fileName);
    bool checkFormatForPlayerHand(std::string& playerHand);

    void keepRecordFileInSyncWithSavingFile(std::string& fileName);
  private:
    GameEngine gameEngine;

};

#endif //ASSIGNMENT_2_MENU
