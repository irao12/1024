# 1024 - Recreated Using C++
* Original game: [link](http://1024game.org)
* Played through the terminal

Given a board of squares where some have numbers, and the rest are empty...
*	You have to use the arrow keys to move the numbered squares in any direction
* Every time you make a move, a random, empty square will gain the value of 1.
*	During a move, any pair of squares that have the same value, in the selected direction that are next to each other will be merged (the values of the two squares will be added together and will become a single square).
* You win if any of the squares have a value of 1024 at any point, and you lose if there are no more empty squares!
* You lose if you are not able to merge anymore and all squares are taken up, and you only gain a 1 if the direction you have selected moves any of the squares!

#  How to Run
1. Clone/Download all the files from the repo
2. Enter the command ```make``` while in the repo directory
3. Enter ```./run``` to start the game
