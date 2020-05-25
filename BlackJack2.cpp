/*
Степанян Григорий
Visual Studio 2019

3.Реализовать класс Hand, который представляет собой коллекцию карт. 
В классе будет одно поле: вектор указателей карт (удобно использовать вектор, 
т.к. это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).
Также в классе Hand должно быть 3 метода:
	-метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
	-метод Clear, который очищает руку от карт
	-метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11).

*/

#include <iostream>
#include <vector>

class Card
{
public:
	enum CardSuit
	{
		SUIT_CLUB,
		SUIT_DIAMOND,
		SUIT_HEART,
		SUIT_SPADE,
		MAX_SUITS
	};

	enum CardRank
	{
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8,
		RANK_9,
		RANK_10,
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE,
		MAX_RANKS
	};

private:
	CardRank m_rank;
	CardSuit m_suit;
	bool m_IsFaceUp;
public:
	Card(CardRank rank = MAX_RANKS, CardSuit suit = MAX_SUITS, bool isFaceUp = false) : m_rank(rank), m_suit(suit), m_IsFaceUp(isFaceUp)
	{

	}

	bool Flip()
	{
		return (m_IsFaceUp == true) ? m_IsFaceUp = false : m_IsFaceUp = true;
	}

	int GetValue() const
	{
		switch (m_rank)
		{
		case Card::RANK_2: return 2;
		case Card::RANK_3: return 3;
		case Card::RANK_4: return 4;
		case Card::RANK_5: return 5;
		case Card::RANK_6: return 6;
		case Card::RANK_7: return 7;
		case Card::RANK_8: return 8;
		case Card::RANK_9: return 9;
		case Card::RANK_10: return 10;
		case Card::RANK_JACK: return 10;
		case Card::RANK_QUEEN: return 10;
		case Card::RANK_KING: return 10;
		case Card::RANK_ACE: return 1;
		default:
			break;
		}
	}
};

class Hand
{
private:
	std::vector<Card*> m_Cards;

public:
	
	void Add(Card* pCard)
	{
		m_Cards.push_back(pCard);
	}
	void Clear()
	{
		m_Cards.clear();
	}
	int GetTotal() 
	{
		int total = 0;
		for (int i = 0; i < m_Cards.size(); ++i)
		{
			total += m_Cards.at(i)->GetValue();
		}
		if (total + 10 <= 21)
		{
			Card::RANK_ACE == 11;
		}
		return total;
	}
};




int main()
{

	/*
	std::cout << "\t\tWelcome to Blackjack!\n\n";

	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		std::cout << "How many players? (1 - 7): ";
		std::cin >> numPlayers;
	}

	std::vector<std::string> names;
	std::string name;
	for (int i = 0; i < numPlayers; ++i)
	{
		std::cout << "Enter player name: ";
		std::cin >> name;
		names.push_back(name);
	}
	std::cout << std::endl;

	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.Play();
		std::cout << "\nDo you want to play again? (Y/N): ";
		std:: cin >> again;
	}*/

	return 0;

}