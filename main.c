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

int main() {
  while (true) {
    int welcomeScreenChoice = printWelcomeScreen();
    break;
  }
  return 0;
}
