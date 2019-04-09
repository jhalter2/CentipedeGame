#include "TEAL\CommonElements.h"
#include "Scorpion.h"
#include "ScorpionFactory.h"
#include "MushroomField.h"

ScorpionFactory* ScorpionFactory::ptrInstance = NULL;


Scorpion* ScorpionFactory::privCreateScorpion(sf::Vector2f p, MushroomField* pM, float speed, float direction)
{
	Scorpion* s;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Scorpion");

		s = new Scorpion();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		s->SetExternalManagement(RecycleScorpion);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Scorpion");

		s = recycledItems.top();
		recycledItems.pop();

		// Tell the object to register itself to the scene
		s->RegisterToCurrentScene();
	}
	s->Initialize(pM, p, speed, direction);
	return s;
}

void ScorpionFactory::privRecycleScorpion(GameObject* b)
{
	recycledItems.push(static_cast<Scorpion*>(b));

	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

void ScorpionFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

ScorpionFactory::~ScorpionFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled items (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}
