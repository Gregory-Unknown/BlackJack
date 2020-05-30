/*
Степанян Григорий
Visual Studio 2019

4.Согласно иерархии классов, которая представлена в методичке к уроку 3,
от класса Hand наследует класс GenericPlayer, который обобщенно представляет игрока,
ведь у нас будет два типа игроков - человек и компьютер. Создать класс GenericPlayer,
в который добавить поле name - имя игрока. Также добавить 3 метода:
    IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
    IsBoosted() - возвращает bool значение, есть ли у игрока перебор
    Bust() - выводит на экран имя игрока и объявляет, что у него перебор.
*/

#include <iostream>
#include <vector>

class Card
{
public:
	enum CardRank {
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};
	enum CardSuit { CLUBS, DIAMONDS, HEARTS, SPADES };

private:
	CardRank m_Rank;
	CardSuit m_Suit;
	bool m_IsFaceUp;
public:
	Card(CardRank rank = ACE, CardSuit suit = SPADES , bool isFaceUp = true) : m_Rank(rank), m_Suit(suit), m_IsFaceUp(isFaceUp)
	{

	}

	void Flip()
	{
		m_IsFaceUp = !(m_IsFaceUp);
	}

	int GetValue() const
	{
		int value = 0;
		if (m_IsFaceUp)
		{
			value = m_Rank;
			
			if (value > 10)
			{
				value = 10;
			}
		}
		return value;

	}
};

class Hand
{
protected:
	std::vector<Card*> m_Cards;

public:
	Hand()
	{
		m_Cards.reserve(7);
	}
	
	virtual ~Hand()
	{
		Clear();
	}


	void Add(Card* pCard)
	{
		m_Cards.push_back(pCard);
	}


	void Clear()
	{
		std::vector<Card*>::iterator iter = m_Cards.begin();
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
		{
			delete* iter;
			*iter = 0;
		}
		m_Cards.clear();
	}

	int GetTotal() const
	{
		if (m_Cards.empty())
		{
			return 0;
		}

		
		if (m_Cards.at(0)->GetValue() == 0)
		{
			return 0;
		}

		
		int total = 0;
		std::vector<Card*>::const_iterator iter;
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
		{
			total += (*iter)->GetValue();
		}

		
		bool containsAce = false;
		for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
		{
			if ((*iter)->GetValue() == Card::ACE)
			{
				containsAce = true;
			}
		}

		
		if (containsAce && total <= 11)
		{
			total += 10;
		}
		return total;
	}
};

class GenericPlayer : public Hand
{
private:
	std::string m_Name;
public:
	GenericPlayer(std::string name) : m_Name(name)
	{

	}
	~GenericPlayer()
	{ 

	}
	virtual bool IsHitting() const = 0;
	bool IsBoosted() const
	{
		return (GetTotal() > 21);
	}
	void Bust() const
	{
		std::cout << m_Name << " is boosted !" << std::endl;
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

