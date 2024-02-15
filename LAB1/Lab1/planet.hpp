#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numbers>
#include <random>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>




class Planet
{
public:
	Planet()
	{
		this->center_x = 0;
		this->center_y = 0;
		this->angle = 0;
		this->size = 5;
		this->radius = 0;
		this->speed = 0;
		color = sf::Color::White;
	};

	void go()
	{
		while (true)
		{
			move(clock.restart());
		}
	}

	void setPosition()
	{
		if (circle == nullptr)
		{
			std::cout << "Не проинициализирован параметр 'circle'. Сначала вызовите метод 'initPlanet'!" << std::endl;
		}

		float x = center_x + 0 * cos(angle * std::numbers::pi_v<float> / 180.0f);
		float y = center_y + 0 * sin(angle * std::numbers::pi_v<float> / 180.0f);
		circle->setPosition(x, y);
	}

	void setCenterCoord(float new_x, float new_y)
	{
		this->center_x = new_x;
		this->center_y = new_y;
	}

	void setSpeed(float speed_)
	{
		this->speed = speed_;
	}

	void setColor(sf::Color color_)
	{
		this->color = color_;
	}

	void setRandomStartAngle()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0.0f, 360.0f);

		this->angle = dis(gen);
	}

	void setRadius(float radius_)
	{
		this->radius = radius_;
	}

	void setSize(float size_)
	{
		this->size = size_;
	}

	void initPlanet()
	{
		circle = new sf::CircleShape(this->size);
		circle->setFillColor(color);
	}


	sf::CircleShape* getCircle()
	{
		return this->circle;
	}

	void getCenterCoord(float& x, float& y)
	{
		x = this->center_x;
		y = this->center_y;
		return;
	}

	int getSize()
	{
		return this->size;
	}

	friend std::ostream& operator<<(std::ostream & os, const Planet & planet)
	{

	}

private:

	void move(sf::Time deltaTime)
	{
		float sec = deltaTime.asSeconds();
		std::cout << sec << std::endl;
		angle += speed * sec;

		float x = center_x + radius * cos(angle * std::numbers::pi_v<float> / 180.0f);
		float y = center_y + radius * sin(angle * std::numbers::pi_v<float> / 180.0f);
		
		
		circle->setPosition(x, y);
	}


	sf::CircleShape* circle;
	sf::Color color;
	sf::Clock clock;

	float center_x, center_y;
	float radius,
		speed,
		size,
		angle;
	float offset;
};