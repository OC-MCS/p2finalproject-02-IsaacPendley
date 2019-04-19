#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "ABomb.h"
#include "AShip.h"
#include "GameUI.h"
#include "PMissile.h"
#include "PShip.h"

enum GameStatus {START, PLAYING, DEATH, NEXT, GAMEND, PAUSE};

class GameMST {
private:
	PShip playa;
	list<PMissile> plrDrills;
	list<AShip> antiSpirals;
	list<ABomb> lBombs;
	bool enemyMovingR;
	GameStatus state;
public:
	GameMST(RenderWindow &window) {
		playa.setShipPos(window);
		state = START;
	}

	void updater(RenderWindow &window) {
		drawAntiSpirals(window);
		drawMissiles(window);
		drawBombs(window);

		movePlayer(window);
		moveMissile();
		moveEnemy(window);
		alienShoot();
		moveBombs();
		playerDie(window);

		deleteEnemy();
	}

	void resetGame(RenderWindow &window) {
		playa.setShipPos(window);
		plrDrills.clear();
		antiSpirals.clear();
		lBombs.clear();
		createAntispiral(10);
	}

	GameStatus getState() {
		return state;
	}

	void setState(GameStatus s) {
		state = s;
	}

	int getRand(int min, int max)
	{
		if (min == max)
		{
			return max;
		}
		else
		{
			return (rand() % (min - max + 1) + min);
		}
	}

	void movePlayer(RenderWindow &window)
	{
		playa.moveShip(window);
	}

	void shootMissile()
	{
		PMissile temp;
		plrDrills.push_back(temp); // push back a temporary value
		plrDrills.back().setTexture();
		plrDrills.back().setPos(playa.getPosition().x, playa.getPosition().y - 40); // set the position
		
	}

	//player missile functions
	void moveMissile()
	{
		list<PMissile>::iterator iter;

		//moves all the player projectiles
		for (iter = plrDrills.begin(); iter != plrDrills.end(); iter++)
			iter->moveMissile();

		//checks if the player projectiles have hit the top
		for (iter = plrDrills.begin(); iter != plrDrills.end();)
		{
			if (iter->getSprite().getPosition().y < 0)
			{
				iter = plrDrills.erase(iter);
			}
			else
				iter++;
		}

	}

	void drawMissiles(RenderWindow &window)
	{
		list<PMissile>::iterator iter;
		if (!plrDrills.empty())
		{
			for (iter = plrDrills.begin(); iter != plrDrills.end(); iter++)
			{
				window.draw(iter->getSprite());
			}
		}
	}

	//Create the spiral nemisis
	void createAntispiral(int numEnemies)
	{
		//Create a int to keep track of how many aliens were created
		int enemyNum;
		//Initialize rows distance from from edge
		int initialX = 70;
		//Create every enemy in the list
		for (enemyNum = 0; enemyNum < numEnemies; enemyNum++)
		{
			//holds the parameters of the alien that we want to add to the list
			AShip *newShip = new AShip;
			newShip->setTexture();
			newShip->setPos(initialX, 50);
			newShip->iFireRate();
			newShip->setFR();
			newShip->cooldown(true);

			antiSpirals.push_back(*newShip);
			initialX += 70;
		}
	}

	void drawAntiSpirals(RenderWindow &window)
	{
		list<AShip>::iterator iter;
		if (!antiSpirals.empty())
		{
			for (iter = antiSpirals.begin(); iter != antiSpirals.end(); iter++)
			{
				window.draw(iter->getSprite());
			}
		}
	}

