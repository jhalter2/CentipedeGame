#include "Explosion.h"
#include "ExplosionFactory.h"

ExplosionFactory* ExplosionFactory::ptrInstance = NULL;

void ExplosionFactory::privCreateExplosion(sf::Vector2f p) {
	Explosion* e;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Explosion");

		e = new Explosion();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		e->SetExternalManagement(RecycleExplosion);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Explosion");

		e = recycledItems.top();
		recycledItems.pop();

		// Tell the object to register itself to the scene
		e->RegisterToCurrentScene();
	}

	e->Initialize(p);
}

void ExplosionFactory::privRecycleExplosion(GameObject* g) {
	recycledItems.push(static_cast<Explosion*>(g));

	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

ExplosionFactory::~ExplosionFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled items (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

void ExplosionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

