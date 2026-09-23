#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;


enum Damage
{
	Fire,
	Water
};

struct DamageData
{
	float value;
	Damage damage;
	char character;
	int range;
};

int main()
{
	map <string, int> Ages;					// Dostęp -> O(log n)
	unordered_map <Damage, DamageData> Damage;	// Dostęp -> O(1)


	Damage["Donald"].range = 100;  ////////////////////////////////


	//	Dodawanie wartości
	Ages["Vladimir"] = 70;
	Ages["Donald"] = 80;
	Ages["Elon"] = 50;
	

	//	Odczyt z mapy
	cout << "Donald is " << Ages["Donald"] << " years old." << endl;	// O(log n)
	Ages["Donald"] = 82;
	cout << "Donald is " << Ages["Donald"] << " years old." << endl;

	// Iteracja po mapie
	for (auto it = Ages.begin(); it != Ages.end(); ++it)
	{
		cout << it->first << ": " << it->second << endl;
	}

	//	Sprawdzanie czy klucz istnieje w mapie
	if (Ages.find("Donald") != Ages.end())
	{
		cout << "Donald IS in the map!" << endl;
	}
	else
	{
		cout << "Donald IS NOT in the map!" << endl;
	}

	//	Aktualizacja mapy
	auto it = Ages.find("Donald");
	if (it != Ages.end())
	{
		it->second = 80;
	}

	return 0;

}