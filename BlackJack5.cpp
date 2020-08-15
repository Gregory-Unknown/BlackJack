/*
Степанян Григорий
Visual Studio 2019

3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. Класс Deck имеет 4 метода:
	-vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
	-void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
	-vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
	-void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать
Обратите внимание на применение полиморфизма. В каких методах применяется этот принцип ООП?
4. Реализовать класс Game, который представляет собой основной процесс игры. У этого класса будет 3 поля:
	-колода карт
	-рука дилера
	-вектор игроков.
Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков. 
В конструкторе создается колода карт и затем перемешивается.
Также класс имеет один метод play().
В этом методе раздаются каждому игроку по две стартовые карты, а первая карта дилера прячется.
Далее выводится на экран информация о картах каждого игра, в т.ч. и для дилера.
Затем раздаются игрокам дополнительные карты. 
Потом показывается первая карта дилера и дилер набирает карты, если ему надо.\
После этого выводится сообщение, кто победил, а кто проиграл.
В конце руки всех игроков очищаются.
5. Написать функцию main() к игре Блекджек.
В этой функции вводятся имена игроков. 
Создается объект класса Game и запускается игровой процесс.
Предусмотреть возможность повторной игры.

*/

#include <iostream>   
#include <string>   
#include <vector>   
#include <algorithm>
#include <ctime>
#include <cstdlib>


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
		const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
		const std::string SUITS[] = { "c", "d", "h", "s" };

		if (aCard.m_IsFaceUp)
		{
			os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
		}
		else
		{
			os << "XX";
		}

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
	bool IsBusted() const
	{
		return (GetTotal() > 21);
	}
	void Bust() const
	{
		std::cout << m_Name << " is boosted !" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer)
	{
		os << aGenericPlayer.m_Name << ":\t";

		std::vector<Card*>::const_iterator pCard;
		if (!aGenericPlayer.m_Cards.empty())
		{
			for (pCard = aGenericPlayer.m_Cards.begin();
				pCard != aGenericPlayer.m_Cards.end();
				++pCard)
			{
				os << *(*pCard) << "\t";
			}


			if (aGenericPlayer.GetTotal() != 0)
			{
				std::cout << "(" << aGenericPlayer.GetTotal() << ")";
			}
		}
		else
		{
			os << "<empty>";
		}

		return os;
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

class Deck : public Hand
{
public:
	Deck()
	{
		m_Cards.reserve(52);
		Populate();
	}

	virtual ~Deck()
	{

	}
	
	void Populate()
	{
		Clear();
		for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
		{
			for (int r = Card::ACE; r <= Card::KING; ++r)
			{
				Add(new Card(static_cast<Card::CardRank>(r),
					static_cast<Card::CardSuit>(s)));
			}
		}

	}

	void Shuffle()
	{
		std::random_shuffle(m_Cards.begin(), m_Cards.end());
	}

	void Deal(Hand& aHand)
	{
		if (!m_Cards.empty())
		{
			aHand.Add(m_Cards.back());
			m_Cards.pop_back();
		}
		else
		{
			std::cout << "Out of cards. Unable to deal.";
		}

	}

	void AdditionalCards(GenericPlayer& aGenericPlayer)
	{
		std::cout << std::endl;
		
		while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
		{
			Deal(aGenericPlayer);
			std::cout << aGenericPlayer << std::endl;

			if (aGenericPlayer.IsBusted())
			{
				aGenericPlayer.Bust();
			}
		}

	}
};

class Game
{
public:
	Game(const std::vector<std::string>& names)
	{
		std::vector<std::string>::const_iterator pName;
		for (pName = names.begin(); pName != names.end(); ++pName)
		{
			m_Players.push_back(Player(*pName));
		}

		srand(static_cast<unsigned int>(time(0)));
		m_Deck.Populate();
		m_Deck.Shuffle();

	}

	~Game()
	{

	}

	void Play()
	{
		std::vector<Player>::iterator pPlayer;
		for (int i = 0; i < 2; ++i)
		{
			for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
			{
				m_Deck.Deal(*pPlayer);
			}
			m_Deck.Deal(m_House);
		}

		m_House.FlipFirstCard();

		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			std::cout << *pPlayer << std::endl;
		}
		std::cout << m_House << std::endl;

		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			m_Deck.AdditionalCards(*pPlayer);
		}

		m_House.FlipFirstCard();
		std::cout << std::endl << m_House;

		m_Deck.AdditionalCards(m_House);

		if (m_House.IsBusted())
		{
			for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
			{
				if (!(pPlayer->IsBusted()))
				{
					pPlayer->Win();
				}
			}
		}
		else
		{
			for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
				++pPlayer)
			{
				if (!(pPlayer->IsBusted()))
				{
					if (pPlayer->GetTotal() > m_House.GetTotal())
					{
						pPlayer->Win();
					}
					else if (pPlayer->GetTotal() < m_House.GetTotal())
					{
						pPlayer->Lose();
					}
					else
					{
						pPlayer->Push();
					}
				}
			}

		}

		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			pPlayer->Clear();
		}
		m_House.Clear();

	}

private:
	Deck m_Deck;
	House m_House;
	std::vector<Player> m_Players;
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

	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.Play();
		std::cout << "\nDo you want to play again? (Y/N): ";
		std::cin >> again;
	}
	return 0;
}

