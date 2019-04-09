#include "TEAL\CommonElements.h"
#include "CentipedeHead.h"
#include "CentipedeHeadFactory.h"
#include "MushroomField.h"

CentipedeHeadFactory* CentipedeHeadFactory::ptrInstance = NULL;


CentipedeHead* CentipedeHeadFactory::privCreateCentipedeHead(sf::Vector2f p, MushroomField* pM, float s, float c, int b)
{
	CentipedeHead* ch;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New CentipedeHead");

		ch = new CentipedeHead();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		ch->SetExternalManagement(RecycleCentipedeHead);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled CentipedeHead");

		ch = recycledItems.top();
		recycledItems.pop();

		// Tell the object to register itself to the scene
		ch->RegisterToCurrentScene();
	}

	ch->Initialize(p, pM, s, c, b);
	return ch;
}

void CentipedeHeadFactory::privRecycleCentipedeHead(GameObject* x)
{
	recycledItems.push(static_cast<CentipedeHead*>(x));

	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

void CentipedeHeadFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

CentipedeHeadFactory::~CentipedeHeadFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled items (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}