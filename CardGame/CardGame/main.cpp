#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>


using namespace std;

enum class Suit { Hearts, Diamonds, Spades, Clubs };
enum class Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

struct Card {
	Suit suit;
	Rank rank;
};

string toString(Suit s)
{
	switch (s)
	{
	case Suit::Hearts: return "Hearts";
	case Suit::Diamonds: return "Diamonds";
	case Suit::Spades: return "Spades";
	case Suit::Clubs: return "Clubs";
	default: return "?";
	}
}

string toString(Rank r)
{
	switch (r)
	{
	case Rank::Two: return "Two";
	case Rank::Three: return "Three";
	case Rank::Four: return "Four";
	case Rank::Five: return "Five";
	case Rank::Six: return "Six";
	case Rank::Seven: return "Seven";
	case Rank::Eight: return "Eight";
	case Rank::Nine: return "Nine";
	case Rank::Ten: return "Ten";
	case Rank::Jack: return "Jack";
	case Rank::Queen: return "Queen";
	case Rank::King: return "King";
	case Rank::Ace: return "Ace";
	default: return "?";
	}
}

int Value(Rank r)
{
	switch (r)
	{
	case Rank::Jack:
	case Rank::Queen:
	case Rank::King:
		return 10;
	case Rank::Ace:
		return 11;
	default:
		return static_cast<int>(r);
	}
}
int Value(Card c)
{
	return Value(c.rank);
}

string toString(Card c)
{
	return toString(c.rank) + " of " + toString(c.suit);
}

/*------------PLAYING CARDS DECK VECTOR------------*/
vector<Card> makeDeck()
{
	vector<Card> deck;
	for (int s = 0; s < 4; ++s)
	{
		for (int r = 2; r <= 14; ++r)
		{
			deck.push_back(Card{ static_cast<Suit>(s), static_cast<Rank>(r) });
		}
	}
	return deck;
}
/*------------CARD DRAW STRUCTURE------------*/
Card drawCard(vector<Card>& deck)
{
	Card c = deck.back();
	deck.pop_back();
	return c;
}

class Hand
{
public:

	/*------------ADDING CARDS TO HAND FUNCTION------------*/
	void add(Card c)
	{
		cards.push_back(c);
	}
	int total() const
	{
		int sum = 0;
		int aces = 0;

		for (const Card& c : cards)
		{
			sum += Value(c);
			if (c.rank == Rank::Ace)			// Adding Ace number drawn to reduce it value if needed.
			{
				aces++;
			}
		}

		while (sum > 21 && aces > 0)			// If any Ace in hand and sum is going to bust -> change Ace value from 11 to 1.
		{
			sum -= 10;
			aces--;
		}
		return sum;
		
	}
	/*------------CHECK IF HAND IS BUSTED------------*/
	bool isBust() const
	{
		return total() > 21;
	}

	/*------------CHECK IF HAND IS BLACKJACK------------*/
	bool isBlackjack() const
	{
		return cards.size() == 2 && total() == 21;
	}

	/*------------CARD PRINT------------*/
	void print() const
	{
		for (const Card& c : cards)
		{
			cout << " " << toString(c) << " (" << Value(c) << ")" << endl;
		}
	}
	
private:
	vector<Card> cards;
};

/*------------GAME RENDER FUNCTION DECLARATION------------*/
void showTable(const Hand& cashier, const Hand& player);

void startScreen();

int main()
{
	startScreen();
	bool restart = false;

	while (!restart)
	{
		/*------------SHUFFLING CARDS IN VECTOR------------*/
		vector<Card> deck = makeDeck();
		mt19937 rng(random_device{}());
		shuffle(deck.begin(), deck.end(), rng);

		/*------------PLAYERS HANDS CREATION------------*/
		Hand cashier;
		Hand player;

		/*------------DRAWING CARDS FROM VECTOR------------*/
		cashier.add(drawCard(deck));
		player.add(drawCard(deck));
		player.add(drawCard(deck));

		bool playerStand = false;
		while (player.total() < 21 && !playerStand)
		{
			system("cls");
			showTable(cashier, player);

			/*------------PLAYER TURN------------*/
			cout << endl << "1. Hit        2. Stand" << endl << endl;
			cout << "Next move: ";
			int choice;
			cin >> choice;

			if (choice == 1)
			{
				player.add(drawCard(deck));
			}
			else if (choice == 2)
			{
				playerStand = true;
			}
		}

		/*------------CASHIER TURN------------*/
		if (!player.isBust())
		{
			while (cashier.total() < 17)
			{
				cashier.add(drawCard(deck));
			}
		}

		/*------------GAME RENDER------------*/
		system("cls");
		showTable(cashier, player);
		cout << endl << endl;


		/*------------WIN CONDITIONS------------*/
		if (player.isBust())
		{
			cout << "Bust! Cashier won!" << endl;
			cout << "------------------" << endl;
		}
		else if (cashier.isBust())
		{
			cout << "Bust! Player won!" << endl;
			cout << "-----------------" << endl;
		}
		else if (cashier.isBlackjack() && cashier.total() > player.total())
		{
			cout << "Blackjack! Cashier won!" << endl;
			cout << "-----------------------" << endl;
		}
		else if (player.isBlackjack() && player.total() > cashier.total())
		{
			cout << "Blackjack! Player won!" << endl;
			cout << "----------------------" << endl;
		}
		else if (player.isBlackjack() && cashier.isBlackjack())
		{
			cout << "Blackjack draw!" << endl;
			cout << "---------------" << endl;
		}
		else if (cashier.total() > player.total())
		{
			cout << "Cashier won!" << endl;
			cout << "------------" << endl;
		}
		else if (cashier.total() == player.total())
		{
			cout << "Draw!" << endl;
			cout << "-----" << endl;
		}
		else if (player.total() > cashier.total())
		{
			cout << "Player won!" << endl;
			cout << "-----------" << endl;
		}

		/*------------RESTART?------------*/
		cout << endl << endl << endl << "Draw another hand? (Y / N)   ";
		string nextHand;
		cin >> nextHand;

		if (nextHand == "N" || nextHand == "n")
		{
			restart = true;
		}
		else if (nextHand == "Y" || nextHand == "y")
		{
			continue;
		}
	}
	return 0;
}

/*------------GAME RENDER INSTRUCTION------------*/
void showTable(const Hand& cashier, const Hand& player)
{
	cout << "CASHIER HAND" << endl << endl;
	cashier.print();
	cout << endl << "Score: " << cashier.total() << endl << endl;

	cout << endl << endl << "PLAYER HAND" << endl << endl;
	player.print();
	cout << endl << "Score: " << player.total() << endl << endl;
}

void startScreen()
{
	cout << endl << endl << "Welcome to the game of" << endl;
	cout << "     ~BLACKJACK~" << endl << endl;
	cout << endl << "A game where you can't win any money, but this time you don't lose any." << endl;
	cout << "In this simulator you can either hit or stay, without double downs and splits." << endl;
	cout << "Cause that would definitely be beyond my abilities (for now!)" << endl;
	cout << "Let's get some fun in this simple simulator. Enjoy!" << endl << endl;
	cout << endl << "Press ENTER to draw your cards...";
	cin.get();
}