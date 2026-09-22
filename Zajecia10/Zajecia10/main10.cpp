#include <iostream>

using namespace std;

class Actor
{

};


struct Point
{
	float x = 0.0f;
	float y = 0.0f;
};

struct Damage
{
	float value;
	int DamageType;
	Point location;
	Actor* Instigator;
	Actor* Victim;

	int effectType;

};

void SetLocation(const Point& point)
{
	///
}

void ApplyDamage(const Damage& damage)
{
	///
}

void GetDamage()
{
	///
}

int main() 
{
	Point p1;
	p1.x = 3.0;
	p1.y = 5.0;

	Damage damage;
	damage.value = 10;
	damage.location = p1;

	ApplyDamage(damage);

	return 0;
}