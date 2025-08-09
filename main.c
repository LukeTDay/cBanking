#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int printWelcomeScreen() {
  int choice;
  int validChoices[] = {1,2,3,4};
  int n = sizeof(validChoices) / sizeof(validChoices[0]);
  bool validChoice;
  //This should print the GUI onto the terminal
  system("cls");//Clears the terminal
  printf("Welcome to the Bank of Florida\n");
  printf("Press 1 to create an account\n");
  printf("Press 2 to log into an account\n");
  printf("Press 3 to log out an account\n");
  printf("Press 4 to exit\n");

  do {
    printf("Enter a valid choice (1, 2, 3 or 4): ");
    scanf("%d", &choice);
    validChoice = false;
    //breaks if non int lol
    for (int i = 0; i < n; i++) {
      if (choice == validChoices[i]) {
        validChoice = true;
        break;
      }
    }
  } while (!validChoice);
  return choice;
}

void exit() {
  system("cls");
  printf("Thank you for your patronage");
  exit(0);
}

int main() {

  while (true) {
    int welcomeScreenChoice = printWelcomeScreen();
    // 1- create an account 2- log into an account 3- log out of an account 4 -exit
    if (welcomeScreenChoice == 1) {

    }
    else if (welcomeScreenChoice == 2) {

    }
    else if (welcomeScreenChoice == 3) {

    }
    else if (welcomeScreenChoice == 4) {
      exit();
    }
    break;
  }
  return 0;
}
