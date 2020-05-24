/*
Степанян Григорий
Visual Studio 2019

1.Создать класс Card, описывающий карту в игре БлэкДжек.
У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой).
Сделать поля масть и значение карты типом перечисления (enum).
Положение карты - тип bool. Также в этом классе должно быть два метода:
метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
*/
#include <iostream>

class Card
{
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
	bool m_faceCard;
public:
	Card(CardRank rank = MAX_RANKS, CardSuit suit = MAX_SUITS, bool faceCard = false) : m_rank(rank), m_suit(suit), m_faceCard(faceCard)
	{

	}

	bool Flip()
	{
		return (m_faceCard == true) ? false : true;
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


int main()
{
	Parallelogram parallelogram(10, 5);
	parallelogram.area();

	Circle circle(5);
	circle.area();

	Rectangle rectangle(10,5);
	rectangle.area();

	Square square(10);
	square.area();

	Rhombus romb(10,5);
	romb.area();

	Minivan minivan("Mercedez - Benz", "V-class");

	Fraction f(2, 4);
	f.print();
	Fraction f1(1, 2);
	f1.print();
	Fraction f2(2, 3);
	f2.print();
	Fraction f3 = f1 + f2;
	f3.print();
	Fraction f4 = f1 - f2;
	f4.print();
	Fraction f5 = f1 * f2;
	f5.print();
	Fraction f6 = f1 / f2;
	f6.print();
	Fraction f7 = -f1;
	f7.print();
	if (f1 == f)
	{
		std::cout << "f1 == f" << std::endl;
	}
	if (f1 != f2)
	{
		std::cout << "f1 != f2" << std::endl;
	}
	if (f1 < f2)
	{
		std::cout << "f1 < f2" << std::endl;
	}
	if (f2 > f)
	{
		std::cout << "f2 > f" << std::endl;
	}
	if (f2 <= f)
	{
		std::cout << "f2 <= f" << std::endl;
	}
	if (f1 >= f2)
	{
		std::cout << "f1 >= f2" << std::endl;
	}

	Card card;
	std::cout << card.GetValue() << std::endl;
	return 0;
}