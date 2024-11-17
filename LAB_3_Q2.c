
#include <stdio.h>
#define initial_balance 1000

// Function Prototypes
void process_transactions(int transactions[], int length, int *balance, int tobeprocessed[], int *tobeprocessed_count);
void print_results(int balance, int tobeprocessed[], int tobeprocessed_count);

int main() {
    
    int balance = initial_balance;

    int transactions[] = {200, -150, -500, -400, -50, -200, -300};  // Transaction array given in question
    int length = sizeof(transactions) / sizeof(transactions[0]); //Equation to find the length of the array 
    int tobeprocessed[10] = {0};  // Array to store unprocessed transactions, set to hold 10 elements
    int tobeprocessed_count = 0;

    // Process transactions
    process_transactions(transactions, length, &balance, tobeprocessed, &tobeprocessed_count);

    // Display final balance and unprocessed transactions
    print_results(balance, tobeprocessed, tobeprocessed_count);

    return 0;
}

// Processes the transactions array and updates balance, storing unprocessed transactions
void process_transactions(int transactions[], int length, int *balance, int tobeprocessed[], int *tobeprocessed_count) {
    for (int i = 0; i < length; i++) {
        int transaction = transactions[i]; //for loop to go through every element of array

        if (transaction < 0 && *balance + transaction < 0) { 
            // Withdrawal exceeds balance then this transaction is skipped
            printf("Transaction %d (withdrawal of %d AED) is invalid due to insufficient funds.\n", i + 1, -transaction);
            tobeprocessed[(*tobeprocessed_count)++] = transaction;
            continue;
        }

        *balance += transaction;  // compute transaction and balance
        printf("Transaction %d: %d AED, New Balance: %d AED\n", i + 1, transaction, *balance);

        // Stop processing if balance reaches zero
        if (*balance == 0) {
            printf("Balance has reached zero. No further transactions will be processed.\n");

            // Store remaining transactions in tobeprocessed
            for (int j = i + 1; j < length; j++) {
                tobeprocessed[(*tobeprocessed_count)++] = transactions[j];
            }
            break;
        }
    }
}

// Prints the final balance and any unprocessed transactions
void print_results(int balance, int tobeprocessed[], int tobeprocessed_count) {
    printf("\nFinal balance: %d AED\n", balance);

    printf("Unprocessed transactions:\n");
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");
}
