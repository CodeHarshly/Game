#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
#include"Game.h"
#include"GameLogic.h"
#include"Mainpage.h"
#include <cstdlib>
#include <ctime> 
#include <random>

using namespace std;
using namespace sf;

const int total = 25;
vector<int> botclicked;
vector<int> botChosenIndices;
Vector2f imagePositions[total], imagePositions2[total];
vector<Vector2f> clickedPositions, clickedPositions2;
vector<Sprite> clicked, clicked2;

int arr[5][5] = { 0 }, psol[5][5] = { 0 }, bot1[5][5] = { 0 }, bsol[5][5] = { 0 },bv;
float p1[5] = { 50,96,142,188,234 }, p3[5] = { 40,86,132,178,224 };

int GoBack3(RenderWindow& window);
int element1();
int element();
int checkwinner(int ch);
int gameover(int win1, RenderWindow& window);
int BingoResult(int w, RenderWindow& window);
int botvalue();

bool checkBot(int botv) {
    bool isDuplicate = false;
    for (const auto& cl : botclicked) {
        if (cl == botv) {
            isDuplicate = true;
            break;
        }
    }
    bool isBotChosen = false;
    for (const auto& chosenIndex : botChosenIndices) {
        if (chosenIndex == botv) {
            isBotChosen = true;
            break;
        }
    }
    if (!isDuplicate && !isBotChosen) {
        botChosenIndices.push_back(botv);
        return true;
    }
    return false;
}
int justchecking() {
    for (int i = 0;i < 5; i++) {
        for (int j = 0;j < 5;j++) {
            cout << bsol[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0;i < 5; i++) {
        for (int j = 0;j < 5;j++) {
            cout << bot1[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


int Bingo(RenderWindow& window)
{
    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.35f, 0.35f);
    back.setScale(bg);
    //background end
    element();
    element1();

    int check = 0, win = 0;
    bool ch = false;
    Texture n[total],p2,bi;
    bi.loadFromFile("images/Bingo.png");
    p2.loadFromFile("Images/number/Cut.png");
    Font f;
    f.loadFromFile("arial.ttf");
    
    Text text[2];
    for (int i = 0;i < 2;i++) {

        text[i].setFont(f);
        text[i].setFillColor(Color::Magenta);
        if (i == 0) {
            text[i].setString("You");
        }
        else {
            text[i].setString("Bot");
        }
        text[i].setCharacterSize(30);
        text[i].setPosition(static_cast < float>(50 * (1 + (i*3))), 350);
    }

    Vector2f s3(0.065f, 0.065f), scale(0.5f, 0.5f),s4(0.35f,0.35f), s5(0.1f, 0.1f);
    

    Sprite s[total], k,c,b(bi),bot;
    c.setTexture(p2);
    c.setScale(s3);
    b.setScale(s4);
    b.setColor(Color::Green);
    b.setPosition(90, -5);
    
    for (int t = 0;t < total;t++) {
        if (!n[t].loadFromFile("images/number/" + to_string(t+1) + ".png")) {
            cout << "couldn't load image " << t+1 << endl;
            return 1;
        }
        s[t].setTexture(n[t]);
        s[t].setScale(scale);
    }
    
    RectangleShape box[2];
    for (int i = 0;i < 2;i++) {
        box[i].setFillColor(Color::Black);
        box[i].setOutlineColor(Color(0, 0, 0, 128));
        box[i].setOutlineThickness(2.0f);
    }
    
    bool turn = false, cuta=false;
    while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
            if (e.type == Event::Closed)
            {
                GoBack3(window);
            }
            else if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                {
                    GoBack3(window);
                }
            }
        }

        window.clear();
        window.draw(back);
        if (!ch && e.type == Event::MouseButtonPressed) {

            //detect mouse clicked position 

            if (e.mouseButton.button == Mouse::Left) {
                Vector2i mousePosition = Mouse::getPosition(window);
                for (int t = 0;t < total;t++) {
                    FloatRect b = s[t].getGlobalBounds();

                    if (b.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        bool alreadyClicked = false;
                        for (const auto& clickedS : clicked) {
                            if (clickedS.getPosition() == s[t].getPosition()) {
                                alreadyClicked = true;
                                break;
                            }
                        }
                        bool validBotIndex = true;
                        for (const auto& chosenIndex : botChosenIndices) {
                            if (chosenIndex == t + 1) {
                                validBotIndex = false;
                                break;
                            }
                        }
                        if (!alreadyClicked && validBotIndex) {
                            cout << t + 1 << " clicked!" << endl;
                            cout << "Image " << t + 1 << " clicked at position: (" << imagePositions[t].x << ", " << imagePositions[t].y << ")" << endl;
                            clickedPositions.push_back(imagePositions[t]); // Store clicked position
                            botclicked.push_back(t + 1);
                            clicked.push_back(s[t]);
                            turn = true;
                            cuta = true;
                            for (int i = 0;i < 5; i++) {
                                for (int j = 0;j < 5;j++) {
                                    if (arr[i][j] == t + 1) {
                                        psol[i][j] = 1;
                                    }
                                    if (bot1[i][j] == t + 1) {
                                        bsol[i][j] = 1;
                                    }
                                }
                            }
                            cout << endl << "potsol" << endl;
                            for (int i = 0;i < 5; i++) {
                                for (int j = 0;j < 5;j++) {
                                    cout << psol[i][j] << " ";
                                }
                                cout << endl;
                            }
                            for (int i = 0;i < 5; i++) {
                                for (int j = 0;j < 5;j++) {
                                    cout << arr[i][j] << " ";
                                }
                                cout << endl;
                            }
                        }
                    }
                    int winner = checkwinner(check);
                    if (winner == 1) {
                        win = 1;
                        ch = true;
                    }
                    if (winner == 2) {
                        win = 2;
                        ch = true;
                    }

                }
            }
        }

        if (turn) {
            if (botclicked.size() <= 12) {
                botvalue();

            }
            turn = false;
        }
        if (bv != 0) {

            bot = s[bv - 1];
            if (!ch && e.type == Event::MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    FloatRect b = s[bv - 1].getGlobalBounds();
                    if (b.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {

                        bool alreadyClicked2 = false;
                        for (const auto& clickedS : clicked2) {
                            if (clickedS.getPosition() == s[bv - 1].getPosition()) {
                                alreadyClicked2 = true;
                                break;
                            }
                        }
                        if (!alreadyClicked2) {
                            cout << "\nbot Image " << bv << " clicked at position: (" << imagePositions2[bv - 1].x << ", " << imagePositions2[bv - 1].y << ")" << endl;
                            clickedPositions2.push_back(imagePositions2[bv - 1]);
                            clicked2.push_back(s[bv - 1]);
                            for (int i = 0;i < 5; i++) {
                                for (int j = 0;j < 5;j++) {
                                    if (arr[i][j] == bv) {
                                        psol[i][j] = 1;
                                    }
                                }
                            }
                            cout << endl << "bpotsol" << endl;
                            for (int i = 0;i < 5; i++) {
                                for (int j = 0;j < 5;j++) {
                                    cout << psol[i][j] << " ";
                                }
                                cout << endl;
                            }
                            for (int i = 0;i < 5; i++) {
                                for (int j = 0;j < 5;j++) {
                                    cout <<  arr[i][j] << " ";
                                }
                                cout << endl;
                            }
                        }
                    }
                }
            }
        }
            //backgroung color 
        box[0].setSize(Vector2f(230, 230));
        box[0].setPosition(40, 50);
        window.draw(box[0]);

            //images bingo
        for (int i = 0; i < 5; i++) {
            for (int j = 0;j < 5; j++)
            {
                for (int t = 0;t < total;t++) {
                    if (arr[i][j] == t + 1) {
                        s[t].setPosition(p3[j], p1[i]);
                        imagePositions[t] = Vector2f(p3[j], p1[i]); // Store the position
                        imagePositions2[t] = Vector2f(p3[j], p1[i]); // Store the position
                        window.draw(s[t]);
                    }
                }
            }
        }
            //cutting image with diagonal line
        for (const auto& pos : clickedPositions) {
            c.setPosition(pos.x + 5, pos.y + 5);
            window.draw(c);

        }
        for (const auto& pos : clickedPositions2) {
            c.setPosition(pos.x + 5, pos.y + 5);
            window.draw(c);

        }
            //end
            //to display the number which are being cut or clicked
        for (int k = 0;k < 2;k++) {
            box[1].setSize(Vector2f(46, 46));
            box[1].setPosition(static_cast <float>(55 * (1 + (k * 2.65))), 390);
            window.draw(box[1]);
        }

        for (const auto& clickedS : clicked) {
            k = clickedS;
            k.setPosition(55, 390);
            k.setColor(Color::Cyan);
            window.draw(k);
        }

        for (int i = 0;i < 2;i++) {
            window.draw(text[i]);
        }
        if (bv != 0) {
            bot = s[bv - 1];
            bot.setPosition(200.76f, 390);
            window.draw(bot);
        }
        if (ch) {
            gameover(win, window);
            break;
        }
        // end here
        window.draw(b);
        window.display();
	}
    return 0;
}

int element1() {

    int i = 0, f3 = 0;
    bool foundDuplicate = false;

    while (true) {
        random_device rd;
        uniform_int_distribution<int> dist(1, 25);
        i = dist(rd);
        f3 = 0;
        foundDuplicate = false;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (bot1[j][k] == i) {
                    foundDuplicate = true;

                    break;
                }
            }

        }
        if (!foundDuplicate) {
            for (int j = 0; j < 5 && f3 == 0; j++) {
                for (int k = 0; k < 5; k++) {
                    if (bot1[j][k] == 0) {
                        bot1[j][k] = i;
                        f3 = 1;
                        break;
                    }
                }

                if (f3 == 1) break;
            }
        }

        // Check if all indices are filled 
        bool allFilled = true;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (bot1[j][k] == 0) {
                    allFilled = false;
                    break;
                }
            }
        }

        // Exit the while loop if all indices are filled
        if (allFilled) {
            break;
        }
    }
    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++) {
            cout << bot1[j][k] << " ";
        }
        cout << endl;
    }

    return 0;
}


