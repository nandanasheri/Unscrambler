/*  Unscrambler : Create a board that is filled with words
    which are then scrambled and presented to the user, who rotates
    the rows and columns to try and get the original words displayed
    in the right order on the board.
    Author: Nandana Sheri
    Date: 05/11/2021
    Class: CS 141, Fall 2021, UIC
    System: CLion using Windows
*/
#include <iostream>
#include <string>                   // To use string functions
#include <random>                   // To use random numbers
#include <vector>                   // To use vectors
#include <fstream>                  // For file input and output
#include <cassert>                  // For the assert statement used to validate file open
#include <sstream>                  // To use string stream

using namespace std;

// Creation of a class Board to implement the board of the game with its size.
class Board {
public:
    void setSize (int size)                                     //size of the board
    { this -> size = size; }                                    // Function to set the board to a user input size
    void setRandomWords (string randomWords) {
        this -> randomWords = randomWords;
    }
    void setScramble ( int scramble) {                          // Function to set extent of scrambling
        this -> scramble = scramble;
    }
    void setCompletedBoard ( string completedBoard) {           // Function to set the completed board words
        completedBoardWords = completedBoard;
    }
    void setInitialBoardWords (string initialBoardWords) {      // Function to set board words after scrambling
        this -> initialBoardWords = initialBoardWords;
    }
    int getSize () { return size; }                                 // Function to get the size of the board
    string getRandomWords() { return randomWords;}                  // Function to get the random words
    int getScramble () { return scramble; }                         // Function get the extent of scrambling
    string getCompletedBoardWords () { return completedBoardWords; }// Function to get the original random words
    string getInitialBoardWords () { return initialBoardWords; }
    void DisplayBoard ();                                           // To display the board
    void DisplayCompletedBoard ();                                  // To display the completed board
    void DisplayRandomWords (vector <string> randomWordsVector) {   // To display the random words generated
        cout << "These are the words that you should try to spell out using the board, in order:" << endl;
        for (int i = 0; i < randomWordsVector.size(); i++) {
            if (i == (randomWordsVector.size() - 1)) {              // Checks for the last word
                cout << randomWordsVector.at(i) << "." << endl;     // Prints word followed by a full stop
            }
            else {
                cout << randomWordsVector.at(i) << ", ";            // Prints word followed by a comma
            }
        }
    }
private:
    int size;                                                       // Size of the board is stored
    string randomWords;                                             // Random words generated are stored here
    int scramble;                                                   // The extent of scrambling stored here
    string completedBoardWords;                                     // What the completed board should be
    string initialBoardWords;                                       // Stores the random words after the first scramble
};

//Function to display the board before the game with random words
void Board::DisplayBoard() {
    cout << "Current board:" << endl;
    int dashes = (size * 4) - 1;                                   // Pre determined formula given
    cout << "    ";
    for (int i = 0; i < size; i ++) {
        cout << i << "   ";                                        // Prints the index position
    }
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << "   ";
        for (int j = 0; j < dashes; j++) {                         // Prints the dashes
            cout << "-";
        }
        cout << endl;
        cout << i;                                                 // Prints the index position at the beginning of each line
        for (int k = 0; k < size; k++) {                           // Prints the standing lines
            int index = (i * size) + k;                            // Formula to determine the index position of each word
            cout << " | " << randomWords.at(index);                // Prints standing line and each character
        }
        cout << " | ";                                             // Last standing line is printed
        cout << endl;
    }
    cout << "   ";
    for (int j = 0; j < dashes; j++) {                             // Prints the dashes
        cout << "-";
    }
    cout << endl;
    cout << "Current board words:  " << randomWords << endl;
}

