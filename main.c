#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int printWelcomeScreen() {
  int choice;
  int validChoices[] = {1,2,3};
  int n = sizeof(validChoices) / sizeof(validChoices[0]);
  bool validChoice;
  //This should print the GUI onto the terminal
  system("cls");//Clears the terminal
  fflush(stdout);
  printf("Welcome to the Bank of Florida\n");
  printf("Press 1 to create an account\n");
  printf("Press 2 to log into an account\n");
  printf("Press 3 to exit\n");

  do {
    printf("Enter a valid choice (1, 2 or 3): \n");fflush(stdout);
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

void exitProgram() {
  system("cls");fflush(stdout);
  printf("Thank you for your patronage\n");
  exit(0);
}

typedef struct {
  int id;
  char firstname[50];
  char lastname[50];
  char email[50];
  char password[50];
} BankAccount;

BankAccount createAccount(BankAccount accounts[], int size) {
  BankAccount account;

  printf("Please enter your first name:\n");fflush(stdout);
  scanf("%49s", account.firstname);

  printf("Please enter your last name:\n");fflush(stdout);
  scanf("%49s", account.lastname);

  printf("Please enter your email:\n");fflush(stdout);
  scanf("%49s", account.email);

  printf("Please enter your password:\n");fflush(stdout);
  scanf("%49s", account.password);

  for (int i = 0; i < size; i++) {
    if (accounts[i].id == -1) {
      account.id = i + 1;
      accounts[i] = account;
      return accounts[i];
    }
  }

  printf("Error...");
  exit(1);
}

BankAccount loginToAccount(BankAccount accounts[], int size) {
  bool emailFound = false;
  BankAccount account;
  system("cls");fflush(stdout);
  do {
    char email[50];
    printf("Please enter the email of your account, please be mindful of capitalization");fflush(stdout);
    scanf("%49s", email);

    if (strcmp(email, "create") == 0) {
      createAccount(accounts, size);
      continue;
    }

    for (int i = 0; i < size; i++) {
      if (strcmp(accounts[i].email, email) == 0) {
        emailFound = true;
        account = accounts[i];
      }
    }

    if (!emailFound) {
      printf("Your email was not found. Please try again.\n");fflush(stdout);
      printf("If you need to create an account enter \"create\" next time you are prompted for a password\n");fflush(stdout);
    }
  } while (!emailFound);

  bool correctPassword = false;

  do {
    char enteredPassword[50];
    printf("Please enter the password for the account associated with %s", account.email);fflush(stdout);
    scanf("%49s", enteredPassword);

    if (strcmp(enteredPassword, account.password) == 0) {
      printf("Welcome back %s! Logging you in\n", account.firstname);fflush(stdout);
      return account;
    }
    else {
      printf("Please try again.\n");
    }


  } while (true);
}

int main() {
  BankAccount Accounts[100] = {-1};
  BankAccount activeAccount = {-1};


  while (true) {
    int welcomeScreenChoice = printWelcomeScreen();
    // 1- create an account 2- log into an account 3- log out of an account 4 -exit
    if (welcomeScreenChoice == 1) {
      activeAccount = createAccount(Accounts, (sizeof(Accounts) / sizeof(Accounts[0])));
    }
    else if (welcomeScreenChoice == 2) {
      activeAccount = loginToAccount(Accounts, (sizeof(Accounts) / sizeof(Accounts[0])));
    }
    else if (welcomeScreenChoice == 3) {
      exitProgram();
      break;
    }
  }
  return 0;
}
