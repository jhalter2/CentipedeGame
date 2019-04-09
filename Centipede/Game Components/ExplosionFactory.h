#ifndef _ExplosionFactory
#define _ExplosionFactory

#include <stack>
#include "Explosion.h"

class ExplosionFactory {
private:
	// Game set up as a singleton
	static ExplosionFactory* ptrInstance;

	ExplosionFactory() = default;									// Private constructor
	ExplosionFactory(const ExplosionFactory&) = delete;				// Prevent copy-construction
	ExplosionFactory& operator=(const ExplosionFactory&) = delete;	// Prevent assignment
	~ExplosionFactory();											// Only this class can delete

	static ExplosionFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ExplosionFactory;
		return *ptrInstance;
	};

	std::stack<Explosion*> recycledItems;

	void privCreateExplosion(sf::Vector2f p);
	void privRecycleExplosion(GameObject* g);
public:
	static void CreateExplosion(sf::Vector2f p) { Instance().privCreateExplosion(p); };
	static void RecycleExplosion(GameObject* g) { Instance().privRecycleExplosion(g); };
	static void Terminate();
};

#endif _ExplosionFactory

