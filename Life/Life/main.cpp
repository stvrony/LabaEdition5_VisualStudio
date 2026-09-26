#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int BoardSize = 30;
string Board[BoardSize][BoardSize] = { " _ " };		// Board definition
string UpdatedBoard[BoardSize][BoardSize];			// Board prepared for updated generation
void PrintBoard();
void InitializeBoard();
void InsertRandNum();
int CountNeighbor(int i, int j);
void UpdateGeneration();


int main()
{

	InitializeBoard();
	InsertRandNum();
	while (true)
	{
		system("cls");
		PrintBoard();
		UpdateGeneration();
		cout << endl << endl;
		cout << "Press ENTER to move on to the next generation...";
		cin.get();
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
			Board[i][j] = " _ ";
		}
	}
}

void InsertRandNum()
{
	srand(time(0));
	
	for (int r = 0; r < 225; r++)
	{
		int random1 = rand() % BoardSize;
		int random2 = rand() % BoardSize;
		Board[random1][random2] = " X ";
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
	/*cout << endl;
	cout << "Neighbors Counter: " << count << endl;*/
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
				UpdatedBoard[i][j] = " _ ";
			}
		}
	}

	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			Board[i][j] = UpdatedBoard[i][j];
		}
	}
}