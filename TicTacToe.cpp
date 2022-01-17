/* Name: Gary Tsang
   Description: This program is a TicTacToe game that contains single
   				player and multiplayer mode
   Input: input of desired game mode, selection of which box to insert
   		  an X or O
   Output: game board result throughout the game and announces the winner
*/

/* Algorithm for program
	1. Greet the user with a welcome message
	2. Prompt user with menu of which game mode they desire
	3. Have Player X select the box on the game board then switch to
	   Player O or AI/Computer
	4. Continue the rotation until X or O has won or there is a tie
	5. Once game ends, prompt user if they want to continue or exit game
*/

//libraries used in program
#include <iostream>
#include <iomanip>

using namespace std;

//global const
const int cols3 = 3;

//function prototypes
void gameBoard(char [][cols3], int, int);
void singlePlayer(char [][cols3]);
void multiplayer(char [][cols3]);
void ComputerAI(char [][cols3], int, int);
bool status(char [][cols3], bool &);
void resetBoard(char [][cols3]);


int main()
{
	//declaration of variables
	const int rows = 3, cols = 3;
	int modes = 0, squarenumSP = 0, squarenumAI_MP = 0;
	bool winner = false;
	char response = '0';
	char board[rows][cols] = {{'1', '2', '3'}, {'4', '5', '6'},
							  {'7', '8', '9'}};

	//welcome message
	cout << setw(37) << setfill('X') << "\n" << setfill (' ')
		 << "{" << setw(32) << "Welcome to the TicTacToe Game!"
		 << setw(4) << "}\n" << setw(37) << setfill('O') << "\n"
		 << setfill (' ');

	//do...while loop for when user wants to play again
	do{
		//do...while loop for if game mode selected is invalid
		do{
			//menu to select game mode
			cout << "\nMain Menu:\n1. Single Player with AI.\n2. Multiplayer.\n"
					"3. Exit Game.\n>>> ";
			cin >> modes;

			//single player mode against AI/Computer
			if (modes == 1)
			{
				//do...while loop for when there is no winner yet and
				//board hasn't been filled up
				do{
					//load game board for Player X
					gameBoard(board, rows, cols);

					//Player X's turn
					singlePlayer(board);

					//counter for Player X for how many moves they made
					squarenumSP++;

					//shows which box X was placed in
					gameBoard(board, rows, cols);

					//after each move check if there is a winning pattern
					if (status(board, winner))
					{
						//if winning pattern is declared then game ends
						//and results are revealed
						gameBoard(board, rows, cols);
						break;
					}

					//since the AI can use up to 4 moves in the rotation,
					//after it's 4th move the game will end
					/* if the math is done right Player X has 5 moves
					   (because of first turn) and the AI has 4 moves
					   (second turn) since there are only 9 boxes in a
					   TicTacToe game board
					*/
					if (squarenumAI_MP == 4)
					{
						break;
					}

					//AI/computer's turn
					ComputerAI(board, rows, cols);

					//counter for AI for how many moves it made
					squarenumAI_MP++;

					//after each move check if there is a winning pattern
					if (status(board, winner))
					{
						//if winning pattern is declared then game ends
						//and results are revealed
						gameBoard(board, rows, cols);
						break;
					}
				}while (!status(board, winner) || (squarenumSP < 6 && squarenumAI_MP < 5));

			}
			else if (modes == 2) //multiplayer mode against friend
			{
				//do...while loop for when there is no winner yet and
				//board hasn't been filled up
				do{
					//load game board for Player X
					gameBoard(board, rows, cols);

					//Player X's turn
					singlePlayer(board);

					//counter for Player X for how many moves they made
					squarenumSP++;

					//shows which box X was placed in
					gameBoard(board, rows, cols);

					//after each move check if there is a winning pattern
					if (status(board, winner))
					{
						gameBoard(board, rows, cols);
						break;
					}

					//since Player O can use up to 4 moves in the rotation,
					//after it's 4th move the game will end
					if (squarenumAI_MP == 4)
					{
						break;
					}

					//Player O's turn
					multiplayer(board);

					//counter for Player O for how many moves they made
					squarenumAI_MP++;

					//after each move check if there is a winning pattern
					if (status(board, winner))
					{
						gameBoard(board, rows, cols);
						break;
					}
				}while (!status(board, winner) || (squarenumSP < 6 && squarenumAI_MP < 5));

			}
			else if (modes == 3)
			{
				//if user decides to quit the game from the menu
				cout << "Thank you for playing\n";
				return 0;
			}
			else //when input is not 1,2, or 3
			{
				cout << "\nInvalid input. Try again!";
			}
		}while(modes != 1 && modes != 2 && modes != 3);

		//there is no winner after the game board is filled with X and O
		if (!status(board, winner))
		{
			//announces the game is a tie
			cout << "\nIt is a tie!!\n";
			//shows result of the board
			gameBoard(board, rows, cols);
		}

		//do...while loop for when response selected is invalid
		do{
			//prompts the user if they want to play again
			cout << "Do you want to play again? y/Y/n/N\n";
			cin >> response;

			//if yes
			if (response == 'y' || response == 'Y')
			{
				//clear the board and counters
				resetBoard(board);
				squarenumSP = 0;
				squarenumAI_MP = 0;
			}
			//if no
			else if (response == 'n' || response == 'N')
			{
				cout << "Thank you for playing!";
				return 0;
			}
			//if response is not yes nor no
			else if (response != 'n' && response != 'N' &&
					 response != 'y' && response != 'Y')
			{
				cout << "Response invalid, try again.\n";
			}
		}while(response != 'n' && response != 'N' &&
			   response != 'y' && response != 'Y');

	  //if user wants to play again
	}while (response == 'y' || response == 'Y');

	return 0;
}


