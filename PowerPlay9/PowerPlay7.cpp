#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

std::vector<Object*> createMonsters(Player* player);

void displayBattle(const std::vector<Object*>& monsters);
void bringOutYourDead(std::vector<Object*>& monsters);


int main()
{
	Player player;
	std::vector<Object*> objects;
	while (!player.isDead())
	{
		player.levelUp();
		objects = createMonsters(&player);

		std::cout << objects.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (!player.isDead() && objects.size() > 0)
		{

			displayBattle(objects);

			//player.update(objects);

			bringOutYourDead(objects);

			std::cout << std::endl;
			std::for_each(objects.begin() + 1, objects.end(), [&](Object* monster)
				{
					//monster.update(objects);
				});

			system("PAUSE");
			system("CLS");
		}
	}

	if (player.isDead())
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.isDead() && objects.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (objects.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}



void displayBattle(const std::vector<Object*>& objects)
{
	Object::nameOnly = false; //TODO:: get rid of this and just dot he full cout.
	std::cout <<*objects[0] << std::endl;
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(objects.begin() + 1, objects.end(), [&](const Object* monster)
			{
				std::cout << "   " << i << ". " << *monster << std::endl;

				i++;
			});
	}
}

std::vector<Object*> createMonsters(Player* player)
{
	std::normal_distribution<double> randomNumMonsters((double)player->getLevel(), player->getLevel() / 2.0);
	std::vector<Object*> objects(1 + std::max(1, (int)randomNumMonsters(Object::engine)));
	objects[0] = player;
	std::generate(objects.begin() + 1, objects.end(), [&]()
		{
			return static_cast<Object*>( new Monster(*player));
		});
	return objects;
}

void bringOutYourDead(std::vector<Object*>& objects)
{
	Object::nameOnly = true;
	objects.erase(
		std::remove_if(objects.begin() + 1, objects.end(),
			[](Object* monster)
			{
				if (monster->isDead())
				{

					std::cout << monster << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		objects.end());

}
