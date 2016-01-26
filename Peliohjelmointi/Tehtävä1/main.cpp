#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}

public:
	virtual void update(float deltaTime) {}
};

class Player : public GameObject
{
public:
	Player() {}
	~Player();

private:
	void update(float deltaTime) { std::cout << "Player is alive!" << std::endl; }
};

class Enemy : public GameObject
{
public:

	Enemy() 
	{
		this->energy = 5;
	}

	~Enemy()
	{
		std::cout << "Enemy has been killed!" << std::endl;
	}

	void takeDamage()
	{
		energy--;
	}

	int getHP()
	{
		return energy;
	}

private:
	int energy;
	void update(float deltaTime)
	{
		std::cout << "Enemy is alive!" << std::endl;
	}
};

class Projectile : public GameObject
{
public:
	Projectile() {}
	~Projectile()
	{
		std::cout << "Projectile was killed." << std::endl;
	}

private:
	void update(float deltaTime) { std::cout << "Projectile is alive!" << std::endl; }
};

class PickableItem : public GameObject
{
public:
	PickableItem() {}

	~PickableItem()
	{
		std::cout << "Player picked up an item." << std::endl;
	}

private:
	void update(float deltaTime) { std::cout << "Item is alive!" << std::endl; }
};


int main()
{
	std::vector<GameObject*> objects;
	float deltaTime = 1000;

	do
	{
		if (GetAsyncKeyState(0x31))		// Add player
		{
			std::cout << "(1) Player has been spawned." << std::endl;
			objects.push_back(new Player);
		}
		if (GetAsyncKeyState(0x32))		// Add enemy
		{
			std::cout << "(2) Enemy has been spawned." << std::endl;
			objects.push_back(new Enemy);
		}
		if (GetAsyncKeyState(0x33))		// Add projectile
		{
			std::cout << "(3) Projectile has been spawned." << std::endl;
			objects.push_back(new Projectile);
		}
		if (GetAsyncKeyState(0x34))		// Add item
		{
			std::cout << "(4) Item has been spawned." << std::endl;
			objects.push_back(new PickableItem);
		}
		if (GetAsyncKeyState(0x41))		// First projectile hits the first Enemy
		{
			Projectile* projectile = nullptr;
			Enemy* enemy = nullptr;

			std::find_if(objects.begin(), objects.end(), [&projectile](GameObject* g)
			{
				projectile = dynamic_cast<Projectile*>(g);
				return projectile != nullptr;
			});

			std::find_if(objects.begin(), objects.end(), [&enemy](GameObject* g)
			{
				enemy = dynamic_cast<Enemy*>(g);
				return enemy != nullptr;
			});

			if (projectile && enemy)
			{
				std::vector<GameObject*>::iterator it = std::find(objects.begin(), objects.end(), projectile);
				delete projectile;
				objects.erase(it);

				enemy->takeDamage();
				std::cout << "Projectile hits enemy!" << std::endl;

				if (enemy->getHP() <= 0)
				{
					it = std::find(objects.begin(), objects.end(), enemy);
					delete enemy;
					objects.erase(it);
				}

			}
			else
			{
				std::cout << "Could not hit!" << std::endl;
			}
		}
		if (GetAsyncKeyState(0x42))		// First player hits the first PickableItem
		{
			std::cout << "HelloB";
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->update(deltaTime);
		}

		Sleep(deltaTime);
		system("cls");

	} while (true);

	return 0;
}