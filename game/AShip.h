#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class AShip {
private:
	Sprite alien;
	Texture aText;
	int fireRate, frCounter;
	bool canFire;
public:
	AShip() {
		
	}

	void setTexture() {
		if (!aText.loadFromFile("Mugann.png"))
		{
			cout << "Unable to load mugann texture!" << endl;
			exit(EXIT_FAILURE);
		}
		alien.setTexture(aText);
	}

	void setPos(int Xpos, int Ypos)
	{
		alien.setPosition(Xpos, Ypos);
	}

	int getWidth() {
		return aText.getSize().x;
	}

	int getHieght() {
		return aText.getSize().y;
	}

	Vector2f getPosition() {
		return alien.getPosition();
	}

	void aMoveY()
	{
		alien.move(0, 10);
	}

	void aMove(bool isMovingRight)
	{
		if (isMovingRight)
		{
			alien.move(5, 0);
		}
		else
		{
			alien.move(-5, 0);
		}
	}

	Texture getTXT()
	{
		return aText;
	}

	void iFireRate()
	{
		frCounter = 0;
	}

	void frCount()
	{
		frCounter++;
	}

	void setFR()
	{
		fireRate = 30;
	}

	int getfrCount()
	{
		return frCounter;
	}

	int getFR()
	{
		return fireRate;
	}

	void cooldown(bool missile)
	{
		canFire = missile;
	}

	bool getCF() {
		return canFire;
	}

	Sprite getSprite() {
		return alien;
	}
};