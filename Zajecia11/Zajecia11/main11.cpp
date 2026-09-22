#include <iostream>

using namespace std;

enum DamageType
{
	Fire,
	Water,
	Electric,
	Toxic,
	Dark,
	Ice,
	Steel
};

enum class Elements
{
	Water,
	Fire,
	Earth,
	Air
};

struct Damage
{
	int value = 10;
	DamageType type;
};

void ApplyDamage(Damage damage)
{
	switch (damage.type)
	{
	case Fire:
		cout << "Damaged by FIRE for "<< damage.value << " HP points!" << endl;
		break;
	case Toxic:
		cout << "Damaged by TOXIC for " << damage.value << " HP points!" << endl;
		break;
	default:
		cout << "Unknown damage!" << endl;
	}
}

int main()
{
	
	Damage damage(100, Fire);
	Elements element = Elements::Fire;

	damage.type = Toxic;
	ApplyDamage(damage);
	

	return 0;
}