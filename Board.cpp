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
  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numCols; j++){
      if (panel[i][j] == 0) return false;

      //Check if the cells above and below are equal
      if (i > 0 && i < numRows-1){
        if (panel[i-1][j] == panel[i][j] || panel[i+1][j] == panel[i][j]){
          return false;
        }
      }

      //Check if the cells to the left and right are equal
      if (j > 0 && j < numCols -1){
        if (panel[i][j-1] == panel[i][j] || panel[i][j+1] == panel[i][j]){
          return false;
        }
      }
    }
  }
  return true;
}

void Board::selectRandomCell(int& row, int& col){
  srand(time(NULL));
  int zeros = 0;

  for (int i = 0; i < numRows; i++){
    for (int j = 0; j < numCols; j++){
      if (panel[i][j] == 0) zeros++;
    }
  }

  //If there are no more empty cells and no adjacent cells have the same value, end the game
  if (zeros == 0 && noAdjacentSameValue()){
    std::cout << "Game over. Try again." << '\n';
    std::exit(0);
  }

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
  row = empty_cells[random] / numCols;
  col = empty_cells[random] % numCols;

  panel[row][col] = 1;
  print();

  //Checks if the game is over after setting an empty cell to 1
  if (noAdjacentSameValue()){
    std::cout << "Game over. Try again." << '\n';
    std::exit(0);
  }
}

void Board::pressUp(){
  for (int i = 1; i < numRows; i++){
    for (int j = 0; j < numCols; j++){
      if (panel[i-1][j] == panel[i][j]){
        panel[i-1][j] = panel[i-1][j] * 2;
        panel[i][j] = 0;
      }
      else if (panel[i-1][j] == 0){
        for (int h = i-1; h >= 0; h--){
          if (panel[h][j] != 0){
            if (panel[h][j] == panel[i][j]){
              panel[h][j] *= 2;
              panel[i][j] = 0;
            }
            panel[h+1][j] = panel[i][j];
            panel[i][j] = 0;
            break;
          }
          if (h == 0 && panel[h][j] == 0){
            panel[h][j] = panel[i][j];
            panel[i][j] = 0;
          }
        }
      }

    }
  }
  int row, col;
  selectRandomCell(row, col);
}

void Board::pressLeft(){
  for (int i = 0; i < numRows; i++){
    for (int j = 1; j < numCols; j++){
      if (panel[i][j-1] == panel[i][j]){
        panel[i][j-1] += panel[i][j];
        panel[i][j] = 0;
      }
      else if (panel[i][j-1] == 0){
        for (int h = j-1; h >= 0; h--){
          if (panel[i][h] != 0){
            if (panel[i][h] == panel[i][j]){
              panel[i][h] *= 2;
              panel[i][j] = 0;
            }
            panel[i][h+1] = panel[i][j];
            panel[i][j] = 0;
            break;
          }
          if (h == 0 && panel[i][h] == 0){
            panel[i][h] = panel[i][j];
            panel[i][j] = 0;
          }
        }
      }
    }
  }
  int row, col;
  selectRandomCell(row, col);
}


void Board::pressDown(){
  for (int i = numRows-2; i >= 0; i--){
    for (int j = 0; j < numCols; j++){
      if (panel[i+1][j] == panel[i][j]){
        panel[i+1][j] += panel[i][j];
        panel[i][j] = 0;
      }
      else if (panel[i+1][j] == 0){
        for (int h = i+1; h < numRows; h++){
          if (panel[h][j] != 0){
            if (panel[h][j] == panel[i][j]){
              panel[h][j] *= 2;
              panel[i][j] = 0;
            }
            panel[h-1][j] = panel[i][j];
            panel[i][j] = 0;
            break;
          }
          if (h == numRows-1 && panel[h][j]==0){
            panel[h][j] = panel[i][j];
            panel[i][j] = 0;
          }
        }
      }
    }
  }
  int row, col;
  selectRandomCell(row, col);
}

void Board::pressRight(){
  for (int i = 0; i < numRows; i++){
    for (int j = numCols - 2; j >= 0; j--){
      if (panel[i][j+1] == panel[i][j]){
        panel[i][j+1] += panel[i][j];
        panel[i][j] = 0;
      }
      else if (panel[i][j+1] == 0){
        for (int h = j+1; h < numCols; h++){
          if (panel[i][h] != 0){
            if (panel[i][h] == panel[i][j]){
              panel[i][h] *= 2;
              panel[i][j] = 0;
            }
            panel[i][h-1] = panel[i][j];
            panel[i][j] = 0;
            break;
          }
          if (h == numCols-1 && panel[i][h]==0){
            panel[i][h] = panel[i][j];
            panel[i][j] = 0;
          }
        }
      }
    }
  }
  int row, col;
  selectRandomCell(row, col);
}
