#include <Windows.h>
#include <iostream>
#include <vector>

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}

protected:
	virtual void update(float deltaTime) {}
};

class Player : public GameObject
{
public:
	Player() {}
	~Player();

private:
	void update(float deltaTime) {}
};

class Enemy : public GameObject
{
public:
	Enemy() {}
	~Enemy();

private:
	int energy;
	void update(float deltaTime)
	{
		if (energy == 0)
		{

		}
	}
};

class Projectile : public GameObject
{
public:
	Projectile() {}
	~Projectile();

private:
	void update(float deltaTime) {}
};

class PickableItem : public GameObject
{
public:
	PickableItem() {}
	~PickableItem();
};


int main()
{
	std::vector<GameObject*> objects;
	float deltaTime = 1000;

	do
	{
		if (GetAsyncKeyState(0x31))		// Add player
		{
			std::cout << "Hello1";
			objects.push_back(new Player);
		}
		if (GetAsyncKeyState(0x32))		// Add enemy
		{
			std::cout << "Hello2";
			objects.push_back(new Enemy);
		}
		if (GetAsyncKeyState(0x33))		// Add projectile
		{
			std::cout << "Hello3";
			objects.push_back(new Projectile);
		}
		if (GetAsyncKeyState(0x34))		// Add item
		{
			std::cout << "Hello4";
			objects.push_back(new PickableItem);
		}
		if (GetAsyncKeyState(0x41))		// First projectile hits the first Enemy
		{
			std::cout << "HelloA";
		}
		if (GetAsyncKeyState(0x42))		// First player hits the first PickableItem
		{
			std::cout << "HelloB";
		}

		Sleep(deltaTime);
	} while (true);

	return 0;
}