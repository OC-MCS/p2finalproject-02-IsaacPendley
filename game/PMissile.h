#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class PMissile {
private:
	Sprite missile;
	Texture mText;
public:
	PMissile() {
		
	}

	void setTexture() {
		if (!mText.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
		missile.setTexture(mText);
	}

	void setPos(int Xpos, int Ypos)
	{
		missile.setPosition(Xpos, Ypos);
	}

	Vector2f getPosition() {
		return missile.getPosition();
	}

	Sprite getSprite() {
		return missile;
	}

	void moveMissile() {
		missile.move(0, -5);
	}
};