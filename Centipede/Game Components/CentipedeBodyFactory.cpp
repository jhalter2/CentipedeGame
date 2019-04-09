#include "TEAL\CommonElements.h"
#include "CentipedeHead.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBody.h"
#include "CentipedeBodyFactory.h"
#include "MushroomField.h"

CentipedeBodyFactory* CentipedeBodyFactory::ptrInstance = NULL;


CentipedeBody* CentipedeBodyFactory::privCreateCentipedeBody(CentipedeHead* pHead, CentipedeBody* pNext, CentipedeBody* pPrev)
{
	CentipedeBody* cb;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New CentipedeBody");

		cb = new CentipedeBody(pHead, pNext, pPrev);

		// Declares that this object should be returned here (rather than deleted) when destroyed
		cb->SetExternalManagement(RecycleCentipedeBody);
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled CentipedeBody");

		cb = recycledItems.top();
		recycledItems.pop();

		// Tell the object to register itself to the scene
		cb->RegisterToCurrentScene();
	}

	cb->Initialize(pHead, pNext, pPrev);
	return cb;
}

void CentipedeBodyFactory::privRecycleCentipedeBody(GameObject* x)
{
	recycledItems.push(static_cast<CentipedeBody*>(x));

	//ConsoleMsg::WriteLine("Recycled Stack Size: " + Tools::ToString(recycledItems.size()));
}

void CentipedeBodyFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

CentipedeBodyFactory::~CentipedeBodyFactory()
{
	//ConsoleMsg::WriteLine("Deleting Recycled items (" + Tools::ToString(recycledItems.size()) + ")");

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}