// Function to display the completed board
void Board ::DisplayCompletedBoard() {
    int dashes = (size * 4) - 1;                                   // Pre determined formula given
    cout << "    ";
    for (int i = 0; i < size; i ++) {
        cout << i << "   ";                                        // Prints the index position
    }
    cout << endl;
    for (int i = 0; i < size; i++) {
        cout << "   ";
        for (int j = 0; j < dashes; j++) {                         // Prints the dashes
            cout << "-";
        }
        cout << endl;
        cout << i;                                                 // Prints the index position at the beginning of each line
        for (int k = 0; k < size; k++) {                           // Prints the standing lines
            int index = (i * size) + k;                            // Formula to determine the index position of each word
            cout << " | " << completedBoardWords.at(index);        // Prints standing line and each character
        }
        cout << " | ";                                             // Last standing line is printed
        cout << endl;
    }
    cout << "   ";
    for (int j = 0; j < dashes; j++) {                             // Prints the dashes
        cout << "-";
    }
    cout << endl;
    cout << "Current board words:  " << completedBoardWords << endl;
}

// Function to read in all the words from the text file
void ReadIntoVector (vector <string> &listOfWords)        // vector passed to store the list of words
{
    // Read in all the words into the vector
    ifstream inStream;                                    // Declare an input stream for reading
    inStream.open( "dictionary-3to5-letters.txt");     // Open dictionary file
    assert( inStream.fail() == false );                   // Ensure file open worked
    listOfWords.clear();                                  // Clears the dictionary in case of any previous records
    // Keep repeating while input from the file yields a word
    string newWord;                                       // Store a single input word
    while( inStream >> newWord) {                         // While there is another word to be read
        listOfWords.push_back( newWord);                  // Add this new word to the end of the vector, growing it in the process
    }
    inStream.close();                                     // Close the dictionary file
    const int wordsInList = listOfWords.size();           // To store the length of the dictionary
    cout << wordsInList << " words have been read in from the dictionary." << endl;
}

// Function to generate random words for the board
void GenerateRandomWords (int size, vector<string> listOfWords,     // Size of the board and vector of all words
                          Board &currentBoard,                      // Current Board used to play the game
                          vector <string> &randomWordsVector) {     // Vector to store all random words
    string randomWords;                                     // Used to hold randomWords
    int numberOfSpacesLeft = size * size;                   // The number of spaces left to fill up words
    while (numberOfSpacesLeft > 2) {                        // Checks if number of spaces left is more than 3
        int index = rand() % listOfWords.size();            // Returns the index of random word
        string word = listOfWords.at(index);                // Generates a random word
        if (word.size() < numberOfSpacesLeft) {
            randomWordsVector.push_back(word);              // All the words are stored in a vector
            randomWords = randomWords + word + " ";         // Adds on to the random word string
            numberOfSpacesLeft = numberOfSpacesLeft - word.size() - 1;    // Length of word is removed from number of spaces left
        }
        else if (word.size() == numberOfSpacesLeft) {       // When the last word is exactly equal to the number of spaces
            randomWordsVector.push_back(word);
            randomWords = randomWords + word;               // A space is not required in the end
            numberOfSpacesLeft = numberOfSpacesLeft - word.size();      // Lack of space nullifies the need of the 1
        }
        else {
            continue;                                       // It goes back and searches for a new word
        }
    }
    while (randomWords.size() != (size * size)) {           // To make sure the length of the total words and spaces is size^2
        randomWords += " ";                                 // Add spaces to the end
    }
    currentBoard.setRandomWords (randomWords);  // Sets the random words on the board
    currentBoard.setCompletedBoard(randomWords); // Sets the random words to what the completed board should be
}

