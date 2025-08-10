#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int printWelcomeScreen() {
  int choice;
  int validChoices[] = {1,2,3};
  int n = sizeof(validChoices) / sizeof(validChoices[0]);
  bool validChoice;
  //This should print the GUI onto the terminal
  system("cls");//Clears the terminal
  printf("Welcome to the Bank of Florida\n");
  printf("Press 1 to create an account\n");
  printf("Press 2 to log into an account\n");
  printf("Press 3 to exit\n");

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

void exitProgram() {
  system("cls");
  printf("Thank you for your patronage");
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

  system("cls");
  printf("Please enter your first name:\n");
  scanf("%49s", account.firstname);

  printf("Please enter your last name:\n");
  scanf("%49s", account.lastname);

  printf("Please enter your email:\n");
  scanf("%49s", account.email);

  printf("Please enter your password:\n");
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
  char email[50];
  bool emailFound = false;
  BankAccount account;
  do {
    system("cls");
    printf("Please enter the email of your account, please be mindful of capitalization");
    scanf("%49s", email);

    for (int i = 0; i < size; i++) {
      if (accounts[i].email == email) {
        emailFound = true;
        account = accounts[i];
      }
    }
  } while (!emailFound);
  return account;
}

int main() {
  BankAccount Accounts[100] = {-1};
  BankAccount activeAccount;


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
    }
  }
  return 0;
}
