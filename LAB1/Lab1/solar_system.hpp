#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>


#include "planet.hpp"



#define PLANETS_COUNT 8
#define WINDOW_SIZE_X 1300
#define WINDOW_SIZE_Y 1000


class SolarSystem
{
public:
	//SolarSystem() {};

	void go();


private:
	void initPlanet();
	void printPlanet(Planet *planet, sf::Color color);
	void event();


	std::condition_variable cv;
	std::mutex mt;

	sf::RenderWindow* window;
	std::vector<Planet*> planets;
	std::vector<std::thread*> th_planets;
	std::vector<sf::Color> colors = { sf::Color::Green, sf::Color::Red, sf::Color::White, sf::Color::Magenta, sf::Color::Blue, sf::Color::Cyan, sf::Color::White, sf::Color::Red, sf::Color::Green };
};