 #include <stdio.h>
#include <stdbool.h>

#define SIZE 6
#define nRows 2
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length); //function for displaying the array
void print_matrix(int rows, int cols, int mat[rows][cols]); //function for displaying matrix
bool isValid(const int arr[], int length, int pos); //function to check if it is valid
void remove_element(int arr[], int length, int pos); //function for removing element
void insert_element(int arr[], int length, int pos, int value); //function for adding element
bool reshape(const int arr[], int length, int rows, int cols, int arr2d[rows][cols]); //function for converting 1d to 2d
void trans_matrix(int rows, int cols, const int mat[rows][cols], int mat_transp[cols][rows]); //function for doing transpose
bool found_duplicate(int arr[], int length); //function for checking if the function has any duplicates

int main() {
    int arr[SIZE] = {10, 10, 30, 40, 50,60}; // Original array of size 5

    // Display the original 1D array
    printf("Original 1D array:\n");
    print_array(arr, SIZE);

    // Check for duplicates in the original array before any modifications
    printf("\nChecking for duplicates in the original array:\n");
    if (found_duplicate(arr, SIZE)) {
        printf("Duplicates found in the original array.\n");
    } else {
        printf("No duplicates found in the original array.\n");
    }

    //  remove_element function
    int pos_to_remove = 3; //define the position to remove
    printf("\nRemoving element at position %d:\n", pos_to_remove);
    remove_element(arr, SIZE, pos_to_remove);
    printf("Array after removing element at position %d:\n", pos_to_remove);
    print_array(arr, SIZE);

    // Reset array for next test
    int arr_insert_test[SIZE] = {10, 10, 30, 40, 50,60};

    // Test insert_element function
    int pos_to_insert = 2;
    int value_to_insert = 80; //defining position to insert and value
    printf("\nInserting element %d at position %d:\n", value_to_insert, pos_to_insert);
    insert_element(arr_insert_test, SIZE, pos_to_insert, value_to_insert);
    printf("Array after inserting element at position %d:\n", pos_to_insert);
    print_array(arr_insert_test, SIZE);

    // Reshape and transpose test
    int arr2d[nRows][nCols];
    if (reshape(arr, SIZE, nRows, nCols, arr2d)) {
        printf("\nReshaped 2D array:\n"); //reshape function, if it works then transpose function
        print_matrix(nRows, nCols, arr2d);

        int arr2d_transposed[nCols][nRows];
        trans_matrix(nRows, nCols, arr2d, arr2d_transposed);
        printf("\nTransposed 2D array:\n");
        print_matrix(nCols, nRows, arr2d_transposed);
    }

    return 0;
}

// Checks if the given position is within the valid range of array indices
bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);
}

// Removes an element by shifting all preceding elements one position down
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {  //if the element is not valid function is broken
        printf("Error: Position %d is out of bounds. Cannot remove element.\n", pos);
        return;
    }

    for (int i = pos; i > 0; i--) {
        arr[i] = arr[i - 1];  //goes through the entire array, from the position to the end and post-decrement
    }
}

// Inserts a new value at the specified position by shifting preceding elements up
void insert_element(int arr[], int length, int pos, int value) { 
    if (!isValid(arr, length, pos)) {
        printf("Error: Position %d is out of bounds. Cannot insert element.\n", pos); //same as before, if the element is invalid the function doesnt run
        return;
    }

    for (int i = 0; i < pos; i++) {
        arr[i] = arr[i + 1]; //shifts the values up
    }
    arr[pos] = value;
}

// Reshapes a 1D array into a 2D array if dimensions match
bool reshape(const int arr[], int length, int rows, int cols, int arr2d[rows][cols]) {
    if (length != rows * cols) { //checks if the reshaping criteria is met
        printf("Error: Array length %d does not match the target dimensions %d x %d.\n", length, rows, cols);
        return false;
    }

    int index = 0;
    for (int col = 0; col < cols; col++) { 
        for (int row = 0; row < rows; row++) {
            arr2d[row][col] = arr[index++]; //nested loops to go through each element, for the row and columns the element is the index and it keeps post increment
        }
    }
    return true;
}

// Transposes a matrix from rows x cols to cols x rows
void trans_matrix(int rows, int cols, const int mat[rows][cols], int mat_transp[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat_transp[j][i] = mat[i][j]; //again nested for loop, converts J element to I element
        }
    }
}

// Checks if there is at least one duplicate in the array
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) { //if the elements are equal returns true, else it returns false.
                return true;
            }
        }
    }
    return false;
}

// Prints a 1D array
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("array[%d] = %d\n", i, array[i]); //displays all the elements of the 1D array
    }
}

// Prints a 2D array (matrix)
void print_matrix(int rows, int cols, int mat[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("mat[%d][%d] = %d\t", i, j, mat[i][j]); //Nested for loops to display elements of 2D array
        }
        printf("\n");
    }
}