// Function to rotate a random row for the scrambling option
void RotateRows (Board &currentBoard,                           // Current Board in the game
                 int rowNumber,                                 // Row to be rotated
                 int numberOfShifts) {                          // Number of times shifting must take place
    int size = currentBoard.getSize();
    string randomWords = currentBoard.getRandomWords();
    string shiftedString = randomWords;                         // Stores the new shifted string
    if (numberOfShifts < 0) {                                   // Checks for whether the number of shifts is negative
        numberOfShifts = numberOfShifts + size;                 // If negative the moves are implemented using positive
    }                                                           // number for eg: 1 step backward in a board of size 4
    for (int j = 0; j < numberOfShifts; j++) {                  // is the same as 3 steps forward.
        for (int i = 0; i < size; i++ ) {                       // Loops through an entire row
            int index = (rowNumber * size) + i;                 // Formula to look through characters in random row
            if (i != (size - 1) ) {                             // For each character
                shiftedString.at(index + 1) = randomWords.at(index);
            }
            else if (i == (size - 1)) {                         // For the last character
                int firstIndex = (rowNumber * size);            // Returns the last index from the row
                shiftedString.at(firstIndex) = randomWords.at(index);
            }
        }
        randomWords = shiftedString;                            // The new updated string becomes the random words
    }
    currentBoard.setRandomWords(shiftedString);     // The new string of random words is the shifted string
}

// Function to rotate a random column for the scrambling
void RotateColumns (Board &currentBoard,                       // Board current board for the game playing
                    int colNumber,                             // Column to be rotated
                    int numberOfShifts) {                      // Number of times each character is shifted
    int size = currentBoard.getSize();                         // Returns size of the board
    string randomWords = currentBoard.getRandomWords();        // Returns random words string
    string shiftedString = randomWords;                        // Stores the new shifted string
    if (numberOfShifts < 0) {
        numberOfShifts = numberOfShifts + size;
    }
    for (int j = 0; j < numberOfShifts; j++) {                 // Loops through the string for the number of times it should be shifted
        for (int i = 0; i < size; i++) {                       // Loops through the words string to shift particular column
            int index = (i * size) + colNumber;                // Formula to find index position of a single column
            if (i == (size - 1)) {                             // Last character becomes the first character of column
                shiftedString.at(colNumber) = randomWords.at(index);
            }
            else {                                              // For every other character
                shiftedString.at(index + size) = randomWords.at(index);        // Shifts one character down
            }
        }
        randomWords = shiftedString;
    }
    currentBoard.setRandomWords(shiftedString); // The new string of random words is the shifted string
}

//Function to rotate rows and columns in the board to shuffle the words
void RotateRowsAndColumns (Board &currentBoard) {                    // Current Board of class Board
    string randomWords = currentBoard.getRandomWords();              // Returns a string of random words
    int size = currentBoard.getSize();
    int scramble = currentBoard.getScramble();                       // Returns the extent of scrambling
    int numberOfRotations = scramble * 2;
    for (int i = 0; i < numberOfRotations; i++) {                    // Loop that alternates between rotating row
        if (i % 2 == 0) {                                            // and column
            int randRow = rand() % size;                             // A random column is selected using rand function
            RotateRows(currentBoard, randRow, 1);    // Rotate a row alternatively
        }
        else {
            int randCol = rand() % size;                             // A random row is selected using rand function
            RotateColumns(currentBoard,randCol, 1);  // Rotates a column alternatively
        }
    }
}