int element() {

    int i = 0, f3 = 0;
    bool foundDuplicate = false;

    while (true) {
        random_device rd;
        uniform_int_distribution<int> dist(1, 25);
        i = dist(rd);
        f3 = 0;
        foundDuplicate = false;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (arr[j][k] == i) {
                    foundDuplicate = true;

                    break;
                }
            }

        }
        if (!foundDuplicate) {
            for (int j = 0; j < 5 && f3 == 0; j++) {
                for (int k = 0; k < 5; k++) {
                    if (arr[j][k] == 0) {
                        arr[j][k] = i;
                        f3 = 1;
                        break;
                    }
                }

                if (f3 == 1) break;
            }
        }

        // Check if all indices are filled 
        bool allFilled = true;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (arr[j][k] == 0) {
                    allFilled = false;
                    break;
                }
            }
        }

        // Exit the while loop if all indices are filled
        if (allFilled) {
            break;
        }
    }
    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++) {
            cout << arr[j][k] << " ";
        }
        cout << endl;
    }

    return 0;
}
int botvalue() {
    bool Update_r = false, Update = false, work = true;

    bv = 0; // Reset bv to 0 initially
    // part 1
    for (int i = 0; i < 5; ++i) {
        // Check if the bot can complete a row
        int rowSum = 0;
        for (int j = 0; j < 5; ++j) {
            rowSum += bsol[i][j];
        }
        if (rowSum == 4) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[i][j] == 0) {
                    bv = bot1[i][j];
                    if (checkBot(bv)) {
                        bsol[i][j] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }

        // Check if the bot can complete a column
        int colSum = 0;
        for (int j = 0; j < 5; ++j) {
            colSum += bsol[j][i];
        }
        if (colSum == 4) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[j][i] == 0) {
                    bv = bot1[j][i];
                    if (checkBot(bv)) {
                        bsol[j][i] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }
    }

    // Check if the bot can complete the main diagonal
    int mainDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        mainDiagonalSum += bsol[i][i];
    }
    if (mainDiagonalSum == 4) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][i] == 0) {
                bv = bot1[i][i];
                if (checkBot(bv)) {
                    bsol[i][i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }

    // Check if the bot can complete the secondary diagonal
    int secondaryDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        secondaryDiagonalSum += bsol[i][4 - i];
    }
    if (secondaryDiagonalSum == 4) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][4 - i] == 0) {
                bv = bot1[i][4 - i];
                if (checkBot(bv)) {
                    bsol[i][4 - i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }
    // part 2
    for (int i = 0; i < 5; ++i) {
        // Check if the bot can complete a row
        int rowSum = 0;
        for (int j = 0; j < 5; ++j) {
            rowSum += bsol[i][j];
        }
        if (rowSum == 3) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[i][j] == 0) {
                    bv = bot1[i][j];
                    if (checkBot(bv)) {
                        bsol[i][j] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }

        // Check if the bot can complete a column
        int colSum = 0;
        for (int j = 0; j < 5; ++j) {
            colSum += bsol[j][i];
        }
        if (colSum == 3) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[j][i] == 0) {
                    bv = bot1[j][i];
                    if (checkBot(bv)) {
                        bsol[j][i] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }
    }

    // Check if the bot can complete the main diagonal
    mainDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        mainDiagonalSum += bsol[i][i];
    }
    if (mainDiagonalSum == 3) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][i] == 0) {
                bv = bot1[i][i];
                if (checkBot(bv)) {
                    bsol[i][i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }

    // Check if the bot can complete the secondary diagonal
    secondaryDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        secondaryDiagonalSum += bsol[i][4 - i];
    }
    if (secondaryDiagonalSum == 3) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][4 - i] == 0) {
                bv = bot1[i][4 - i];
                if (checkBot(bv)) {
                    bsol[i][4 - i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }

    //part 3
    for (int i = 0; i < 5; ++i) {
        // Check if the bot can complete a row
        int rowSum = 0;
        for (int j = 0; j < 5; ++j) {
            rowSum += bsol[i][j];
        }
        if (rowSum == 2) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[i][j] == 0) {
                    bv = bot1[i][j];
                    if (checkBot(bv)) {
                        bsol[i][j] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }

        // Check if the bot can complete a column
        int colSum = 0;
        for (int j = 0; j < 5; ++j) {
            colSum += bsol[j][i];
        }
        if (colSum == 2) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[j][i] == 0) {
                    bv = bot1[j][i];
                    if (checkBot(bv)) {
                        bsol[j][i] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }
    }

    // Check if the bot can complete the main diagonal
    mainDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        mainDiagonalSum += bsol[i][i];
    }
    if (mainDiagonalSum == 2) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][i] == 0) {
                bv = bot1[i][i];
                if (checkBot(bv)) {
                    bsol[i][i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }

    // Check if the bot can complete the secondary diagonal
    secondaryDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        secondaryDiagonalSum += bsol[i][4 - i];
    }
    if (secondaryDiagonalSum == 2) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][4 - i] == 0) {
                bv = bot1[i][4 - i];
                if (checkBot(bv)) {
                    bsol[i][4 - i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }

    // part 4
    for (int i = 0; i < 5; ++i) {
        // Check if the bot can complete a row
        int rowSum = 0;
        for (int j = 0; j < 5; ++j) {
            rowSum += bsol[i][j];
        }
        if (rowSum == 1) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[i][j] == 0) {
                    bv = bot1[i][j];
                    if (checkBot(bv)) {
                        bsol[i][j] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }

        // Check if the bot can complete a column
        int colSum = 0;
        for (int j = 0; j < 5; ++j) {
            colSum += bsol[j][i];
        }
        if (colSum == 1) {
            for (int j = 0; j < 5; ++j) {
                if (bsol[j][i] == 0) {
                    bv = bot1[j][i];
                    if (checkBot(bv)) {
                        bsol[j][i] = 1;
                        justchecking();
                        return bv;
                    }
                }
            }
        }
    }

    // Check if the bot can complete the main diagonal
    mainDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        mainDiagonalSum += bsol[i][i];
    }
    if (mainDiagonalSum == 1) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][i] == 0) {
                bv = bot1[i][i];
                if (checkBot(bv)) {
                    bsol[i][i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }

    // Check if the bot can complete the secondary diagonal
    secondaryDiagonalSum = 0;
    for (int i = 0; i < 5; ++i) {
        secondaryDiagonalSum += bsol[i][4 - i];
    }
    if (secondaryDiagonalSum == 1) {
        for (int i = 0; i < 5; ++i) {
            if (bsol[i][4 - i] == 0) {
                bv = bot1[i][4 - i];
                if (checkBot(bv)) {
                    bsol[i][4 - i] = 1;
                    justchecking();
                    return bv;
                }
            }
        }
    }


    // If no strategic moves are available, make a random choice
    while (work) {
        random_device rd;
        uniform_int_distribution<int> dist(1, 25);
        bv = dist(rd);
        if (checkBot(bv)) {
            Update = true; // to add random number
            work = false;
            break;
        }
    }//*/
    if (Update) {
        // Update bsol matrix
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (bot1[i][j] == bv) {
                    bsol[i][j] = 1;
                }
            }
        }
        justchecking();
    }


    return bv;

}


