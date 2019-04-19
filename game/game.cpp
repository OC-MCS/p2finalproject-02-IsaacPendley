//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little gray and red ship). 
//========================================================
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 
#include "ABomb.h"
#include "AShip.h"
#include "GameMST.h"
#include "GameUI.h"
#include "PMissile.h"
#include "PShip.h"

//============================================================
// Isaac N Pendley
// Program 8 "Space Invaders"
// Programming 2
// 4/19/2019
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen



int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PIERCE THE HEAVENS WITH YOUR DRILL!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	GameMST GM(window);
	GM.createAntispiral(10);
	GameUI GUI;
	GUI.setStartTexture();

	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);


	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					// handle space bar
					GM.shootMissile();
				}
				
			}
			else if (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				// check to see if mouse is in the drawing area
				if (GUI.mouseInStart(mousePos))
				{
					// add a shape to the list based on current settings
					GM.setState(PLAYING);
				}
				else if (GUI.mouseInRestart(mousePos))
				{
					// add a shape to the list based on current settings
					GM.setState(PLAYING);
				}
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

		if (GM.getState() == START)
		{
			GUI.drawStart(window);
		}
		if (GM.getState() == PLAYING)
		{
			GM.updater(window);
		}
		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