// Function to rotate any row or column upon user's input
void RotateAnyRowOrColumn (Board &currentBoard,    // Current Board which user is playing with and vector with random words
                           vector<string> randomWordsVector) {
    char rowOrCol;                                 // To rotate either row or column
    int rowOrColNumber, numberOfShifts;            // To store row or column number and number of positions to rotate
    int maxRotations = currentBoard.getSize() - 1; // Maximum number of rotations is given by size - 1
    while (true) {                                 // Prints the menu options
        cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
                "   This should be in the format of <R or C> <row/column number> <number of positions to rotate>,\n"
                "   where valid row and column numbers are between 0 and " << currentBoard.getSize() - 1 << ", \n" <<
                "   E.g. R 0 1 would rotate the top row (row 0) of the board to the right once,\n"
                "        c 1 -2 would rotate the second column (col 1) of the board upwards twice.\n"
                "   Your choice: ";
        cin >> rowOrCol;                            // Each input is stored into separate variables
        cin >> rowOrColNumber;
        cin >> numberOfShifts;
        rowOrCol = toupper(rowOrCol);               // Converts into uppercase
        if ((rowOrCol == 'R' or rowOrCol == 'C') and (numberOfShifts <= maxRotations)
        and (rowOrColNumber >= 0 and rowOrColNumber < currentBoard.getSize()) ) {   // To check whether user input is valid
            if (rowOrCol == 'R') {                                     // To rotate a particular row
                RotateRows(currentBoard, rowOrColNumber, numberOfShifts);
            }
            else if (rowOrCol == 'C') {                                // To rotate a particular column
                RotateColumns(currentBoard, rowOrColNumber, numberOfShifts);
            }
            string  randomWords = currentBoard.getRandomWords();       // Returns random words string
            string completedBoardWords = currentBoard.getCompletedBoardWords();
            if (randomWords == completedBoardWords) {           // Checks if the two strings are equal
                currentBoard.DisplayCompletedBoard();
                cout << "Congratulations, you won! Thank you for playing!\n"
                        "Exiting program..." << endl;
                exit(0);                                 // PLayer has won the game and exits
            }
            else {
                currentBoard.DisplayRandomWords(randomWordsVector); // To print for random words if no win is detected
                currentBoard.DisplayBoard();                    // Displays the board
            }
            break;
        }
        else if ((rowOrCol != 'R') and (rowOrCol != 'C'))  {       // If either R or C is not entered
            cout << "First input must be 'R' or 'C'. Try again." << endl;
        }
        else if (rowOrColNumber >= currentBoard.getSize() or rowOrColNumber < 0){   // If row number exceeds the limit
            cout << "Number must be between 0 and " << currentBoard.getSize() - 1 << ". Try again." << endl;
        }
    }
}

// Function to reset the board to original way along with the scramble
void ResetBoard (Board &currentBoard) {                          // Current Board that user is playing with
    string initialBoardWords = currentBoard.getInitialBoardWords();
    currentBoard.setRandomWords(initialBoardWords);  // Random Words will reset back to the original words
    currentBoard.DisplayBoard();                                 // Displays the reset board
}

// Function to print Menu Options and ask for user input
void MenuOptions (Board &currentBoard) {
    char choice;                                            // To store the user's choice
    cout << "Enter Q to quit or B to begin: ";
    cin >> choice;
    if (toupper(choice) == 'Q') {                           // Checks for upper and lower case
        cout << "Thank you for playing!\n"
                "Exiting program...";
        exit(0);                                      // Exits the game and the program
    }
    else if (toupper(choice) == 'B') {                      // If user wishes to play
        int size = 0;                                       // Size is initialized to 0
        int scramble = 0;                                   // The number of times the words must be scrambled
        cout << "Choose your board size (must be a number greater than or equal to 4):";
        cin >> size;
        while (size < 4) {                                  // If size is not greater than or equal to 4
            cout << "The board size must be at least 4. Retry." << endl;
            cout << "Choose your board size (must be a number greater than or equal to 4):";
            cin >> size;
        }
        currentBoard.setSize(size);                         // Sets board size as user input
        cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):";
        cin >> scramble;                                    // Asks for number of times board must be scrambled
        while (scramble < 1) {
            cout << "The number of times you select must be at least 1. Retry." << endl;
            cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):";
            cin >> scramble;                                // Checks if number entered is valid if not asks for input
        }
        currentBoard.setScramble(scramble);                 // Sets to how much the board must be scrambled
    }
}

