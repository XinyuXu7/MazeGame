#pragma once
#include "../graphics/Window.h"
#include "../core/Board.h"
#include "../entities/Player.h"
#include "../core/InputHandler.h"
#include "../systems/Systems.h" 
#include "../entities/FirePool.h"
#include "../entities/LogPool.h"
#include "../entities/PotionPool.h"


class GameInputHandler;
class System;

class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	bool isPaused() const { return paused; }

	//  IV.A (2/2) Write a function that returns the shared pointer of the player of the game.
	std::shared_ptr<Player> getPlayer() const { return player; }

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row);


private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	// II.A Declare a unique pointer of type Board 
	std::unique_ptr<Board> board;

	// III.D Declare a vector from the standard template library that 
	//       contains shared pointers to Entity classes. Recommended name: entities.
	std::vector<std::shared_ptr<Entity>> entities;

	// III.E Declare a variable of type EntityID (which is declared in Entity.h). This variable will
	//       be incremented by one every time an entity is added to the game.
	EntityID idCounter;

	
	// IV.A (1/2) Declare a pointer to a player object. The pointer must be shared pointer from the standard library.
	std::shared_ptr<Player> player;

	// V.A Declare a unique pointer to an Input Handler object for this class.
	std::unique_ptr<GameInputHandler> inputHandler;

	std::vector<std::shared_ptr<System>> systems; // Add a vector for systems

	void bigArray(float elapsed); // Declare the bigArray function

	std::shared_ptr<FirePool> firePool;
	std::shared_ptr<PotionPool> potionPool;
	std::shared_ptr<LogPool> logPool;

};

