#include "Mainpage.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Mainpage::Mainpage(float width, float height) {

	if (!font.loadFromFile("arial.ttf"))
	{
		
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		hovering[i] = false;
	}
	 
	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color::Cyan);
	mainmenu[0].setString("Play");
	mainmenu[0].setCharacterSize(40);
	mainmenu[0].setStyle(Text::Bold);
	mainmenu[0].setPosition(Vector2f(width / 2 - mainmenu[0].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS + 1) * 1 ) - mainmenu[0].getGlobalBounds().height / 2));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("Setting");
	mainmenu[1].setCharacterSize(40);
	mainmenu[1].setStyle(Text::Bold);
	mainmenu[1].setPosition(Vector2f(width / 2 - mainmenu[1].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS + 1) * 2)- mainmenu[1].getGlobalBounds().height / 2));

	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("Exit");
	mainmenu[2].setCharacterSize(40);
	mainmenu[2].setStyle(Text::Bold);
	mainmenu[2].setPosition(Vector2f(width / 2 - mainmenu[2].getGlobalBounds().width / 2, (height / (MAX_NUMBER_OF_ITEMS + 1) * 3)- mainmenu[2].getGlobalBounds().height / 2));

	selected = 0; 


}
Mainpage::~Mainpage(){}


void Mainpage::draw(RenderWindow& window) 
{
	for (int i = 0;i < MAX_NUMBER_OF_ITEMS;i++) 
	{
		window.draw(mainmenu[i]);
	}
}

void Mainpage::MoveUp() 
{
	if (selected - 1 >= 0)
	{
		mainmenu[selected].setFillColor(Color::White);
		selected--;
		mainmenu[selected].setFillColor(Color::Cyan);
	}
}

void Mainpage::MoveDown()
{
	if (selected + 1 < MAX_NUMBER_OF_ITEMS)
	{
		mainmenu[selected].setFillColor(Color::White);
		selected++;
		mainmenu[selected].setFillColor(Color::Cyan);
	}

}
/*void Mainpage::draw(RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		if (hovering[i]) {
			mainmenu[i].setFillColor(Color::Cyan);
		}
		else {
			mainmenu[i].setFillColor(Color::White);
		}
		window.draw(mainmenu[i]);
	}
}*/
