/*
Степанян Григорий
Visual Studio 2019

3.Реализовать класс Player, который наследует от класса GenericPlayer. 
У этого класса будет 4 метода:
    -virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.
    Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false. 
    -void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
    -void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
    -void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.

4.Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer.
У него есть 2 метода:
	-virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта.
	Если у дилера не больше 16 очков, то он берет еще одну карту.
	-void FlipFirstCard() - метод переворачивает первую карту дилера.

5.Написать перегрузку оператора вывода для класса Card. 
Если карта перевернута рубашкой вверх (мы ее не видим), вывести ХХ, 
если мы ее видим, вывести масть и номинал карты.
Также для класса GenericPlayer написать перегрузку оператора вывода,
который должен отображать имя игрока и его карты, а также общую сумму очков его карт.
*/

#include <iostream>   
#include <string>   
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
	Card(CardRank rank = ACE, CardSuit suit = SPADES, bool isFaceUp = true) : m_Rank(rank), m_Suit(suit), m_IsFaceUp(isFaceUp)
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
	friend std::ostream& operator <<(std::ostream& os, const Card& aCard)
	{
		const std::string RANK[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K" };
		const std::string SUITS[] = { "c","d","h","s" };
		if (aCard.m_IsFaceUp)
			os << RANK[aCard.m_Rank] << SUITS[aCard.m_Suit];
		else
			os << "XX";
		return os;
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
protected:
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

class Player : public GenericPlayer
{
public:
    Player(std::string name = "") : GenericPlayer(name)
    {

    }
    virtual ~Player()
    {

    }
    virtual bool IsHitting() const
    {
        std::cout << m_Name << ", do  you want a hit? (Y/N):";
        char response;
        std::cin >> response;
        return(response == 'Y' || response == 'y');
    }
    void Win() const
    {
        std::cout << m_Name << " wins.\n";
    }
    void Lose() const
    {
        std::cout << m_Name << " loses.\n";
    }
    void Push() const
    {
        std::cout << m_Name << " pushes.\n";
    }
};

class House : public GenericPlayer
{
public:
	House(const std::string& name = "House") : GenericPlayer(name)
	{

	}
	virtual ~House()
	{

	}
	virtual bool IsHitting() const
	{
		return(GetTotal() <= 16);
	}
	void FlipFirstCard()
	{
		if (!(m_Cards.empty()))
			m_Cards.at(0)->Flip();
		else
			std::cout << "No card to flip!\n";
	}
};

int main()
{
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

	/*Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.Play();
		std::cout << "\nDo you want to play again? (Y/N): ";
		std::cin >> again;
	}*/
	return 0;
}

