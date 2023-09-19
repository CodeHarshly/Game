#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include "Game.h"
#include "Mainpage.h"

int setting(RenderWindow& window);
int GoBack4(RenderWindow& window);
int setting(RenderWindow& window)
{
    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.35f, 0.35f);
    back.setScale(bg);
    //background end
    
    while (window.isOpen())
    {
        window.clear();
        window.draw(back);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GoBack4(window);
        }

        
        window.display();
    }

    return 0;
}


int GoBack4(RenderWindow& window)
{
    RenderWindow window2(VideoMode(250, 100), "EXIT", Style::None);
    EB EB(static_cast<float>(window2.getSize().x), static_cast<float>(window2.getSize().y));

    while (true) {
        while (window2.isOpen()) {
            Event event1;
            while (window2.pollEvent(event1)) {
                if (event1.type == Event::Closed) {
                    window2.close();
                    setting(window);
                    break;
                }
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
                            window2.close();
                            MainPage(window);
                            break;
                        case 1:
                            cout << "NO" << endl;
                            window2.close();
                            setting(window);
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
