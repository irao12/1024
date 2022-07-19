#include <iostream>
#include "Board.hpp"
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

//Default Board is 3
Board::Board(){
    numRows = 3;
    numCols = 3;
    panel = new int*[numRows];
    for (int i = 0; i < numRows; i++){
      panel[i] = new int[numCols];
      for (int j = 0; j < numCols; j++){
        panel[i][j] = 0;
      }
    }
    target = 1024;
    max = 0;
}

//Creates a board with m rows and m columns
Board::Board(int m){
  if (m >= 1){
    numRows = m;
    numCols = m;
  }
  else{
    numRows = 3;
    numCols = 3;
  }

  panel = new int*[numRows];
  for (int i = 0; i < numRows; i++){
    panel[i] = new int[numCols];
  }

  target = 1024;
  max = 0;
}

//create a board with m rows and n columns
Board::Board(int m, int n){
  if (m >= 1 && n>= 1){
    numRows = m;
    numCols = n;
  }
  else {
    numRows = 3;
    numCols = 3;
  }

  panel = new int*[numRows];
  for (int i = 0; i < numRows; i++){
    panel[i] = new int[numCols];
  }
  target = 1024;
  max = 0;
}

//Deconstructor
Board::~Board(){
  for (int i = 0; i < numRows; i++){
    delete [] panel[i];
  }
  delete [] panel;
  panel = nullptr;
}

void Board::print() const {
  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numCols; j++){
      std::cout << "+----";
    }
    std::cout << "+" << '\n';

    for (int j = 0; j < numCols; j++){
      if (panel[i][j] > 0 && panel[i][j] < 1024)
        std::cout << "|" << std::setw(4) << panel[i][j];
      else std::cout << "|    ";
    }
    std::cout << "|" << '\n';
  }
  for (int j = 0; j < numCols; j++){
    std::cout << "+----";
  }
  std::cout << "+" << '\n';
}

bool Board::noAdjacentSameValue() const {
    for (int row = 0; row < numRows; row++)
        for (int col = 0; col < numCols-1; col++)
            if (panel[row][col] == panel[row][col+1])
               return false;
      //No two cells share same value in horizontal direction
    for (int col = 0; col < numCols; col++)
        for (int row = 0; row < numRows-1; row++)
            if (panel[row][col] == panel[row+1][col])
               return false;

    return true;
}

void Board::selectRandomCell(){
  srand(time(NULL));
  int zeros = 0;

  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numCols; j++){
      if (panel[i][j] == 0) zeros++;
    }
  }

  std::cout << zeros << '\n';
  std::cout << noAdjacentSameValue() << '\n';
  //If there are no more empty cells and no adjacent cells have the same value, end the game
  if (zeros == 0 && noAdjacentSameValue()){
    std::cout << "Game over. Try again." << '\n';
    std::exit(0);
  }
  std::cout << "g" << '\n';

  //Creates a vector storing all the empty empty cells
  std::vector <int> empty_cells;
  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numCols; j++){
      if (panel[i][j] == 0){
        empty_cells.push_back(numCols * i + j);
      }
    }
  }

  //Randomly pick an empty cell and sets its value to 1
  int random = rand() % empty_cells.size();
  int row = empty_cells[random] / numCols;
  int col = empty_cells[random] % numCols;

  panel[row][col] = 1;
  print();

  //Checks if the game is over after setting an empty cell to 1
  if (noAdjacentSameValue()){
    std::cout << "Game over. Try again." << '\n';
    std::exit(0);
  }
}

void Board::pressUp(){
  std::vector<int> nonZeros;
  // in each column, store the values that are not equal to zero
  for (int col = 0; col < numCols; col++){

    // store from the top to the bottom
    for (int row = 0; row < numRows; row++){
      if (panel[row][col] != 0) {
        nonZeros.push_back(panel[row][col]);
      }
    }

    // keeps track of the current index of nonZeros
    int i = 0;
    int size = nonZeros.size();

    // merge the identical values
    while (i < size-1){
      if (nonZeros[i] == nonZeros[i+1]){
        // if values are equal, double the first one and set the second one to 0
        nonZeros[i] *= 2;

        if (max < nonZeros[i])
          max = nonZeros[i];

        nonZeros[i+1] = 0;

        // skip the value that became zero
        i+=2;
      }
      else {
        i++;
      }
    }

    // update the panel with the merged column
    int row = 0;
    for (int i = 0; i < size; i++){
        if (nonZeros[i] != 0){
          // if the value is not equal to zero, update the panel and
          // move onto the next row
          panel[row][col] = nonZeros[i];
          row++;
        }
    }
    // if the rows have not all been filled, pad the column with zeros
    while (row < numRows) {
      panel[row][col] = 0;
      row++;
    }
    //reset the vector containing nonZeros for the next column
    nonZeros.clear();

  }

  int row, col;
  selectRandomCell();
}

void Board::pressDown(){
  std::vector<int> nonZeros;
  // in each column, store the values that are not equal to zero
  for (int col = 0; col < numCols; col++){

    // store from the bottom to the top
    for (int row = numRows-1; row >= 0; row--){
      if (panel[row][col] != 0) {
        nonZeros.push_back(panel[row][col]);
      }
    }

    // keeps track of the current index of nonZeros
    int i = 0;
    int size = nonZeros.size();

    // merge the identical values
    while (i < size-1){
      if (nonZeros[i] == nonZeros[i+1]){
        // if values are equal, double the first one and set the second one to 0
        nonZeros[i] *= 2;

        if (max < nonZeros[i])
          max = nonZeros[i];

        nonZeros[i+1] = 0;

        // skip the value that became zero
        i+=2;
      }
      else {
        i++;
      }
    }

    // update the panel with the merged column
    int row = numRows-1;
    for (int i = 0; i < size; i++){
        if (nonZeros[i] != 0){
          // if the value is not equal to zero, update the panel and
          // move onto the next row
          panel[row][col] = nonZeros[i];
          row--;
        }
    }
    // if the rows have not all been filled, pad the column with zeros
    while (row >= 0) {
      panel[row][col] = 0;
      row--;
    }
    //reset the vector containing nonZeros for the next column
    nonZeros.clear();
  }

  int row, col;
  selectRandomCell();
}