	void moveEnemy(RenderWindow &window)
	{
		if (!antiSpirals.empty())
		{
			list<AShip>::iterator iter = antiSpirals.begin();
			Texture txtSize = antiSpirals.begin()->getTXT();
			if (antiSpirals.front().getPosition().x == 0)
			{
				for (iter = antiSpirals.begin(); iter != antiSpirals.end(); iter++)
				{
					iter->aMoveY();
				}
			}
			if (antiSpirals.back().getPosition().x == 740)
			{
				for (iter = antiSpirals.begin(); iter != antiSpirals.end(); iter++)
				{
					iter->aMoveY();
				}
			}
			if (enemyMovingR)
			{
				int limit, lastPos;
				limit = 800 - txtSize.getSize().x;
				lastPos = antiSpirals.back().getPosition().x;
				if (lastPos <= limit)
				{
					for (iter = antiSpirals.begin(); iter != antiSpirals.end(); iter++)
					{
						iter->aMove(enemyMovingR);
					}
				}
				else
				{
					enemyMovingR = false;
				}
			}
			else
			{
				if (antiSpirals.front().getPosition().x >= 0)
				{
					for (iter = antiSpirals.begin(); iter != antiSpirals.end(); iter++)
					{
						iter->aMove(enemyMovingR);
					}
				}
				else
				{
					enemyMovingR = true;
				}
			}
		}
	}

	void deleteEnemy()
	{
		list<AShip>::iterator enemyIter;
		list<PMissile>::iterator missileIter;
		if (!antiSpirals.empty() && !plrDrills.empty())
		{
			for (missileIter = plrDrills.begin(); missileIter != plrDrills.end();)
			{
				bool missileDeleted = false;
				for (enemyIter = antiSpirals.begin(); enemyIter != antiSpirals.end();)
				{
					if (missileIter->getSprite().getGlobalBounds().intersects(enemyIter->getSprite().getGlobalBounds()))
					{
						missileIter = plrDrills.erase(missileIter);
						enemyIter = antiSpirals.erase(enemyIter);
						missileDeleted = true;
						break;
					}
					else
					{
						enemyIter++;
					}
				}
				if (!missileDeleted)
				{
					missileIter++;
				}
			}
		}
	}

	void drawBombs(RenderWindow &window)
	{
		list<ABomb>::iterator iter;
		if (!lBombs.empty())
		{
			for (iter = lBombs.begin(); iter != lBombs.end(); iter++)
			{
				window.draw(iter->getSprite());
			}
		}
	}

	void alienShoot()
	{
		if (!antiSpirals.empty())
		{
			list<AShip>::iterator sIter;
			for (sIter = antiSpirals.begin(); sIter != antiSpirals.end(); sIter++)
			{
				if (sIter->getCF())
				{
					int fireT = getRand(0, 1000);
					if (fireT >= 50 && fireT <= 53 && lBombs.size() < 4)
					{
						ABomb *newBomb = new ABomb;
						newBomb->setSprite();
						int BombX = (sIter->getPosition().x + (sIter->getPosition().x + sIter->getWidth())) / 2;
						BombX -= (newBomb->getWidth() / 2);
						int BombY = (sIter->getPosition().y + (sIter->getPosition().y + sIter->getHieght())) / 2;
						newBomb->setPos(BombX, BombY);
						lBombs.push_back(*newBomb);
						sIter->cooldown(false);
					}
				}
				else
				{
					sIter->frCount();
					if (sIter->getfrCount() == sIter->getFR())
					{
						sIter->cooldown(true);
						sIter->iFireRate();
					}
				}
			}
		}
	}

	void moveBombs()
	{
		list<ABomb>::iterator iter;

		//moves all the player projectiles
		for (iter = lBombs.begin(); iter != lBombs.end(); iter++)
			iter->moveB();

		//checks if the player projectiles have hit the top
		for (iter = lBombs.begin(); iter != lBombs.end();)
		{
			if (iter->getSprite().getPosition().y > 600)
			{
				iter = lBombs.erase(iter);
			}
			else
				iter++;
		}
	}

	void playerDie(RenderWindow &window)
	{
		list<ABomb>::iterator bombIter;
		if (!lBombs.empty())
		{
			for (bombIter = lBombs.begin(); bombIter != lBombs.end();)
			{
				bool bombDeleted = false;
				if (bombIter->getSprite().getGlobalBounds().intersects(playa.getSprite().getGlobalBounds()))
				{
 					bombIter = lBombs.erase(bombIter);
					setState(START);
					resetGame(window);
					bombDeleted = true;
					break;
				}
				if (!bombDeleted)
				{
					bombIter++;
				}
			}
		}
	}
};