int checkwinner(int ch)
{
    for (int j = 0;j < 5;j++) {
        if (bsol[0][j] == 1 && bsol[1][j] == 1 && bsol[2][j] == 1 && bsol[3][j] == 1 && bsol[4][j] == 1) {
            cout << "\n bot win from line: 0"<< j << endl;
            return 2;
            break;
        }
        if (bsol[j][0] == 1 && bsol[j][1] == 1 && bsol[j][2] == 1 && bsol[j][3] == 1 && bsol[j][4] == 1) {
            cout << "\n bot win from line: 0" << j << endl;
            return 2;
            break;
        }
        if (psol[0][j] == 1 && psol[1][j] == 1 && psol[2][j] == 1 && psol[3][j] == 1 && psol[4][j] == 1) {
            cout << "\n you win from line: 0" << j << endl;
            return 1;
            break;
        }
        if (psol[j][0] == 1 && psol[j][1] == 1 && psol[j][2] == 1 && psol[j][3] == 1&& psol[j][4] == 1) {
            cout << "\n you win from line: 0" << j << endl;
            return 1;
            break;
        }
    }
    if (bsol[0][0] == 1 && bsol[1][1] == 1 && bsol[2][2] == 1 && bsol[3][3] == 1 && bsol[4][4] == 1) {
        cout << "\n bot win from diagonal line: 00" << endl;
        return 2;
    }
    if (bsol[0][4] == 1 && bsol[1][3] == 1 && bsol[2][2] == 1 && bsol[3][1] == 1 && bsol[4][0] == 1) {
        cout << "\n bot win from diagonal line: 04" << endl;
        return 2;
    }
    if (psol[0][0] == 1 && psol[1][1] == 1 && psol[2][2] == 1 && psol[3][3] == 1 && psol[4][4] == 1) {
        cout << "\n you win from diagonal line: 00" << endl;
        return 1;
    }
    if (psol[0][4] == 1 && psol[1][3] == 1 && psol[2][2] == 1 && psol[3][1] == 1 && psol[4][0] == 1) {
        cout << "\n you win from diagonal line: 04" << endl;
        return 1;
    }

    
    return 0;
}

