
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Mainpage.h"
#include"BoardGame.h"
#include"GameLogic.h"
#include"Header.h"
#include"Setting.h"

using namespace std;
using namespace sf;

int GameOptions(RenderWindow& window);
int MainPage(RenderWindow& window);
int GoBack1(RenderWindow& window);

bool flag = false;

int main()
{
    RenderWindow window(VideoMode(320, 480), "My Game");
    MainPage(window);
}

int MainPage(RenderWindow& window)
{
    Mainpage Mainpage(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.35f, 0.35f);
    back.setScale(bg);
    //background end

    while (true) {
        while (window.isOpen()) {
            window.clear();
            window.draw(back);
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    flag = false;
                    GoBack1(window);
                    break;
                }
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        Mainpage.MoveUp();

                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        Mainpage.MoveDown();

                    }
                    if (event.key.code == Keyboard::Return)
                    {
                        switch (Mainpage.GetPressValue())
                        {
                        case 0:
                            cout << "Play button has been Pressed " << endl;
                            GameOptions(window);
                            break;
                        case 1:
                            cout << "setting button has been Pressed " << endl;
                            setting(window);
                            break;
                        case 2:
                            flag = false;
                            GoBack1(window);
                            break;

                        }
                    }
                }
                /*Vector2i mousePosition = Mouse::getPosition(window);

                for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
                    if (mainmenu[i].getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        hovering[i] = true;

                        if (Mouse::isButtonPressed(Mouse::Left)) {
                            switch (i) {
                            case 0:
                                cout << "Play button has been Pressed " << endl;
                                GameOptions(window);
                                break;
                            case 1:
                                cout << "setting button has been Pressed " << endl;
                                setting(window);
                                break;
                            case 2:
                                flag = false;
                                GoBack1(window);
                                break;
                            }
                        }
                    }
                    else {
                        hovering[i] = false;
                    }
                }*/
            }
            Mainpage.draw(window);
            window.display();


        }
    }
}

int GameOptions(RenderWindow& window)
{
    Optionspage Optionspage(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.35f, 0.35f);
    back.setScale(bg);
    //background end

    while (true) {
        while (window.isOpen()) {
            window.clear();
            window.draw(back);
            Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        flag = true;
                        GoBack1(window);
                        break;
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Up)
                        {
                            Optionspage.MoveUp1();

                        }
                        if (event.key.code == Keyboard::Down)
                        {
                            Optionspage.MoveDown1();

                        }
                        if (event.key.code == Keyboard::Escape)
                        {
                            MainPage(window);
                            break;
                        }
                        if (event.key.code == Keyboard::Return)
                        {
                            switch (Optionspage.GetPressValue1())
                            {
                            case 0:
                                cout << "STM button has been Pressed " << endl;
                                mainGame(window);
                                break;
                            case 1:
                                cout << "O button has been Pressed " << endl;
                                boardgame(window);
                                break;
                            case 2:
                                Bingo(window);
                                break;
                            case 3:
                                MainPage(window);
                                break;

                            }
                        }
                    }
                }
            Optionspage.draw1(window);
            window.display();


        }
    }
}

int GoBack1(RenderWindow& window)
{
    RenderWindow windowe(VideoMode(250, 100), "EXIT", Style::None);
    EB EB(static_cast<float>(windowe.getSize().x), static_cast<float>(windowe.getSize().y));


    while (true) {
        while (windowe.isOpen()) {
            Event event1;
            while (windowe.pollEvent(event1)) {
                if (event1.type == Event::Closed) {
                    windowe.close();
                    GameOptions(window);
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
                           
                            windowe.close();
                            window.close();
                            break;
                        case 1:
                            cout << "NO" << endl;
                            if (flag)
                            {
                                windowe.close();
                                GameOptions(window);
                            }
                            else
                            {
                                windowe.close();
                                MainPage(window);
                            }
                            break;
                        }
                    }
                }
            }
            windowe.clear(Color(64, 64, 64));
            EB.drawe(windowe);
            windowe.display();


        }
    }

    return 0;
}
