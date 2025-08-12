#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
typedef struct {
  int id;
  char firstname[50];
  char lastname[50];
  char email[50];
  char password[50];
  float balance;
  float transactionHistory[10];
} BankAccount;

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

int printLoggedInScreen(BankAccount *account) {
  int choice;
  int validChoices[] = {1,2,3,4,5};
  int n = sizeof(validChoices) / sizeof(validChoices[0]);
  bool validChoice;

  system("cls");
  fflush(stdout);
  do {
    validChoice = false;
    printf("Welcome back %s!\n", account->firstname);
    printf("Press 1 to make a deposit\n");
    printf("Press 2 to make a withdrawal\n");
    printf("Press 3 to view transaction history\n");
    printf("Press 4 to log out\n");
    printf("Press 5 to exit\n");
    printf("\nEnter a valid choice (1-5): ");
    scanf("%d", &choice);

    for (int i = 0; i < n; i++) {
      if (choice == validChoices[i]) {
        validChoice = true;
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

void fillTransactionHistory(BankAccount *account, float nonZeroNumber){
  if (nonZeroNumber == 0){
    printf("Error... 0 was submitted for fillTransactionHistory() ");
    exit(0);
  }
  for (int i = 0; i < 10; i++){
    if (account->transactionHistory[i] == 0){
      account->transactionHistory[i] = nonZeroNumber;
      return;
    }
  }
  for (int i = 8; i >= 0; i--){
      account->transactionHistory[i+1] = account->transactionHistory[i];

    }
    account->transactionHistory[0] = nonZeroNumber;
    return;
}

void makeADeposit(BankAccount *account) {
  system("cls");
  float depositAmount = 0.0f;
  do {
      printf("How much money would you like to deposit? ");
      scanf("%f", &depositAmount);
      if (depositAmount > 0.0f){
        account->balance += depositAmount;
        fillTransactionHistory(account, depositAmount);
        printf("Hey %s thank you for depositing %.2f, you currently have a balance of %.2f", account->firstname, depositAmount, account->balance);
        Sleep(3000);
        return;
      }
      printf("Make sure that you are depositing more than 0 dollars\n");
      fflush(stdout);
      Sleep(3000);
  } while (true);
}

void makeAWithdrawl(BankAccount *account){
  system("cls");
  float withdrawlAmount = 0.0f;

  do{
    printf("Please enter the amount that you would like to withdrawl. You currently have a balance of %.2f$", account->balance);
    scanf("%f", &withdrawlAmount);

    if (withdrawlAmount <= 0){
      printf("Make sure to enter a positive amount of money\n");
      Sleep(5000);    
      continue;
    }
    else if ((account->balance - withdrawlAmount) < 0){
      printf("Insufficient Funds\n");
      printf("%.2f - %.2f = %.2f\n", account->balance, withdrawlAmount, (account->balance - withdrawlAmount));
      Sleep(5000);      
    }
    else {
      printf("Thansk you for withdrawing %.2f dollars. You now have a current balance of %.2f\n", withdrawlAmount, account->balance-withdrawlAmount);
      account->balance = account->balance - withdrawlAmount;
      fillTransactionHistory(account,-1*withdrawlAmount);
      Sleep(5000);
      return;
    }
  }while(true);
}

void viewTransactionHistory(BankAccount *account){
  system("cls");
  printf("This is the history of the account\n", account->email);
  for(int i = 0; i < 10; i++){
    if (account->transactionHistory[i] == 0){
      printf("That it the complete history of your account...\n");
      Sleep(5000);
      return;
    }
    else if (account->transactionHistory[i] > 0){
      printf("Deposited %.2f $\n", account->transactionHistory[i]);
      Sleep(500);
    }
    else if (account->transactionHistory[i] < 0){
      printf("Withdrew %.2f $\n", -1 * account->transactionHistory[i]);
      Sleep(500);
    }
  }
  printf("That it the complete history of your account...\n");
  Sleep(5000);
  return;
}

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

  account.balance = 0;

  for (int i = 0; i < 10; i++) {
    account.transactionHistory[i] = 0;
  }

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
  BankAccount Accounts[100];
  for (int i = 0; i < 100; i++) {
    Accounts[i].id = -1;
    Accounts[i].firstname[0] = '\0';
    Accounts[i].lastname[0] = '\0';
    Accounts[i].email[0] = '\0';
    Accounts[i].password[0] = '\0';
    Accounts[i].balance = 0.0f;
    for (int j = 0; j < 10; j++) {
        Accounts[i].transactionHistory[j] = 0;
    }
}
  BankAccount activeAccount = Accounts[0];
  
  while (true) {
    if (activeAccount.id != -1) {
      int loggedInSelection = -1;
      loggedInSelection = printLoggedInScreen(&Accounts[activeAccount.id]);

      if (loggedInSelection == 1){
        makeADeposit(&Accounts[activeAccount.id]);
      }
      else if (loggedInSelection == 2){
        makeAWithdrawl(&Accounts[activeAccount.id]);
      }
      else if (loggedInSelection == 3){
        viewTransactionHistory(&Accounts[activeAccount.id]);
      }
      else if (loggedInSelection == 4){
        activeAccount.id = -1;
      }
      else if (loggedInSelection == 5){
        exitProgram();
      }
      continue;
    }

    
    int welcomeScreenChoice = printWelcomeScreen();
    // 1- create an account 2- log into an account 3- log out of an account 4 -exit
    if (welcomeScreenChoice == 1) {
      //TODO Pass pointer
      activeAccount = createAccount(Accounts, (sizeof(Accounts) / sizeof(Accounts[0])));
    }
    else if (welcomeScreenChoice == 2) {
      //TODO Pass Pointer
      activeAccount = loginToAccount(Accounts, (sizeof(Accounts) / sizeof(Accounts[0])));
    }
    else if (welcomeScreenChoice == 3) {
      exitProgram();
      break;
    }
  }
  return 0;
}
