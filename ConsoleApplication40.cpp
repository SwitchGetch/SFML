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

int main()
{
    srand(time(NULL));

    vector<sf::Color> colors
    {
        sf::Color::Red,
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color::Magenta
    };

    int winX, winY, r;

    cout << "window size: ";
    cin >> winX >> winY;

    cout << "ball radius: ";
    cin >> r;

    int maxX = winX - (2 * r);
    int maxY = winY - (2 * r);


    int x = rand() % (maxX + 1), y = rand() % (maxY + 1);
    string direction = "lu";

    int temp = rand() % 4;

    switch (temp)
    {
    case 0: direction = "rd"; break;
    case 1: direction = "ld"; break;
    case 2: direction = "lu"; break;
    case 3: direction = "ru"; break;
    }

    int amc = 0;
    int color_id = 0;

    cout << "angle match count: " << amc << endl;


    sf::RenderWindow window(sf::VideoMode(winX, winY), "My window");


    sf::CircleShape ball(r);
    ball.setFillColor(colors[color_id]);
    ball.setPosition(x, y);



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

        if (direction == "rd")
        {
            if (x < maxX && y < maxY)
            {
                //window.clear(sf::Color::Black);

                window.draw(ball);

                window.display();

                //this_thread::sleep_for(milliseconds(1));

                x++;
                y++;

                ball.setPosition(x, y);
            }
            else
            {
                if (x == maxX && y == maxY)
                {
                    direction = "lu";

                    amc++;

                    system("cls");

                    cout << "window size: " << winX << " " << winY << endl;
                    cout << "ball radius: " << r << endl;
                    cout << "angle match count: " << amc << endl;
                }
                else if (x == maxX) direction = "ld";
                else if (y == maxY) direction = "ru";

                color_id++;
                color_id %= 6;
                ball.setFillColor(colors[color_id]);
            }
        }
        else if (direction == "ld")
        {
            if (x > 0 && y < maxY)
            {
                //window.clear(sf::Color::Black);

                window.draw(ball);

                window.display();

                //this_thread::sleep_for(milliseconds(1));

                x--;
                y++;

                ball.setPosition(x, y);
            }
            else
            {
                if (x == 0 && y == maxY)
                {
                    direction = "ru";

                    amc++;

                    system("cls");

                    cout << "window size: " << winX << " " << winY << endl;
                    cout << "ball radius: " << r << endl;
                    cout << "angle match count: " << amc << endl;
                }
                else if (x == 0) direction = "rd";
                else if (y == maxY) direction = "lu";

                color_id++;
                color_id %= 6;
                ball.setFillColor(colors[color_id]);
            }
        }
        else if (direction == "lu")
        {
            if (x > 0 && y > 0)
            {
                //window.clear(sf::Color::Black);

                window.draw(ball);

                window.display();

                //this_thread::sleep_for(milliseconds(1));

                x--;
                y--;

                ball.setPosition(x, y);
            }
            else
            {
                if (x == 0 && y == 0)
                {
                    direction = "rd";

                    amc++;

                    system("cls");

                    cout << "window size: " << winX << " " << winY << endl;
                    cout << "ball radius: " << r << endl;
                    cout << "angle match count: " << amc << endl;
                }
                else if (x == 0) direction = "ru";
                else if (y == 0) direction = "ld";

                color_id++;
                color_id %= 6;
                ball.setFillColor(colors[color_id]);
            }
        }
        else if (direction == "ru")
        {
            if (x < maxX && y > 0)
            {
                //window.clear(sf::Color::Black);

                window.draw(ball);

                window.display();

                //this_thread::sleep_for(milliseconds(1));

                x++;
                y--;

                ball.setPosition(x, y);
            }
            else
            {
                if (x == maxX && y == 0)
                {
                    direction = "ld";

                    amc++;

                    system("cls");

                    cout << "window size: " << winX << " " << winY << endl;
                    cout << "ball radius: " << r << endl;
                    cout << "angle match count: " << amc << endl;
                }
                else if (x == maxX) direction = "lu";
                else if (y == 0) direction = "rd";

                color_id++;
                color_id %= 6;
                ball.setFillColor(colors[color_id]);
            }
        }
    }
}