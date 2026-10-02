#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

const int BoardSize = 30;
string Board[BoardSize][BoardSize] = { "   " };		// Board definition
string UpdatedBoard[BoardSize][BoardSize];			// Board prepared for updated generation
void PrintBoard();
void InitializeBoard();
int CountNeighbor(int i, int j);
void UpdateGeneration();
void GameIntro();
void RandomBoard();
void ManualInsert();
void InsertPattern(int startx, int starty, int pattern[][2], int patternSize);
void SelectPreset();
int density;
int setupChoice;

int Blinker[][2] = {
	{0, 0}, {0, 1}, {0, 2}
};

int Glider[][2] = {
	{0, 1},
	{1, 2},
	{2, 0}, {2, 1}, {2, 2}
};

int Block[][2] = {
	{0, 0}, {0, 1},
	{1, 0}, {1, 1}
};


int main()
{
	InitializeBoard();
	GameIntro();
	system("cls");
	cout << endl << "How do you want to start Your Game on 30x30 board?" << endl;
	cout << "1 - Random Cells" << endl;
	cout << "2 - Manual Coordinates" << endl;
	cout << "3 - Preset Patterns" << endl;
	cout << endl << "My choice is: ";
	cin >> setupChoice;

	switch (setupChoice)
	{
	case 1: RandomBoard();  break;
	case 2: ManualInsert(); break;
	case 3: SelectPreset(); break;
	}
	cin.ignore();
	system("cls");
	cout << endl << "Creating Your next generation of cells..." << endl << endl;
	cout << "Press ENTER to generate your board!";
	cin.get();
	while (true)
	{
		system("cls");
		PrintBoard();
		UpdateGeneration();
		cout << endl << endl;
		cout << "Press any key to move on, or ESC to exit...";
		char Key = _getch();
		if (Key == 27)
		{
			cout << endl << endl << "Thanks for playing and see you next time!" << endl << endl;
			break;
		}
		//cin.get();
	}
	return 0;
}


void PrintBoard() 
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			cout << Board[i][j];
		}
		cout << endl;
	}

}

void InitializeBoard()
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			Board[i][j] = "   ";
		}
	}
}

int CountNeighbor(int i, int j)
{
	int count = 0;

	for (int movedi = -1; movedi <= 1; movedi++)
	{
		for (int movedj = -1; movedj <= 1; movedj++)	//	A loop designed to check the neighbors on the other side of the rolled-up board as well as adjacent neighbors
		{
			if (movedi == 0 && movedj == 0) continue;   //	The loop skips the space on the board occupied by the object whose neighbors we are checking

			int newi = (i + movedi + 30) % 30;			//	This is the row number, including the rolled-up board — +30 prevents a negative result
			int newj = (j + movedj + 30) % 30;			//	This is the column number, including the rolled-up board - %30 brings the result back into the 0–29 range

			if (Board[newi][newj] == " X ") count++;	//	If there is a neighbor on the other side of the board, it counts that one as well
		}
	}
	return count;
}

void UpdateGeneration()
{
	for (int i = 0; i < BoardSize; i++)		// Loop that count neighbors for every active object on board
	{
		for (int j = 0; j < BoardSize; j++)
		{
			int neighbors = CountNeighbor(i, j);
			//cout << " " << neighbors << " ";
			bool isAlive = (Board[i][j] == " X ");

			if (isAlive && (neighbors == 2 || neighbors == 3))
			{
				UpdatedBoard[i][j] = " X ";
			}
			else if (!isAlive && neighbors == 3)
			{
				UpdatedBoard[i][j] = " X ";
			}
			else
			{
				UpdatedBoard[i][j] = "   ";
			}
		}
	}

	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			Board[i][j] = UpdatedBoard[i][j];	// Refresh the board to display a new, updated board with a new generation of objects
		}
	}
}

void GameIntro()
{
	cout << " -------------------------------------------------------------" << endl;
	cout << "|                                                             |" << endl;
	cout << "|                      The Game of Life                       |" << endl;
	cout << "|                                                             |" << endl;
	cout << " -------------------------------------------------------------" << endl << endl << endl;
	cout << "The Game of Life is a Mathematical Dance of Evolution-Form Chaos to Order." << endl;
	cout << "This is a unique cellular automaton created in 1970 by mathematician John Conway." << endl;
	cout << "You don't need a player or a strategy here-all you have to do is set up the initial arrangement of cells, and the rest will unfold on its own according to three simple rules: " << endl << endl;
	cout << "- Loneliness: A cell with fewer than two neighbors dies." << endl;
	cout << "- Overcrowding: A cell with more than four neighbors dies." << endl;
	cout << "- Reproduction: An empty cell with exactly three neighbors comes to life." << endl << endl << endl;
	cout << "Press ENTER to start configurating your game!" << endl;
	cin.get();
}

void RandomBoard()
{
	system("cls");
	cout << "Enter the number of initial live cells: ";
	cin >> density;
	system("cls");
	srand(time(0));
	for (int r = 0; r < density; r++)
	{
		
		int random1 = rand() % BoardSize;
		int random2 = rand() % BoardSize;
		Board[random1][random2] = " X ";
	}
}

void ManualInsert()
{
	system("cls");
	cout << endl << "If you want to create live cells, enter their coordinates (X, Y)" << endl;
	cout << "If you want to finish entering values or skip this step, enter (-1, -1):" << endl << endl;
	int x = 0;
	int y = 0;

	while (true)
	{
		cout << "X: ";
		cin >> x;
		cout << "Y: ";
		cin >> y;
		cout << endl;
		if (x == -1 && y == -1)
		{
			break;
		}
		Board[x][y] = " X ";
	}
}

void SelectPreset()
{
	system("cls");
	while (true)
	{
		cout << endl << "Choose a preset pattern to add to your board:" << endl;
		cout << "1 - Blinker" << endl;
		cout << "2 - Glider" << endl;
		cout << "3 - Block" << endl;
		cout << "0 - Skip / Finish" << endl;
		cout << endl << "My choice is: ";
		int choice;
		cin >> choice;

		if (choice == 0)
		{
			return;
		}

		int startx = 0;
		int starty = 0;
		cout << endl << "Enter your starting position as coordinates (X, Y): " << endl;
		cout << "X: ";
		cin >> startx;
		cout << "Y: ";
		cin >> starty;

		switch (choice)
		{
		case 1:
			InsertPattern(startx, starty, Blinker, 3);
			break;
		case 2:
			InsertPattern(startx, starty, Glider, 5);
			break;
		case 3:
			InsertPattern(startx, starty, Block, 4);
			break;
		default:
			cout << "Invalid choice!" << endl;
		}
		cout << endl << "Do you want to add another pattern? (Y / N)";
		cout << endl << "My choice is: ";
		char again;
		cin >> again;
		if (again == 'N' || again == 'n')
		{
			break;
		}
	}
}

void InsertPattern(int startx, int starty, int pattern[][2], int patternSize)
{
	for (int t = 0; t < patternSize; t++)
	{
		int x = (startx + pattern[t][0] + BoardSize) % BoardSize;
		int y = (starty + pattern[t][1] + BoardSize) % BoardSize;
		Board[x][y] = " X ";
	}
}