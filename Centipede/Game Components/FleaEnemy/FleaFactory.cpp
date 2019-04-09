#include "TEAL\CommonElements.h"
#include "Flea.h"
#include "FleaFactory.h"
#include "MushroomField.h"

FleaFactory* FleaFactory::ptrInstance = NULL;


Flea* FleaFactory::privCreateFlea(sf::Vector2f p, MushroomField* pM)
{
	Flea* f;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Flea");

		f = new Flea(pM);

		// Declares that this object should be returned here (rather than deleted) when destroyed
		f->SetExternalManagement(RecycleFlea);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Flea");

		f = recycledItems.top();
		recycledItems.pop();

								// Tell the object to register itself to the scene
		f->RegisterToCurrentScene();
	}

	
	f->Initialize(p, pM);
	return f;
}

void FleaFactory::privRecycleFlea(GameObject* b)
{
	recycledItems.push(static_cast<Flea*>(b));

	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

void FleaFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

FleaFactory::~FleaFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled items (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}
