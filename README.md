# 1024 - Recreated Using C++ 
* Original game: [link](http://1024game.org)
* Project done in CSCI 135 Software Analysis and Design I course
* Played through the terminal

Given a board of squares where some have numbers, and the rest are empty...
*	You can use the wasd keys to move the numbered squares in any direction (a for left, d for right, w for up, and s for down.) 
*	All numbered squares will move in the direction that you select, at the same time, as far as they can go without taking over the space of another square that has a value 
* Every time you move these squares, a random, empty square will gain the value of 1.
*	After moving them, any pair of squares that have the same value, in the selected direction that are next to each other will be merged (the values of the two squares will be added together and will become a single square). 
*	The squares do not increase in size-- you will gain an empty square after a merge. 
* If you happen to have more than two squares of the same value in the same direction that you are moving in and they are all next to each other, the equal pairs closest to the edge of the direction you had selected will merge first. 

When there are more than two identical values in adjacent cells (omitting empty cells), then the cells in the given direction have a higher precedence. For example, given a row in a 4-column board, where x is a space, as follows.
2 x 2 2
If we press LEFT, the leftmost two identical value cells (ignoring empty cell in between) are merged and we get
4 2 x x
If we press RIGHT, the rightmost two identical value cells are merged and we get
x x 2 4

* You win if any of the squares have a value of 1024 at any point, and you lose if there are no more empty squares!
* You lose if you are not able to merge anymore and all squares are taken up, and you only gain a 1 if the direction you have selected moves any of the squares! 

#  How to Run
1. Clone/Download all the files from the repo
2. Enter the command ```make``` while in the repo directory
3. Enter ```./run``` to start the game

