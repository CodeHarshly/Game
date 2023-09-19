#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
#include"Game.h"
#include"Mainpage.h"
using namespace std;
using namespace sf;



bool flagf = false;
const double GRAVITY = 9.81f;
const float w_width = 320;
const float w_height = 480;
const float air_resist = 0.5f;
bool jump = false;
const int M = 20;
const int N = 10;

int field[M][N] = { 0 }, topRow = M, d1, d2;

int positioncheck();
int GoBack(RenderWindow& window);


struct Point
{
    int x, y;
} a[10], b[10];

int figures[6][6] =
{
    {0, 1, 2, 3, 4, 5},
    {1, 2, 3, 5, 1, 1},
    {2, 3, 2, 3, 2, 3},
    {0, 1, 2, 3, 0, 1},
    {1, 3, 1, 3, 1, 3},
    {1, 3, 5, 1, 3, 5}

};

bool check()     //for blocks
{
    for (int i = 0; i < 6; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M || field[a[i].y][a[i].x] != 0)
            return 0;
        else if (field[a[i].y][a[i].x])
            return 0;

    return 1;
};

void mainGame(RenderWindow& window)
{
    srand(static_cast<unsigned int>(time(0)));
    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.3f, 0.3f);
    back.setScale(bg);
    //background end
    

    Texture t1, t2,btl,btr,btu;

    t1.loadFromFile("images/man2.png");
    t2.loadFromFile("images/tiles.png");
    btl.loadFromFile("images/leftside.png");
    btr.loadFromFile("images/rightside.png");
    btu.loadFromFile("images/upside.png");

    Sprite s(t1), s2(t2), saves,bsl,bsr,bsu;

    //stickman
    s.setTextureRect(IntRect(0, 0, 500, 600));
    Vector2f scale(0.06f, 0.06f), sposition;
    s.setScale(scale);
    s.setPosition(window.getSize().x / 2 - s.getGlobalBounds().width / 2, window.getSize().y / 2 - s.getGlobalBounds().height / 2);
    s.setPosition(0, 200);
    //resize the photo      for man

    // for blocks
    s2.setTextureRect(IntRect(0, 0, 18, 18));    

    //for button
    bsl.setTexture(btl);
    Vector2f scale1(0.02f, 0.02f);
    bsl.setScale(scale1);
    bsl.setPosition(window.getSize().x / 2 - bsl.getGlobalBounds().width / 2, window.getSize().y / 2 - bsl.getGlobalBounds().height / 2);
    bsl.setPosition(0, 410);

    bsr.setTexture(btr);
    bsr.setScale(scale1);
    bsr.setPosition(window.getSize().x / 2 - bsr.getGlobalBounds().width / 2, window.getSize().y / 2 - bsr.getGlobalBounds().height / 2);
    bsr.setPosition(50, 410);

    bsu.setTexture(btu);
    bsu.setScale(scale1);
    bsu.setPosition(window.getSize().x / 2 - bsu.getGlobalBounds().width / 2, window.getSize().y / 2 - bsu.getGlobalBounds().height / 2);
    bsu.setPosition(24, 380);


    const float MAX_X = N * 18 - s.getGlobalBounds().width;
    const float MIN_X = 0;
    float FLOOR_LEVEL = M * 18 - s.getGlobalBounds().height;
    // Define the gravitational acceleration

    // Define the initial velocity and time variables
    double velocity = 0.0f;
    float jump_v = -40.f;
    float hori_move = 0.0f;

    

    int colorNum = 1, dx = 0;
    double timer = 0, delay = 0.3;

    Clock clock, clock2;
    bool onBlock = false;
    int add = 0, ch = 0, frame = 0, frameCount = 4;
    float deltaTime = clock.restart().asSeconds();

    while (window.isOpen())
    {
        int flag = 0;
        float time2 = clock2.getElapsedTime().asSeconds();
        clock2.restart();
        timer += time2;
        window.clear(Color::White);

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                flagf = false;
                GoBack(window);
            }
                // for man ->

            else if (e.type == Event::KeyPressed)
            {

                if (e.key.code == Keyboard::Left)
                {
                    if (jump) {
                        hori_move = -0.1f;
                    }
                    else {
                        s.move(-8.f, 0);
                        // Move image left
                    }
                    ch = 1;
                }
                else if (e.key.code == Keyboard::Right)
                {
                    if (jump) {
                        hori_move = 0.1f;
                    }
                    else {
                        s.move(8.f, 0);
                        // Move image right
                    }
                    ch = 1;
                }
                else if (e.key.code == Keyboard::Up)
                {
                    jump = true;
                    hori_move = 0.0f;
                    jump_v = -40.f;
                    s.move(0, jump_v);
                    d1 = static_cast<int>(s.getPosition().x);
                    d2 = static_cast<int>(s.getPosition().y);
                    positioncheck();
                    ch = 1;
                   
                    
                }
                if (e.key.code == Keyboard::Escape)
                {
                    flagf = true;
                    GoBack(window);
                }
            }
            else if (e.type == Event::KeyReleased)
            {
                if (e.key.code == Keyboard::Left || e.key.code == Keyboard::Right || e.key.code == Keyboard::Up)
                {
                    hori_move = 0.0f;
                    d1 = static_cast<int>(s.getPosition().x);
                    d2 = static_cast<int>(s.getPosition().y);
                    positioncheck();
                    ch = 0;
                    
                }
            }
            if (e.type == Event::MouseButtonReleased)
            {
                if (e.mouseButton.button == Mouse::Left)
                {
                    // Get the mouse position
                    Vector2i mousePosition = Mouse::getPosition(window);

                    // Check if the mouse position is within the button bounds
                    if (bsl.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        // Button is clicked! Perform action or state transition here
                        // ...
                    }
                }
                if (e.mouseButton.button == Mouse::Left)
                {
                    // Get the mouse position
                    Vector2i mousePosition = Mouse::getPosition(window);

                    // Check if the mouse position is within the button bounds
                    if (bsr.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        // Button is clicked! Perform action or state transition here
                        // ...
                    }
                }
                if (e.mouseButton.button == Mouse::Left)
                {
                    // Get the mouse position
                    Vector2i mousePosition = Mouse::getPosition(window);

                    // Check if the mouse position is within the button bounds
                    if (bsu.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        // Button is clicked! Perform action or state transition here
                        // ...
                    }
                }
            }

            //if (stickRow < M && field[stickRow + 1][stickColumn] != 0) {

            if (jump)
            {

                jump_v += GRAVITY;
                s.move(hori_move, jump_v);


                if (s.getPosition().y >= FLOOR_LEVEL)
                {
                    s.setPosition(s.getPosition().x, FLOOR_LEVEL);
                    jump_v = -40.f;
                    //jump = false;
                }   //*/

            }
            if (s.getPosition().x < MIN_X) {
                // Move the sprite back to the boundary
                s.setPosition(MIN_X, s.getPosition().y);
            }
            else if (s.getPosition().x > MAX_X) {
                s.setPosition(MAX_X, s.getPosition().y);
            }    //<- end */
        }

        if (jump)
        {
            jump = false;
        }
        FLOOR_LEVEL = topRow * 18 - s.getGlobalBounds().height;   //*/
        if (!check())      //for blocks
        {
            for (int i = 0; i < 6; i++)
                a[i] = b[i];
        }
        for (int k = 0;k < N / 2;k++)    //for blocks
            if (field[11][k])
            {
                for (int j = 5;j < N;j++)
                {
                    if (field[11][j] == 0)
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }

                }

            }
        if (timer > delay)        //for blocks
        {
            for (int i = 0; i < 6; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            if (!check())
            {
                for (int i = 0; i < 6; i++)
                    field[b[i].y][b[i].x] = colorNum;
                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                int x = rand() % 6;
                if (flag)
                {
                    if (x >= 0 && x <= 2)
                        x = 5 - x;
                }
                for (int i = 0; i < 6; i++)
                {
                    a[i].x = x + figures[n][i] / 2;
                    a[i].y = figures[n][i] % 2;
                }
            }
            timer = 0;
        }
        for (int j = 0;j < N;j++)     //for blocks
            if (field[9][j])
            {
                int k = M - 1;
                for (int i = M - 2; i > 0; i--)
                {
                    for (int j = 0; j < N; j++)
                    {
                        field[k][j] = field[i][j];
                    }
                    k--;
                }
                break;
            }
        delay = 0.3;
        dx = 0;

        // Update the time and velocity variables
        double deltaTime = clock.getElapsedTime().asSeconds();

        //float resist = jump ? air_resist : 0.0f;

        // Update the position of the sprite based on the current velocity and time
        s.move(hori_move, static_cast<float>(velocity * deltaTime));

        // Update vertical position based on current velocity and gravity
        velocity += GRAVITY * deltaTime * 24;

        // Check if the sprite has reached the floor
        if (s.getPosition().y >= FLOOR_LEVEL) {
            // Reset the position and velocity of the sprite
            s.setPosition(s.getPosition().x, FLOOR_LEVEL);
            velocity = 0.0f;
        }

        // Reset the clock
        clock.restart();

        

        for (int i = 0; i < 6; i++)       //for blocks
        {
            s2.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s2.setPosition(static_cast<float>(a[i].x * 18), static_cast<float>(a[i].y * 18));
            window.draw(s2);
        }

        for (int i = 0; i < M; i++)       //for blocks
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0) continue;
                s2.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                s2.setPosition(static_cast<float>(j * 18), static_cast<float>(i * 18));

                window.draw(s2);
            }
        //FLOOR_LEVEL = s2.getPosition().y + s2.getGlobalBounds().height  - s.getGlobalBounds().height;
        if (ch)
        {
            int frameWidth = t1.getSize().x / frameCount;
            int frameHeight = t1.getSize().y;

            int x = frame * frameWidth;
            int y = 0;

            s.setTextureRect(IntRect(x, y, frameWidth, frameHeight));
        }
        else {
            int frameWidth = t1.getSize().x;
            int frameHeight = t1.getSize().y;
            s.setTextureRect(IntRect(0, 0, 500, 600));
        }
        frame++;
        if (frame >= frameCount)
        {
            frame = 0;
        }
        window.draw(s);
        window.draw(bsl);
        window.draw(bsr);
        window.draw(bsu);
        window.display();
    }
    
}

int positioncheck()
{
    topRow = M;
    int stickColumn = static_cast<int>(d1 / 18);
    int stickRow = static_cast<int>(d2 / 18);
    //if(stickcolumn>stickcolumn2)
    for (int i = stickColumn; i < N; i++) {
        for (int j = stickRow; j < M; j++) {
            if (field[j][i] != 0) {
                topRow = j;
                break;
            }
        }
        if (topRow != M) {
            break;
        }
    }
    return 0;
}

int GoBack(RenderWindow& window)
{
    RenderWindow window2(VideoMode(250, 100), "EXIT", Style::None);
    EB EB(static_cast<float>(window2.getSize().x), static_cast<float>(window2.getSize().y));

    while (true) {
        while (window2.isOpen()) {
            Event event1;
            while (window2.pollEvent(event1)) {
                if (event1.type == Event::Closed) {
                    window2.close();
                    mainGame(window);
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
                            if (flagf)
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