int gameover(int win1, RenderWindow& window)
{
    //RenderWindow windowg(VideoMode(320, 240), "Game Over", Style::None);
    GameOver GameOver(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    //window.setPosition(Vector2i(window.getPosition().x,window.getPosition().y+120));
    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.35f, 0.35f);
    back.setScale(bg);
    //background end
    if (win1 != 0) {
        Texture bii;
        bii.loadFromFile("images/Bingo.png");
        Sprite bi(bii);
        bi.setScale(bg);
        bi.setColor(Color::Green);
        bi.setPosition(90, -5);
        Font f;
        f.loadFromFile("arial.ttf");
        Text text1;
        text1.setFont(f);
        text1.setFillColor(Color::Red);
        
        if (win1 == 1) {
            text1.setString("You win");
        }
        else if (win1 == 2) {
            text1.setString("You lose");
        }
        text1.setCharacterSize(30);
        text1.setPosition(110, 65);

        while (true) {
            while (window.isOpen()) {
                Event event1;
                while (window.pollEvent(event1)) {
                    if (event1.type == Event::KeyPressed)
                    {
                        if (event1.key.code == Keyboard::Up)
                        {
                            GameOver.MoveUpgo();

                        }
                        if (event1.key.code == Keyboard::Down)
                        {
                            GameOver.MoveDowngo();

                        }
                        if (event1.key.code == Keyboard::Return)
                        {
                            switch (GameOver.GetPressValuego())
                            {
                            case 0:
                                cout << "Play again" << endl;
                                window.clear();
                                // Reset arrays to all zeros
                                for (int i = 0; i < 5; i++) {
                                    for (int j = 0; j < 5; j++) {
                                        arr[i][j] = 0;
                                        psol[i][j] = 0;
                                        bot1[i][j] = 0;
                                        bsol[i][j] = 0;
                                    }
                                }
                                bv = 0;
                                botclicked.clear();
                                botChosenIndices.clear();
                                clickedPositions.clear();
                                clickedPositions2.clear();
                                clicked.clear();
                                clicked2.clear();
                                for (int i = 0; i < total; i++) {
                                    imagePositions[i] = Vector2f(0, 0);
                                    imagePositions2[i] = Vector2f(0, 0);
                                }
                                // call function to play again
                                Bingo(window);
                                break;
                            case 1:
                                cout << "Result" << endl;
                                BingoResult(win1,window);
                                break;

                            case 2:
                                cout << "exit" << endl;
                                window.clear();
                                // Reset arrays to all zeros
                                for (int i = 0; i < 5; i++) {
                                    for (int j = 0; j < 5; j++) {
                                        arr[i][j] = 0;
                                        psol[i][j] = 0;
                                        bot1[i][j] = 0;
                                        bsol[i][j] = 0;
                                    }
                                }
                                bv = 0;
                                botclicked.clear();
                                botChosenIndices.clear();
                                clickedPositions.clear();
                                clickedPositions2.clear();
                                clicked.clear();
                                clicked2.clear();
                                for (int i = 0; i < total; i++) {
                                    imagePositions[i] = Vector2f(0, 0);
                                    imagePositions2[i] = Vector2f(0, 0);
                                }
                                // calling the function to go to menu
                                GameOptions(window);
                                break;
                            }
                        }
                    }
                }
                window.draw(back);
                window.draw(bi);
                window.draw(text1);
                GameOver.drawgo(window);
                window.display();


            }
        }
    }
    
    return 0;
}
int BingoResult(int w, RenderWindow& window)
{
    //background start
    Texture backg;
    backg.loadFromFile("images/Background.png");
    Sprite back(backg);
    back.setPosition(0, 0);
    Vector2f bg(0.35f, 0.35f);
    back.setScale(bg);
    //background end
    Font f;
    f.loadFromFile("arial.ttf");
    Text text1;
    text1.setFont(f);
    text1.setFillColor(Color::Cyan);
    text1.setString("Go Back");
    text1.setCharacterSize(30);
    text1.setPosition(160 - text1.getGlobalBounds().width / 2, 440);
    Texture n[total];
    Sprite s[total];
    Vector2f scale(0.5f, 0.5f);
    for (int t = 0;t < total;t++) {
        if (!n[t].loadFromFile("images/number/" + to_string(t + 1) + ".png")) {
            cout << "couldn't load image " << t + 1 << endl;
            return 1;
        }
        s[t].setTexture(n[t]);
        s[t].setScale(scale);
    }

    while (window.isOpen()) {
        Event event1;
        while (window.pollEvent(event1)) {
            if (event1.type == Event::KeyPressed)
            {
                if (event1.key.code == Keyboard::Return || event1.key.code == Keyboard::Escape)
                {
                    gameover(w,window);
                }
            }
        }
        window.clear();
        window.draw(back);
        window.draw(text1);
        window.display();
    }
    return 0;
}
int GoBack3(RenderWindow& window)
{
    RenderWindow window2(VideoMode(250, 100), "EXIT", Style::None);
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
                            window2.close();
                            // Reset arrays to all zeros
                            for (int i = 0; i < 5; i++) {
                                for (int j = 0; j < 5; j++) {
                                    arr[i][j] = 0;
                                    psol[i][j] = 0;
                                    bot1[i][j] = 0;
                                    bsol[i][j] = 0;
                                }
                            }
                            bv = 0;
                            botclicked.clear();
                            botChosenIndices.clear();
                            clickedPositions.clear();
                            clickedPositions2.clear();
                            clicked.clear();
                            clicked2.clear();
                            for (int i = 0; i < total; i++) {
                                imagePositions[i] = Vector2f(0, 0);
                                imagePositions2[i] = Vector2f(0, 0);
                            }
                            // calling the function to go to menu
                            GameOptions(window);
                            break;
                        case 1:
                            cout << "NO" << endl;
                            window2.close();
                            Bingo(window);
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

