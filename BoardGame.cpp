#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
#include"Game.h"
#include"GameLogic.h"
#include"Mainpage.h"

using namespace std;
using namespace sf;

bool flagb = false;

int GoBack2(RenderWindow& window);

void boardgame(RenderWindow& window)
{
    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.3f, 0.3f);
    back.setScale(bg);
    //background end

	srand(static_cast<unsigned int>(time(0)));

	Texture t1;

	t1.loadFromFile("images/board.png");



	Sprite s;
	s.setTexture(t1);
	Vector2f scale(0.2145f, 0.2145f), s4(0.35f,0.35f);
	s.setScale(scale);
	s.setPosition(window.getSize().x / 2 - s.getGlobalBounds().width / 2, window.getSize().y / 2 - s.getGlobalBounds().height / 2);
	s.setPosition(0, 0);

	while (window.isOpen())
	{
        
		Event e;
		while (window.pollEvent(e))
		{
            window.clear();
            window.draw(back);
			if (e.type == Event::Closed)
			{
				flagb = false;
				GoBack2(window);
			}
            else if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                {
                    flagb = true;
                    GoBack2(window);
                }
            }
		}
        
        window.draw(s);
        window.display();

	}
}

int GoBack2(RenderWindow& window)
{
    RenderWindow window2(VideoMode(250, 100), "EXIT",Style::None);
    EB EB(static_cast<float>(window2.getSize().x), static_cast<float>(window2.getSize().y));

    while (true) {
        while (window2.isOpen()) {
            Event event1;
            while (window2.pollEvent(event1)) {
                
                if (event1.type == Event::KeyPressed)
                {
                    if (event1.key.code == Keyboard::Left)
                    {
                        EB.left();

                    }
                    if (event1.key.code == Keyboard::Right)
                    {
                        EB.right();

                    }
                    if (event1.key.code == Keyboard::Return)
                    {
                        switch (EB.GetPressValue1())
                        {
                        case 0:
                            cout << "YES" << endl;
                            if (flagb)
                            {
                                window2.close();
                                GameOptions(window);
                                break;
                            }
                            else
                            {
                                window2.close();
                                window.close();
                            }
                        case 1:
                            cout << "NO" << endl;
                            window2.close();
                            mainGame(window);
                            break;
                        }
                    }
                }
            }
            window2.clear(Color(64, 64, 64));
            EB.drawe(window2);
            window2.display();


        }
    }

    return 0;
}