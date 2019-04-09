#ifndef _FleaFactory
#define _FleaFactory

#include <stack>
#include "Flea.h"
#include "MushroomField.h"

class FleaFactory
{
private:
	// Game set up as a singleton
	static FleaFactory* ptrInstance;			

	FleaFactory() = default;												// Private constructor
	FleaFactory(const FleaFactory&) = delete;				// Prevent copy-construction
	FleaFactory& operator=(const FleaFactory&) = delete;	// Prevent assignment
	~FleaFactory();														// Only this class can delete

	static FleaFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new FleaFactory;
		return *ptrInstance;
	};

	std::stack<Flea*> recycledItems;  // Back to be a non-static member

										// Note: Some factory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not done for this demo however

										// Private NON_STATIC methods to perform actual work on member var
	Flea* privCreateFlea(sf::Vector2f p, MushroomField* pM);
	void privRecycleFlea(GameObject* b);

public:

	// Services/API as STATIC METHODS
	static Flea* CreateFlea(sf::Vector2f p, MushroomField* pM) { return Instance().privCreateFlea(p, pM); };
	static void RecycleFlea(GameObject* b) { Instance().privRecycleFlea(b); };

	static void Terminate();
};


#endif _FleaFactory

