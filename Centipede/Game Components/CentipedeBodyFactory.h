#ifndef _CentipedeBodyFactory
#define _CentipedeBodyFactory

#include <stack>
#include "CentipedeBody.h"
#include "MushroomField.h"
#include "CentipedeHead.h"

class CentipedeBodyFactory
{
private:
	// Game set up as a singleton
	static CentipedeBodyFactory* ptrInstance;

	CentipedeBodyFactory() = default;												// Private constructor
	CentipedeBodyFactory(const CentipedeBodyFactory&) = delete;				// Prevent copy-construction
	CentipedeBodyFactory& operator=(const CentipedeBodyFactory&) = delete;	// Prevent assignment
	~CentipedeBodyFactory();														// Only this class can delete

	static CentipedeBodyFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeBodyFactory;
		return *ptrInstance;
	};

	std::stack<CentipedeBody*> recycledItems;  // Back to be a non-static member

											   // Note: Some factory designs also keep a list of 'currently active' objects
											   // Often useful at cleanup time. Not done for this demo however

											   //create centipede head with position, mushroomfield, speed, column, and body length
	CentipedeBody* privCreateCentipedeBody(CentipedeHead* pHead, CentipedeBody* pNext, CentipedeBody* pPrev);
	void privRecycleCentipedeBody(GameObject* x);

public:

	// Services/API as STATIC METHODS
	static CentipedeBody* CreateCentipedeBody(CentipedeHead* pHead, CentipedeBody* pNext, CentipedeBody* pPrev) { return Instance().privCreateCentipedeBody(pHead, pNext, pPrev); };
	static void RecycleCentipedeBody(GameObject* x) { Instance().privRecycleCentipedeBody(x); };

	static void Terminate();
};


#endif _CentipedeHeadFactory

