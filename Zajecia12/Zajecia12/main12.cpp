#include <iostream>

using namespace std;

int COUNTER = 0;


//	O(n)
int WyszukiwanieLiniowe(int tab[], int n, int value)
{
	for (int i = 0; i < n; ++i)
	{
		COUNTER++;
		if (tab[i] == value)
		{
			return i;
		}
	}
	return -1;
}

//	O(log n)
int WyszukiwanieBinarne(int tab[], int value, int begin, int end)
{
	if (begin > end)
	{
		return -1;
	}

	int middleIndex = begin + (end - begin) / 2;
	COUNTER++;
	if (tab[middleIndex] == value)	//  Element znaleziony
	{
		return middleIndex;
	}

	if (tab[middleIndex] < value)
	{
		return WyszukiwanieBinarne(tab, value, middleIndex + 1, end);	// Wywołanie rekurencyjne
	}
	else
	{
		return WyszukiwanieBinarne(tab, value, begin, middleIndex - 1);
	}
}

int selectionSort(int tab[], int size)
{

	for (int j = 0; j < size; ++j)
	{
		int minValue = tab[j];
		int minIndex = j;
		//	Szukam najmniejszego elementu, O(n)
		for (int i = j + 1; i < size; ++i)
		{
			if (tab[i] < minValue)
			{
				minValue = tab[i];
				minIndex = i;
			}
		}
		int temp = tab[j];
		tab[j] = minValue;
		tab[minIndex] = temp;
	}
	return 0;
}

int Partition(int tab[], int begin, int end)	//O(n)
{
	int pivot = tab[end];
	int minIndex = begin;

	for (int i = begin; i <= end; ++i)
	{

		if (tab[i] < pivot)
		{
			minIndex++;

			//	swap

			swap(tab[i], tab[minIndex]);
		}
	}

	swap(tab[minIndex+1], tab[end]);
	return minIndex + 1;
}

void QuickSort(int tab[], int begin, int end)
{
	if (begin >= end)
	{
		return;
	}
	
	int pivotIndex = Partition(tab, begin, end);

	QuickSort(tab, begin, pivotIndex - 1);
	QuickSort(tab, pivotIndex + 1, end);
}



int main()
{


	int Tab[] = {1, 6, 8, 2, 0, -11, 192, 45, 33, 5};
	int Tab2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	const int size = 100000;
	int BigArray[size];
	for (int i = 0; i < size; ++i)
	{
		BigArray[i] = i;
	}

	int searchedValue = 1;
	cout << WyszukiwanieLiniowe(BigArray, size, searchedValue) << endl;
	cout << "Counter: " << COUNTER << endl;
	COUNTER = 0;
	cout << WyszukiwanieBinarne(BigArray, searchedValue, 0, size-1) << endl;
	cout << "Counter: " << COUNTER << endl;
	COUNTER = 0;

	selectionSort(Tab, 10);
	cout << "Counter: " << COUNTER << endl;
	COUNTER = 0;

	QuickSort(BigArray, 0, size-1);
	cout << "Counter: " << COUNTER << endl;
	COUNTER = 0;

	return 0;
}