void Board::pressLeft(){
  std::vector<int> nonZeros;
  // in each row, store the values that are not equal to zero
  for (int row = 0; row < numRows; row++){

    // store from the left to the right
    for (int col = 0; col < numCols; col++){
      if (panel[row][col] != 0) {
        nonZeros.push_back(panel[row][col]);
      }
    }

    // keeps track of the current index of nonZeros
    int i = 0;
    int size = nonZeros.size();

    // merge the identical values
    while (i < size-1){
      if (nonZeros[i] == nonZeros[i+1]){
        // if values are equal, double the first one and set the second one to 0
        nonZeros[i] *= 2;

        if (max < nonZeros[i])
          max = nonZeros[i];

        nonZeros[i+1] = 0;

        // skip the value that became zero
        i+=2;
      }
      else {
        i++;
      }
    }

    // update the panel with the merged column
    int col = 0;
    for (int i = 0; i < size; i++){
        if (nonZeros[i] != 0){
          // if the value is not equal to zero, update the panel and
          // move onto the next row
          panel[row][col] = nonZeros[i];
          col++;
        }
    }
    // if the rows have not all been filled, pad the column with zeros
    while (col < numCols) {
      panel[row][col] = 0;
      col++;
    }
    //reset the vector containing nonZeros for the next column
    nonZeros.clear();
  }
  int row, col;
  selectRandomCell();
}

void Board::pressRight(){
  std::vector<int> nonZeros;
  // in each row, store the values that are not equal to zero
  for (int row = 0; row < numRows; row++){

    // store from the right to the left
    for (int col = numCols-1; col >= 0; col--){
      if (panel[row][col] != 0) {
        nonZeros.push_back(panel[row][col]);
      }
    }

    // keeps track of the current index of nonZeros
    int i = 0;
    int size = nonZeros.size();

    // merge the identical values
    while (i < size-1){
      if (nonZeros[i] == nonZeros[i+1]){
        // if values are equal, double the first one and set the second one to 0
        nonZeros[i] *= 2;

        if (max < nonZeros[i])
          max = nonZeros[i];

        nonZeros[i+1] = 0;

        // skip the value that became zero
        i+=2;
      }
      else {
        i++;
      }
    }

    // update the panel with the merged column
    int col = numCols-1;
    for (int i = 0; i < size; i++){
        if (nonZeros[i] != 0){
          // if the value is not equal to zero, update the panel and
          // move onto the next row
          panel[row][col] = nonZeros[i];
          col--;
        }
    }
    // if the rows have not all been filled, pad the column with zeros
    while (col >= 0) {
      panel[row][col] = 0;
      col--;
    }
    //reset the vector containing nonZeros for the next column
    nonZeros.clear();
  }

  int row, col;
  selectRandomCell();
}

void Board::print_round(int round, std::string move) const{
  std::cout << "Round" << std::setw(5) << round << ": Press " << move << ". Goal: " << std::setw(4) << target << '\n';
}

bool Board::validate(char move){
  if (move == 'A'){
    for (int j = 0; j < numCols; j++){
      // check if there is at least one column that can be
      // moved up
      for (int i = 0; i < numRows-1; i++){
        if (panel[i][j] == 0) return true;
        if (panel[i][j] == panel[i+1][j]) return true;
      }
    }
  }
  if (move == 'B'){
    for (int j = 0; j < numCols; j++){
      for (int i = numRows-1; i > 0; i--){
        if (panel[i][j] == 0) return true;
        if (panel[i][j] == panel[i-1][j]) return true;
      }
    }
  }
  if (move == 'D'){
    for (int i = 0; i < numRows; i++){
      for (int j = 0; j < numCols-1; j++){
        if (panel[i][j] == 0) return true;
        if (panel[i][j] == panel[i][j+1]) return true;
      }
    }
  }
  if (move == 'C'){
    for (int i = 0; i < numRows; i++){
      for (int j = numCols-1; j > 0; j--){
        if (panel[i][j] == 0) return true;
        if (panel[i][j] == panel[i][j-1]) return true;
      }
    }
  }

  return false;
}

void Board::start(){
    int row, col;
    //Randomly places two 1's into the panel to begin the game
    selectRandomCell();
    selectRandomCell();
    //each loop is a round: asks for input and makes a move depending on the input
    int round = 1;
    while (true){
      char move;
      // if the first value is esc, check if it was an arrow key
      if (getchar() == '\033') {
        getchar(); // skip the [
        move = getchar();

        bool valid = false;

        switch(move) {
          // A -> up
          case 'A':
            valid = true;
            print_round(round, "UP");
            pressUp();
            break;
          // B -> down
          case 'B':
            valid = true;
            print_round(round, "DOWN");
            pressDown();
            break;
          // C -> right
          case 'C':
            valid = true;
            print_round(round, "RIGHT");
            pressRight();
            break;
          // D -> left
          case 'D':
            valid = true;
            print_round(round, "LEFT");
            pressLeft();
            break;
          // otherwise, the move is not valid
          default:
            std::cout << "Enter a valid move" << '\n';
        }
        if (valid){
          round += 1;
          if (max == target){
            std::cout << "Congratulations!" << '\n';
            std::exit(0);
          }
        }
      }
    }
}
