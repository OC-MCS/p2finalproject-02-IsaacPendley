#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class PShip {
private:
	Sprite player;
	Texture pText;
public:
	PShip() {
		if (!pText.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
		player.setTexture(pText);
	}

	void setShipPos(RenderWindow &window) {
		player.setPosition(window.getSize().x / 2.0f, 500);
	}

	Vector2f getPosition() {
		return player.getPosition();
	}

	Sprite getSprite() {
		return player;
	}

	void moveShip(RenderWindow &window)
	{
		const float DISTANCE = 5.0;

		if (Keyboard::isKeyPressed(Keyboard::Left) && player.getPosition().x > 0)
		{
			// left arrow is pressed: move our ship left 5 pixels
			// 2nd parm is y direction. We don't want to move up/down, so it's zero.
			player.move(-DISTANCE, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && (player.getPosition().x < (window.getSize().x - pText.getSize().x)))
		{
			// right arrow is pressed: move our ship right 5 pixels
			player.move(DISTANCE, 0);
		}
		window.draw(player);
	}
};