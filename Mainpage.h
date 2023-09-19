#pragma once
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_ITEMS_2 4
#define MAX_NUMBER_OF_ITEMS_3 2

class Mainpage
{
public:

	Mainpage(float width, float height);
	~Mainpage();


	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressValue()
	{
		return selected;
	}

private:
	int selected;
	Font font;
	Text mainmenu[MAX_NUMBER_OF_ITEMS];
	bool hovering[MAX_NUMBER_OF_ITEMS];
};
class Optionspage
{
public:

	Optionspage(float width, float height);
	~Optionspage();

	void draw1(RenderWindow& window);
	void MoveUp1();
	void MoveDown1();
	int GetPressValue1()
	{
		return selected1;
	}

private:
	int selected1;
	Font font;
	Text Options[MAX_NUMBER_OF_ITEMS_2];
};
class EB
{
public:
	EB(float width, float height);
	~EB();
	
	void drawe(RenderWindow& windowe);
	void left();
	void right();
	int  GetPressValue1()
	{
		return selected2;
	}
private:
	int selected2;
	Font font;
	Text exits[MAX_NUMBER_OF_ITEMS_3],exits1;

};

class GameOver
{
public:
	GameOver(float width, float height);
	~GameOver();

	void drawgo(RenderWindow& window);
	void MoveUpgo();
	void MoveDowngo();
	int GetPressValuego()
	{
		return selectedgo;
	}
private:
	int selectedgo;
	Font fontgo;
	Text textgo[MAX_NUMBER_OF_ITEMS];

};


// MAINPAGE.h

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <SFML/Graphics/RenderWindow.hpp>
using namespace sf;

int MainPage(RenderWindow& window);
#endif

