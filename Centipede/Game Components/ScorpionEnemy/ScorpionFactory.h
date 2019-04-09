#ifndef _ScorpionFactory
#define _ScorpionFactory

#include <stack>
class Scorpion;
class MushroomField;

class ScorpionFactory
{
private:
	// Game set up as a singleton
	static ScorpionFactory* ptrInstance;

	ScorpionFactory() = default;					// Private constructor
	ScorpionFactory(const ScorpionFactory&) = delete;		// Prevent copy-construction
	ScorpionFactory& operator=(const ScorpionFactory&) = delete;	// Prevent assignment
	~ScorpionFactory();						// Only this class can delete

	static ScorpionFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new ScorpionFactory;
		return *ptrInstance;
	};

	std::stack<Scorpion*> recycledItems;  // Back to be a non-static member

	// Private NON_STATIC methods to perform actual work on member var
	Scorpion* privCreateScorpion(sf::Vector2f p, MushroomField* pM, float speed, float direction);
	void privRecycleScorpion(GameObject* b);

public:

	// Services/API as STATIC METHODS
	static Scorpion* CreateScorpion(sf::Vector2f p, MushroomField* pM, float speed, float direction) { return Instance().privCreateScorpion(p, pM, speed, direction); };
	static void RecycleScorpion(GameObject* b) { Instance().privRecycleScorpion(b); };

	static void Terminate();
};


#endif _ScorpionFactory