/* gameBoard - create the TicTacToe game map
   Parameters -
   char board[][cols3] - the array to create the game board
   int rows - how many rows for the TicTacToe board
   int cols - how many columns for the TicTacToe board
*/
void gameBoard(char board[][cols3], int rows, int cols){

	//loop to create the TicTacToe game board
	for(int i = 0; i < rows; i++)
	{
		cout << " " << setw(12) << setfill ('-') << "\n";

		for(int j = 0; j < cols; j++)
		{
			cout << "| " << board[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << " " << setw(12) << setfill ('-') << "\n";
}


/* singlePlayer - controls for player X
   Parameters -
   char board[][cols3] - array for identifying the box location for where
   						 the user wants to place the X
*/
void singlePlayer(char board[][cols3]){
	//declaration of variables
	char squareX = '0';
	bool selectionX = false;

	//do...while loop to check if the box the user selected is occupied
	//with an X or O
	do{
		//prompt's user for where they want to place the X
		cout << "\nPlayer X turn, Make a selection: ";
		cin >> squareX;

		//if user selects box 1
		if (squareX == '1')
		{
			//if that box already has an X or O
			if (board[0][0] == 'O' || board[0][0] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else //if box is empty and not filled, mark it with X
			{
				board[0][0] = 'X';
				selectionX = true;
			}
		}

		//(boxes 2 - 9 works the same as box 1)
		if (squareX == '2')
		{
			if (board[0][1] == 'O' || board[0][1] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[0][1] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '3')
		{
			if (board[0][2] == 'O' || board[0][2] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[0][2] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '4')
		{
			if (board[1][0] == 'O' || board[1][0] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[1][0] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '5')
		{
			if (board[1][1] == 'O' || board[1][1] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[1][1] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '6')
		{
			if (board[1][2] == 'O' || board[1][2] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[1][2] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '7')
		{
			if (board[2][0] == 'O' || board[2][0] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[2][0] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '8')
		{
			if (board[2][1] == 'O' || board[2][1] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[2][1] = 'X';
				selectionX = true;
			}
		}

		if (squareX == '9')
		{
			if (board[2][2] == 'O' || board[2][2] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionX = false;
			}
			else
			{
				board[2][2] = 'X';
				selectionX = true;
			}
		}

		//if the box input the user entered is invalid
		if (squareX < '1' || squareX > '9'|| cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			selectionX = false;

			//if the user enters an invalid box number
			if (squareX < '1' || squareX > '9')
			{
				cout << "\nYour selection must be between 1 and 9\n";
			}
			else //if user enters anything besides a number
			{
				cout << "\nYou can enter numbers only!\n";
			}
		}

	}while(selectionX == false);

}


/* multiplayer - controls for Player O
   Parameters -
   char board[][cols3] - array for identifying the box location for where
   						 the user wants to place the O
*/
void multiplayer(char board[][cols3]){
	//decalration of variables
	char squareO = '0';
	bool selectionO = false;

	//do...while loop to check if the box the user selected is occupied
	//with an X or O
	do{
		//prompt's user for where they want to place the O
		cout << "\nPlayer O turn, Make a selection: ";
		cin >> squareO;

		//if user selects box 1
		if (squareO == '1')
		{
			//if that box already has an X or O
			if (board[0][0] == 'O' || board[0][0] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else //if box is empty and not filled, mark it with O
			{
				board[0][0] = 'O';
				selectionO = true;
			}
		}

		//(boxes 2 - 9 works the same as box 1)
		if (squareO == '2')
		{
			if (board[0][1] == 'O' || board[0][1] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[0][1] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '3')
		{
			if (board[0][2] == 'O' || board[0][2] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[0][2] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '4')
		{
			if (board[1][0] == 'O' || board[1][0] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[1][0] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '5')
		{
			if (board[1][1] == 'O' || board[1][1] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[1][1] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '6')
		{
			if (board[1][2] == 'O' || board[1][2] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[1][2] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '7')
		{
			if (board[2][0] == 'O' || board[2][0] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[2][0] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '8')
		{
			if (board[2][1] == 'O' || board[2][1] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[2][1] = 'O';
				selectionO = true;
			}
		}

		if (squareO == '9')
		{
			if (board[2][2] == 'O' || board[2][2] == 'X')
			{
				cout << "This slot is already selected\n";
				selectionO = false;
			}
			else
			{
				board[2][2] = 'O';
				selectionO = true;
			}
		}

		if (squareO < '1' || squareO > '9' || cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			selectionO = false;

			if (squareO < '1' || squareO > '9')
			{
				cout << "\nYour selection must be between 1 and 9\n";
			}
			else if (cin.fail())
			{
				cout << "\nYou can enter numbers only!\n";
			}
		}

	}while(selectionO == false);
}


/* ComputerAI - controls for the AI/computer
   Parameters -
   char board[][cols3] - array for identifying the box location for where
   						 the AI wants to place the O
   int rows - identifies how many rows are on the board so randomization
   			  doesn't go out of bound
   int cols - identifies how many cols are on the board so randomization
   			  doesn't go out of bound
*/
void ComputerAI(char board[][cols3], int rows, int cols){
	//declaration of variables
	bool empty = true;

	cout << "\nComputer's turn!\n";

	//do...while loop to check if the box selected by the user is
	//occupied by an X or O. If occupied, find another box that is free
	do{
		//randomize the placeage of X or O
		int y = rand() % rows;
		int x = rand() % cols;

		//if there is an X or O occupying the box selected by the user
		if (board[y][x] == 'X' || board[y][x] == 'O')
		{
			cout << "This slot is already selected\n";
			empty = false;
		}
		else if (board[y][x] != 'X') //if box is not filled with X or O
		{
			board[y][x] = 'O';
			empty = true;
		}

	}while (empty == false);
}


/* status - winning conditions
   Parameters -
   char board[][cols3] - array for identifying the box location for where
   						 the X and O are placed
   bool &winner - trigger to see if the patterns on the board are winning
   				  conditions
   Return value - if there are any winning patterns on the board
*/
bool status(char board[][cols3], bool &winner){

	//WIN CONDITION FOR PLAYER X
	//horizontal wins
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}
	else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}
	else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}

	//--------------------------------------------------------------------
	//vertical wins
	else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}
	else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}
	else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}

	//--------------------------------------------------------------------
	//diagonal wins
	else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}
	else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
	{
		cout << "\nPlayer X Won!!\n";
		winner = true;
	}

	//WIN CONDITION FOR PLAYER O OR AI/COMPUTER
	//horizontal wins
	else if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}
	else if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}
	else if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}

	//--------------------------------------------------------------------
	//vertical wins
	else if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}
	else if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}
	else if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}

	//--------------------------------------------------------------------
	//diagonal wins
	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}
	else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
	{
		cout << "\nPlayer O Won!!\n";
		winner = true;
	}

	return winner;

}


/* resetBoard - clears the board for next game
   Parameters -
   char board[][cols3] - array for changing the X and O back to the box
   						 numbers thus clearing the board
*/
void resetBoard(char board[][cols3]){

	//resets the game board after a winner is decided, there is a tie, or
	//the user wants to play again
	if (board[0][0] == 'O' || board[0][0] == 'X')
	{
		board[0][0] = '1';
	}

	if (board[0][1] == 'O' || board[0][1] == 'X')
	{
		board[0][1] = '2';
	}

	if (board[0][2] == 'O' || board[0][2] == 'X')
	{
		board[0][2] = '3';
	}

	if (board[1][0] == 'O' || board[1][0] == 'X')
	{
		board[1][0] = '4';
	}

	if (board[1][1] == 'O' || board[1][1] == 'X')
	{
		board[1][1] = '5';
	}

	if (board[1][2] == 'O' || board[1][2] == 'X')
	{
		board[1][2] = '6';
	}

	if (board[2][0] == 'O' || board[2][0] == 'X')
	{
		board[2][0] = '7';
	}

	if (board[2][1] == 'O' || board[2][1] == 'X')
	{
		board[2][1] = '8';
	}

	if (board[2][2] == 'O' || board[2][2] == 'X')
	{
		board[2][2] = '9';
	}
}
