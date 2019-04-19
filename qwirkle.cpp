
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

using std::cout;
using std::cin;
using std::endl;

void printMenu();
void showStudentInformation();

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   int userInput = 0;
   std::string line;

   cout << "Welcome to Qwirkle!" << endl;
   cout << "-------------------" << endl;

  do {
     printMenu();
     cin >> userInput;

     // Validate userInput
     if( !(cin.eof()) and ((userInput < 1) or (userInput > 4) or (!cin)) ){
       cin.clear();
       cout << "Invalid Input" << endl;
     }
     else{
         if ( userInput == 1 ){
           cout << "@TODO: New Game" << endl;
         }
         else if( userInput == 2){
           cout << "@TODO: Load Game" << endl;
         }
         else if( userInput == 3){
           showStudentInformation();
         }
       }
     } while ( (std::getline(cin, line)) && (userInput != 4) );

   cout << "\nGoodbye" << endl;

   return EXIT_SUCCESS;
}

void printMenu(){
	cout << "Menu\n"
    "1. New Game\n"
	   "2. Load Game\n"
	   "3. Show student information\n"
	   "4. Quit\n"
     "> " << std::flush;
}

void showStudentInformation(){
  cout << "---------------------------------------------" << endl;

  cout << "Name: Jessica Cruz" << endl;
  cout << "Student ID: s3571051" << endl;
  cout << "Email: s3571051@student.rmit.edu.au\n" << endl;

  cout << "Name: Kevin Vu" << endl;
  cout << "Student ID: s3678490" << endl;
  cout << "Email: s3678490@rmit.edu.vn\n" << endl;

  cout << "Name: Khoi Nguyen" << endl;
  cout << "Student ID: s3678755" << endl;
  cout << "Email: s3678755@rmit.edu.vn\n" << endl;

  cout << "Name: Tuan Vu" << endl;
  cout << "Student ID: s3678491" << endl;
  cout << "Email: s3678491@rmit.edu.vn" << endl;

  cout << "---------------------------------------------\n" << endl;
}
