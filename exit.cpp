#include "Mainpage.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

//to close the game
EB::EB(float width, float height) {

	if (!font.loadFromFile("arial.ttf"))
	{

	}

	exits[0].setFont(font);
	exits[0].setFillColor(Color::Cyan);
	exits[0].setString("YES");
	exits[0].setPosition(Vector2f(width / (MAX_NUMBER_OF_ITEMS_3 + 3) * 1, height / 2 ));

	exits[1].setFont(font);
	exits[1].setFillColor(Color::White);
	exits[1].setString("NO");
	exits[1].setPosition(Vector2f(width / (MAX_NUMBER_OF_ITEMS_3 + 1) * 2, height / 2));

	exits1.setFont(font);
	exits1.setFillColor(Color::Red);
	exits1.setString("Are You Sure");
	exits1.setPosition(Vector2f(width / 6, height / 8 ));


	selected2 = 0;

}
EB::~EB() {}


void EB::drawe(RenderWindow& windowe)
{
	windowe.draw(exits1);
	for (int i = 0;i < MAX_NUMBER_OF_ITEMS_3;i++)
	{
		windowe.draw(exits[i]);
	}
}

void EB::left()
{
	if (selected2 - 1 >= 0)
	{
		exits[selected2].setFillColor(Color::White);
		selected2--;
		exits[selected2].setFillColor(Color::Cyan);
	}
}

void EB::right()
{
	if (selected2 + 1 < MAX_NUMBER_OF_ITEMS_2)
	{
		exits[selected2].setFillColor(Color::White);
		selected2++;
		exits[selected2].setFillColor(Color::Cyan);
	}

}

//for game over
GameOver::GameOver(float width, float height) {

	if (!fontgo.loadFromFile("arial.ttf"))
	{

	}

	textgo[0].setFont(fontgo);
	textgo[0].setFillColor(Color::Cyan);
	textgo[0].setString("Play Again");
	textgo[0].setPosition(Vector2f(width / 2 - textgo[0].getGlobalBounds().width / 2, 150));

	textgo[1].setFont(fontgo);
	textgo[1].setFillColor(Color::White);
	textgo[1].setString("Result");
	textgo[1].setPosition(Vector2f(width / 2 - textgo[1].getGlobalBounds().width / 2, 250));

	textgo[2].setFont(fontgo);
	textgo[2].setFillColor(Color::White);
	textgo[2].setString("Exit");
	textgo[2].setPosition(Vector2f(width / 2 - textgo[2].getGlobalBounds().width / 2, 350));


	selectedgo = 0;

}
GameOver::~GameOver() {}


void GameOver::drawgo(RenderWindow& windowe)
{
	for (int i = 0;i < MAX_NUMBER_OF_ITEMS;i++)
	{
		windowe.draw(textgo[i]);
	}
}

void GameOver::MoveUpgo()
{
	if (selectedgo - 1 >= 0)
	{
		textgo[selectedgo].setFillColor(Color::White);
		selectedgo--;
		textgo[selectedgo].setFillColor(Color::Cyan);
	}
}

void GameOver::MoveDowngo()
{
	if (selectedgo + 1 < MAX_NUMBER_OF_ITEMS)
	{
		textgo[selectedgo].setFillColor(Color::White);
		selectedgo++;
		textgo[selectedgo].setFillColor(Color::Cyan);
	}

}