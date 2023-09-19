#include "Mainpage.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Optionspage::Optionspage(float width, float height) {

	if (!font.loadFromFile("arial.ttf"))
	{

	}

	Options[0].setFont(font);
	Options[0].setFillColor(Color::Cyan);
	Options[0].setString("Save the Man");
	Options[0].setPosition(Vector2f(width / 2 - Options[0].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS_2 + 1) * 1)-Options[0].getGlobalBounds().height / 2));

	Options[1].setFont(font);
	Options[1].setFillColor(Color::White);
	Options[1].setString("Yet to decide");
	Options[1].setPosition(Vector2f(width / 2 - Options[1].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS_2 + 1) * 2)-Options[1].getGlobalBounds().height / 2));

	Options[2].setFont(font);
	Options[2].setFillColor(Color::White);
	Options[2].setString("Bingo");
	Options[2].setPosition(Vector2f(width / 2 - Options[2].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS_2 + 1) * 3)-Options[2].getGlobalBounds().height / 2));

	Options[3].setFont(font);
	Options[3].setFillColor(Color::White);
	Options[3].setString("Back");
	Options[3].setPosition(Vector2f(width / 2 - Options[3].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS_2 + 1) * 4)-Options[3].getGlobalBounds().height / 2));

	selected1 = 0;

}
Optionspage::~Optionspage() {}


void Optionspage::draw1(RenderWindow &window)
{
	for (int i = 0;i < MAX_NUMBER_OF_ITEMS_2;i++)
	{
		window.draw(Options[i]);
	}
}

void Optionspage::MoveUp1()
{
	if (selected1 - 1 >= 0)
	{
		Options[selected1].setFillColor(Color::White);
		selected1--;
		Options[selected1].setFillColor(Color::Cyan);
	}
}

void Optionspage::MoveDown1()
{
	if (selected1 + 1 < MAX_NUMBER_OF_ITEMS_2)
	{
		Options[selected1].setFillColor(Color::White);
		selected1++;
		Options[selected1].setFillColor(Color::Cyan);
	}

}