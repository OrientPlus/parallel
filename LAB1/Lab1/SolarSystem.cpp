#include "solar_system.hpp"



void SolarSystem::go()
{
    initPlanet();

    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Solar system");
    
    while (window->isOpen())
    {
        window->clear(sf::Color::Black);

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        for (auto pl : planets)
            window->draw(*pl->getCircle());
        
        window->display();
    }

    for (auto th : th_planets)
    {
        th->detach();
    }

    for (auto planet : planets)
        delete planet;
}

void SolarSystem::initPlanet()
{
    Planet *solar = new Planet;
    float default_speed = 100.0f;
    float center_pos = WINDOW_SIZE_Y / 2;

    solar->setColor(sf::Color::Yellow);
    solar->setSize(25);
    solar->initPlanet();
    solar->setCenterCoord(480, 480);
    solar->setPosition();
    planets.push_back(solar);


    Planet* planet;
    // Меркурий
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(50);
    planet->setSize(5);
    planet->setColor(sf::Color(128,128,128));
    planet->setSpeed(default_speed / (88.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));

    // Венера
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(100);
    planet->setSize(7);
    planet->setColor(sf::Color(200, 50, 50));
    planet->setSpeed(default_speed / (225.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));

    // Земля
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(150);
    planet->setSize(9);
    planet->setColor(sf::Color(0, 100, 200));
    planet->setSpeed(default_speed);
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));

    // Марс
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(170);
    planet->setSize(5);
    planet->setColor(sf::Color(150, 50, 0));
    planet->setSpeed(default_speed / (687.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));

    // Юпитер
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(300);
    planet->setSize(35);
    planet->setColor(sf::Color(240, 220, 180));
    planet->setSpeed(default_speed / (4333.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));

    // Сатурн
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(360);
    planet->setSize(25);
    planet->setColor(sf::Color(245, 230, 150));
    planet->setSpeed(default_speed / (10759.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));

    // Уран
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(410);
    planet->setSize(17);
    planet->setColor(sf::Color(90, 170, 200));
    planet->setSpeed(default_speed / (30689.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));


    // Нептун
    planet = new Planet();
    planet->setCenterCoord(center_pos, center_pos);
    planet->setRadius(450);
    planet->setSize(17);
    planet->setColor(sf::Color(60, 100, 220));
    planet->setSpeed(default_speed / (60182.0f / 360));
    planet->setRandomStartAngle();
    planet->initPlanet();
    planets.push_back(planet);
    th_planets.push_back(new std::thread(&Planet::go, *planet));
}

void SolarSystem::event()
{
    
}