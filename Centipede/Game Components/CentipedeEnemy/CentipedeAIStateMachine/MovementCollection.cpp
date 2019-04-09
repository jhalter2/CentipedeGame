#include "MovementCollection.h"

//put the movement values in that we'll need for each state of the centipedehead FSM

const OffsetArray MovementCollection::OffsetsStraightRight = OffsetArray(sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f),
	sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f),
	sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f), sf::Vector2f(1.0f, 0.0f),
	sf::Vector2f(1.0f, 0.0f), 0, 1);

const OffsetArray MovementCollection::OffsetsTurnUpEndRight = OffsetArray(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), -1, 0);

const OffsetArray MovementCollection::OffsetsTurnDownEndRight = OffsetArray(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(0.0f, 1.0f), 1, 0);

const OffsetArray MovementCollection::OffsetsStraightLeft = OffsetArray(sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f),
	sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f),
	sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f),
	sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(-1.0f, 0.0f), 0, -1);

const OffsetArray MovementCollection::OffsetsTurnUpEndLeft = OffsetArray(sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f),
	sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), sf::Vector2f(0.0f, -1.0f), -1, 0);

const OffsetArray MovementCollection::OffsetsTurnDownEndLeft = OffsetArray(sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f),
	sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(0.0f, 1.0f), 1, 0);