// Function to print out the sub menu options after the board is generated and scrambled initially
void SubMenuOptions ( Board &currentBoard,                      // Current Board in which user is playing
                      vector<string> randomWordsVector,         // Vector containing all random words
                      vector <string> listOfWords ) {           // Vector containing all words from the dictionary
    char userChoice = ' ';                                      // Stores the user input
    while (toupper(userChoice) != 'Q') {
        cout << "Enter one of the following:\n"                 // Prints the menu options
                "   R to rotate a row or column,\n"
                "   C to view what the completed board should look like,\n"
                "   B to reset the board back to the beginning,\n"
                "   G to generate a new board with new random words,\n"
                "   S to have the computer automatically solve a board that you enter (5 points extra credit),\n"
                "   Q to quit.\n"
                "Your choice: ";
        cin >> userChoice;
        if (toupper(userChoice) == 'R') {                       // To rotate rows and columns explicitly
            RotateAnyRowOrColumn(currentBoard, randomWordsVector); // Rotates row or column
        }
        else if (toupper(userChoice) == 'C') {                  // To show the completed board
            cout << "The completed board should look like:" << endl;
            currentBoard.DisplayCompletedBoard();
            currentBoard.DisplayRandomWords(randomWordsVector);
            currentBoard.DisplayBoard();
        }
        else if (toupper(userChoice) == 'B') {
            currentBoard.DisplayRandomWords(randomWordsVector); // Displays the random words
            ResetBoard(currentBoard);                       // Resets the board back to the beginning
        }
        else if (toupper(userChoice) == 'G') {
            int size = currentBoard.getSize();
            randomWordsVector.clear();                         // To erase all previous words
            GenerateRandomWords(size, listOfWords,currentBoard, randomWordsVector); // Generating new random words
            string randomWords = currentBoard.getRandomWords();// To return the original random words
            currentBoard.DisplayRandomWords(randomWordsVector);                     // Displaying random words
            currentBoard.setCompletedBoard(randomWords);   // To set random words in completed board
            RotateRowsAndColumns(currentBoard);             // To scramble the board
            randomWords = currentBoard.getRandomWords();       // Returns the scrambled random words
            currentBoard.setInitialBoardWords(randomWords); // Initial scrambled words
            currentBoard.DisplayBoard();                       // To display the board
        }
        else if (toupper(userChoice) != 'R' and toupper(userChoice) != 'C' and toupper(userChoice) != 'B'
        and toupper(userChoice) != 'G' and toupper(userChoice) != 'Q') {    // Checking whether any of the options is valid
            cout << "You did not enter one of the valid options. Try again." << endl;
            currentBoard.DisplayRandomWords(randomWordsVector);
            currentBoard.DisplayBoard();
        }
    }
    if (toupper(userChoice) == 'Q') {                       // Quitting program based off of user input
        cout << "Thank you for playing! \n"
                "Exiting program...";
        exit(0);
    }
}

// Main Function of the program
int main() {
    // Seed the random number generator so that the results are predictably the same.
    cout << "Program 5: Unscrambler\t\n"
            "CS 141, Fall 2021, UIC\t\n"
            " \n"
            "You will be presented with a board that is filled  \n"
            "with scrambled words. Rotate the rows and columns  \n"
            "to get the words displayed in the right order. " << endl;
    srand( 1);                                       // srand() makes the random number predictable
    vector <string> listOfWords;
    ReadIntoVector(listOfWords);                        // The entire text file is read into a vector and stored as strings
    Board currentBoard;                                    // The board is set to class Board
    while (true) {
        MenuOptions(currentBoard);                      // Prints the menu options
        int size = currentBoard.getSize();
        vector <string> randomWordsVector;                 // To store each word as an element in the vector
        GenerateRandomWords(size,listOfWords, currentBoard, randomWordsVector );
        currentBoard.DisplayRandomWords(randomWordsVector);     // Correctly spelled words is printed
        RotateRowsAndColumns(currentBoard);            // Rotates the Rows and Columns
        currentBoard.setInitialBoardWords(currentBoard.getRandomWords()); // To set the initial board words after scramble
        currentBoard.DisplayBoard();                      // After scrambling, board is displayed
        SubMenuOptions(currentBoard, randomWordsVector, listOfWords);
        break;
    }
    return 0;
}