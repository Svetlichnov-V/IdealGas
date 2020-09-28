#include "SFML/Graphics.hpp"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <math.h>
#include "sphere.h"

int main()
{
    const int X_MAX = 1960;
    const int Y_MAX = 1080;

    const float DT = 0.1;

    sf::Uint8 redFill = 10;
    sf::Uint8 greenFill = 10;
    sf::Uint8 blueFill = 0;
    sf::Color fillColor = sf::Color(redFill, greenFill, blueFill);
    sf::Color lineColor = sf::Color(redFill, greenFill, blueFill);

    int numberOfCicles = 25;
    int numberOfCiclesInDrawTrack = 10;

    int radius = 25;
    float SPHERE_MASS = 1;

    sf::Color colorSphere = sf::Color(0, 0, 255);
    sf::Color colorTrackSphere = fillColor;

    const int numberOfParticles = 200;
    Sphere particles[numberOfParticles];

    srand(500);

    for (int i = 0; i < numberOfParticles; ++i)
    {
        Vector2f position{ rand() % X_MAX, rand() % Y_MAX };
        Vector2f velocity{ rand() % 200, rand() % 200 };
        Sphere particle{ position,     position,     velocity,     Vector2f {0, 0}, radius, SPHERE_MASS, colorSphere, colorTrackSphere };
        particles[i] = particle;
    }

    float controllability = 20;

    float coefficientSlowdown = 0.0;

    sf::RenderWindow window(sf::VideoMode(X_MAX, Y_MAX), "Main window");
    window.clear(fillColor);
    window.display();

    while (window.isOpen())
    {
        for (int i = 0; i < numberOfParticles; ++i)
        {
            collisionSphere(&particles[i], X_MAX, Y_MAX);
        }
        for (int i = 0; i < numberOfParticles; ++i)
        {
            for (int j = i + 1; j < numberOfParticles; ++j)
            {
                if (isCollidedTwoSpheres(&particles[i], &particles[j]))
                    resolutionSphereOnCollision(&particles[i], &particles[j]);
            }
        }
        for (int i = 0; i < numberOfParticles; ++i)
        {
            moveSphere(&particles[i], DT);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(fillColor);
        for (int i = 0; i < numberOfParticles; ++i)
        {
            drawSphere(&window, &particles[i], numberOfCicles);
        }
        window.display();
    }
    return 0;
}