#ifndef _CentipedeHeadFactory
#define _CentipedeHeadFactory

#include <stack>
class CentipedeHead;
class MushroomField;

class CentipedeHeadFactory
{
private:
	// Game set up as a singleton
	static CentipedeHeadFactory* ptrInstance;

	CentipedeHeadFactory() = default;												// Private constructor
	CentipedeHeadFactory(const CentipedeHeadFactory&) = delete;				// Prevent copy-construction
	CentipedeHeadFactory& operator=(const CentipedeHeadFactory&) = delete;	// Prevent assignment
	~CentipedeHeadFactory();														// Only this class can delete

	static CentipedeHeadFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeHeadFactory;
		return *ptrInstance;
	};

	std::stack<CentipedeHead*> recycledItems;  // Back to be a non-static member

	//create centipede head with position, mushroomfield, speed, column, and body length
	CentipedeHead* privCreateCentipedeHead(sf::Vector2f p, MushroomField* pM, float s, float c, int b);
	void privRecycleCentipedeHead(GameObject* x);

public:

	// Services/API as STATIC METHODS
	static CentipedeHead* CreateCentipedeHead(sf::Vector2f p, MushroomField* pM, float s, float c, int b) { return Instance().privCreateCentipedeHead(p, pM, s, c, b); };
	static void RecycleCentipedeHead(GameObject* x) { Instance().privRecycleCentipedeHead(x); };

	static void Terminate();
};


#endif _CentipedeHeadFactory
