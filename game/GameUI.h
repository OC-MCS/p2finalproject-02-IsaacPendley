#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class GameUI {
private:
	Texture sText;
	Sprite start;
	Texture reText;
	Sprite restart;
public:
	GameUI() {

	}

	void setStartTexture() {
		if (!sText.loadFromFile("start.png"))
		{
			cout << "Unable to load mugann texture!" << endl;
			exit(EXIT_FAILURE);
		}
		start.setTexture(sText);
		setStartPosition();
	}

	void setRestartTexture() {
		if (!reText.loadFromFile("restart.png"))
		{
			cout << "Unable to load mugann texture!" << endl;
			exit(EXIT_FAILURE);
		}
		restart.setTexture(reText);
	}

	bool mouseInStart(Vector2f mousePos) {
		return start.getGlobalBounds().contains(mousePos);
	}

	bool mouseInRestart(Vector2f mousePos) {
		return restart.getGlobalBounds().contains(mousePos);
	}

	void drawStart(RenderWindow &window) {
		window.draw(start);
	}

	void drawRestart(RenderWindow &window) {
		window.draw(restart);
	}

	void setStartPosition() {
		start.setPosition(400, 300);
	}

	void setRestartPosition() {
		restart.setPosition(400, 300);
	}
};