#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;

HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cord;


void statsOutput(int x, int y, int winX, int winY, int maxX, int maxY, string dirX, string dirY, int r, int red, int green, int blue, int range, int bounce_count)
{
    cord.X = 0;
    cord.Y = 0;

    SetConsoleCursorPosition(hand, cord);

    cout << "window size:" << endl;
    cout << "x: " << winX << endl;
    cout << "y: " << winY << endl;

    cout << endl;

    cout << "current position:" << endl;
    cout << "x: " << x; for (int i = 0; i < to_string(maxX).size() - to_string(x).size(); i++) { cout << ' '; } cout << endl;
    cout << "y: " << y; for (int i = 0; i < to_string(maxY).size() - to_string(y).size(); i++) { cout << ' '; } cout << endl;

    cout << endl;

    cout << "min x: 0" << endl;
    cout << "max x: " << maxX << endl;
    cout << "min y: 0" << endl;
    cout << "max y: " << maxY << endl;

    cout << endl;

    cout << "currend direction:" << endl;

    cout << "x: " << dirX; for (int i = 0; i < 5 - dirX.size(); i++) { cout << ' '; } cout << endl;
    cout << "y: " << dirY; for (int i = 0; i < 4 - dirY.size(); i++) { cout << ' '; } cout << endl;

    cout << endl;

    cout << "ball radius: " << r << endl;
    cout << "ball diameter: " << 2 * r << endl;

    cout << endl;

    cout << "current color:" << endl;
    cout << "R: " << red; for (int i = 0; i < 3 - to_string(red).size(); i++) { cout << ' '; } cout << endl;
    cout << "G: " << green; for (int i = 0; i < 3 - to_string(green).size(); i++) { cout << ' '; } cout << endl;
    cout << "B: " << blue; for (int i = 0; i < 3 - to_string(blue).size(); i++) { cout << ' '; } cout << endl;

    cout << endl;

    cout << "range (pixels per frame): " << range << endl;

    cout << endl;

    cout << "bounce count: " << bounce_count << endl;
}


void setRandomDirection(string& dirX, string& dirY)
{
    int x = rand() % 2;
    int y = rand() % 2;

    dirX = (x ? "right" : "left");
    dirY = (y ? "down" : "up");
}


void setMaxCords(int& maxX, int& maxY, int winX, int winY, int r)
{
    maxX = winX - (2 * r);
    maxY = winY - (2 * r);
}


void setRandomCords(int& x, int& y, int maxX, int maxY)
{
    x = rand() % (maxX + 1);
    y = rand() % (maxY + 1);
}


void setRandomColor(sf::CircleShape& ball, int& red, int& green, int& blue)
{
    red = rand() % 256;
    green = rand() % 256;
    blue = rand() % 256;

    ball.setFillColor(sf::Color( red, green, blue ));
}


//void setNextColor(sf::CircleShape& ball, vector<sf::Color> colors, int& color_id)
//{
//    color_id++;
//    color_id %= colors.size();
//
//    ball.setFillColor(colors[color_id]);
//}
//
//int setRandomColor(sf::CircleShape& ball, vector<sf::Color> colors)
//{
//    int color_id = rand() % colors.size();
//
//    ball.setFillColor(colors[color_id]);
//
//    return color_id;
//}


void changeDirX(string& dirX)
{
    dirX = (dirX == "right" ? "left" : "right");
}


void changeDirY(string& dirY)
{
    dirY = (dirY == "down" ? "up" : "down");
}


void outputShape(sf::RenderWindow& window, sf::CircleShape& ball)
{
    window.clear(sf::Color::Black);

    window.draw(ball);

    window.display();
}


void moveShape(sf::CircleShape& ball, int& x, int& y, int maxX, int maxY, string dirX, string dirY, int range)
{
    for (int i = 0; i < range; i++)
    {
        int nextX = x + (dirX == "right" ? 1 : -1);
        int nextY = y + (dirY == "down" ? 1 : -1);

        if ((0 <= nextX && nextX <= maxX) && (0 <= nextY && nextY <= maxY))
        {
            x = nextX;
            y = nextY;
        }
        else break;
    }

    ball.setPosition(x, y);
}


int main()
{
    srand(time(NULL));

    /*vector<sf::Color> colors =
    {
        sf::Color::Red,
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color::Magenta,
    };*/

    int winX, winY, r;
    int maxX, maxY;
    int x, y;
    /*
    int color_id;
    */
    string dirX, dirY;
    int red, green, blue;
    int bounce_count = 0, range = 1;


    cout << "window size: ";
    cin >> winX >> winY;

    winX = abs(winX);
    winY = abs(winY);

    cout << "ball radius: ";
    cin >> r;

    r = abs(r);

    if (2 * r > min(winX, winY)) r = min(winX, winY) / 2;


    setMaxCords(maxX, maxY, winX, winY, r);

    setRandomCords(x, y, maxX, maxY);

    setRandomDirection(dirX, dirY);


    sf::RenderWindow window(sf::VideoMode(winX, winY), "My window");


    sf::CircleShape ball(r);

    /*
    color_id = setRandomColor(ball, colors);
    */

    setRandomColor(ball, red, green, blue);

    ball.setPosition(x, y);


    system("cls");


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        statsOutput(x, y, winX, winY, maxX, maxY, dirX, dirY, r, red, green, blue, range, bounce_count);

        outputShape(window, ball);

        moveShape(ball, x, y, maxX, maxY, dirX, dirY, range);

        if (x == 0 || y == 0 || x == maxX || y == maxY)
        {
            if (x <= 0 || x >= maxX) changeDirX(dirX);

            if (y <= 0 || y >= maxY) changeDirY(dirY);


            bounce_count++;
            range += log10(1 + (bounce_count - 1) % 10);


            setRandomColor(ball, red, green, blue);
        }

        this_thread::sleep_for(milliseconds(1));
    }
}
