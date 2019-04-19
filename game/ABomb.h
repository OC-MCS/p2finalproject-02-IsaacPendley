#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class ABomb {
private:
	Sprite bomb;
	Texture bText;
public:
	ABomb() {
		
	}

	void setSprite() {
		if (!bText.loadFromFile("bomb.png"))
		{
			cout << "Unable to load bomb texture!" << endl;
			exit(EXIT_FAILURE);
		}
		bomb.setTexture(bText);
	}

	Vector2f getPosition() {
		return bomb.getPosition();
	}

	void setPos(int Xpos, int Ypos)
	{
		bomb.setPosition(Xpos, Ypos);
	}

	int getWidth() {
		return bText.getSize().x;
	}

	int getHieght() {
		return bText.getSize().y;
	}

	Sprite getSprite() {
		return bomb;
	}

	void moveB()
	{
		bomb.move(0, 5);
	}
};