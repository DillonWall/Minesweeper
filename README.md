# Minesweeper

## Overview
This program is a CLI implementation of the game Minesweeper.

The game consists of a grid of cells that represent a minefield
and the player trys to uncover all cells that are not a mine.

Uncovering all cells that are not mines wins, while uncovering
a cell that is a mine loses.


## Details
### Input
In the initial menu, entering 'b' 'i' or 'e' starts a beginner,
intermediate, or expert game respectively, and 'x' exits the program.

During gameplay, to uncover a cell you enter its coordinate
as 'X Y' where X is how far right the cell is and Y is how
far down the cell is. 

To mark a cell, it is very similar
but you start with a lowercase 'm', the command to mark is 'm X Y'

If you want to exit the game before finishing, enter 'exit'

### Output
Upon initial start, the program will display a message asking
the user to input the desired difficulty, or if they would
like to quit.

During gameplay, There is a grid of symbols represent cells
and numbered axis to help the user pick a coordinate.

The symbols for cells are: 
* '?' = covered
* 'M' = marked
* '-' = uncovered/blank
* '#' where # is a number 1 to 8 = number cell
* 'X' = mine/bomb. 

For readability, number cells are colored blue,
bombs are colored red, and marked cells are colored green.

After the user ends a game, it will output either a 'game over' message
or 'you win' message to report if they won, and go back to the 
initial start message asking for a difficulty.

  
## Installation
Open and run with Visual Studio 2022 (or your IDE of choice)

  
## Status
This project is finished.

  
## Screenshots
![Minesweeper](https://user-images.githubusercontent.com/49173127/166114801-2fc6ce08-be94-4770-be24-4da67dd3cd1c.png)

![image](https://user-images.githubusercontent.com/49173127/166114814-d472ac55-1dab-455e-973f-b856634f17d6.png)

![image](https://user-images.githubusercontent.com/49173127/166114819-74cfefd7-088e-4db2-87be-9870d58a756c.png)

![image](https://user-images.githubusercontent.com/49173127/166114822-c3b78ad5-cb7d-47e9-8ddd-fa1c8c7b47f7.png)
