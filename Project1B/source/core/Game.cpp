#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include <iostream>
#include "../../include/audio/ServiceLocator.h"
#include "../../include/audio/SFMLAudioService.h"
#include "../../include/observer/AchievementSystem.h"

// III.F Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game() : paused(false), idCounter(0), player(std::make_shared<Player>())
{
	// V.B: Create the unique pointer to the Input Handler object.
	inputHandler = std::make_unique<GameInputHandler>();
	std::shared_ptr<System> ttlSystem = std::make_shared<TTLSystem>();
	systems.push_back(ttlSystem);

	potionPool = std::make_shared<PotionPool>(10);
	logPool = std::make_shared<LogPool>(10);

}

Game::~Game()
{
	delete ServiceLocator::getAudio();
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();

	if constexpr (std::is_same_v<T, Fire>)
	{
		
	}
	else if constexpr (std::is_same_v<T, Potion>)
	{
		auto potion = potionPool->getPotion();
		if (potion)
		{
			ent = potion;
		}
	}
	else if constexpr (std::is_same_v<T, Log>)
	{
		auto log = logPool->getLog();
		if (log)
		{
			ent = log;
		}
	}

	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->setPosition(x + cntrFactor, y + cntrFactor);
	ent->init(filename, itemScale);

	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	// II.B Instantiate the unique pointer of type "Board". 
	//     Use the constructor of Board that receives the width and the height for the game grid.
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	SFMLAudioService* myAudioService = new SFMLAudioService();
	ServiceLocator::provide(myAudioService);

	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				// II.C (1/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				//      The parameters are the column (for x) and row (for y) where the tile is to be placed, the scale 
				//      of the tile (you can use the variable "tileScale") and the tile type. TileTypes are 
				//      defined in the enumerator TileType in Tile.h. You DON'T need to pass a filename parameter for the texture.

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'w':
			{
				// II.C (2/5) Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				/// III.A Call the function "buildEntityAt" to create a Log pointer. The parameters are the filename to 
				///       the file with the sprite ("img/log.png"), the column and the row where the log should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				/// 
				auto img_log = buildEntityAt<Log>("img/log.png", col, row);

				addEntity(img_log);/// uncomment this (you may have to change "ent" for the name of the pointer you've just created above).
	
				//By default, entities stand on corridors
				// II.C (3/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{

				/// III.B Call the function "buildEntityAt" to create a Potion pointer. The parameters are the filename to 
				///       the file with the sprite ("img/potion.png"), the column and the row where the potion should be place.
				///		  Then, uncomment the call to the funcion "addEntity" passing the pointer to the new entity as parameter.
				
				auto img_potion = buildEntityAt<Potion>("img/potion.png", col, row);
				addEntity(img_potion);			/// uncomment this
	
				//By default, entities stand on corridors
				// II.C (4/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{

				// IV.B (1/4): Create the player shared pointer.
				player = std::make_shared<Player>();

				// IV.B (2/4): Call the function that initializes the Sprite Sheet with a single parameter, a const std::string& filename.
				//			   This string should be "img/DwarfSpriteSheet_data.txt"
				player->initSpriteSheet("img/DwarfSpriteSheet_data.txt");

				// IV.B (3/4): Call the function that positions the sprite of the player in the board (Player::positionSprite). 
				//			   Parameters are the row and column where this object goes in the board, the sprite width and height (const int Game::spriteWH) 
				//			   and the scale for the tiles (const float Game::tileScale)
				player->positionSprite(row, col, spriteWH, tileScale);

				// IV.B (4/4): Call our function to add an entity to a game passing the player that has just been created.
				addEntity(player);

				//By default, entities stand on corridors:
				// II.C (5/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	// III.I This function adds an entity, received by parameter, to the collection of entities.
	//       This must: i) Increase the entity counter (note: the very first entity should have a ID = 1).
	//		 ii) Assign the ID to the entity received by parameter. iii) Add the entity to the vector of entities of this class.
	
	idCounter++;	
	newEntity->setID(idCounter);  // Assign the ID to the entity received by parameter
	entities.push_back(newEntity);  // Add the entity to the vector of entities of this class
}

void Game::handleInput()
{
	// V.C: Call the fucntion that handles the input for the game and retrieve the command returned in a variable.
	//      Then, call the "execute" method of the returned object to run this command.
	auto Handler = inputHandler->handleInput();

	if (Handler != nullptr){
		Handler->execute(*this);
	}
	else {
		void();
	}
			
	// V.D: Call the function handleInput on the player's object.
	player->handleInput(*this);

}


void Game::update(float elapsed)
{
	// First call bigArray function
	bigArray(elapsed);

	// V.E Only update the game entities if the game is not paused.
	if (!isPaused()){
		auto iterator = entities.begin();
		while (iterator != entities.end()) {
			(*iterator)->update(this, elapsed);
			++iterator;
		}
	}
		// Collisions block:
	// IX.C: Retrieve a reference to the player's bounding box and run through all entities (using an itereator)  
		//      in the game with a while loop. You don't need to check the player's bounding box to itself, 
		//      so include a check that skips the player entity while looping through the entities vector.
	auto playerBox = player->getBoundingBox();
	for (auto& entity : entities)
	{
		if (entity == player)continue;


		// IX.D: (Inside the loop) Once you have a different entity to player, retrieve it's bounding box
		//       and check if they intersect.
		if (playerBox.intersects(entity->getBoundingBox()))//player box is bigger
		{
			// IX.E (if there is an intesection) Write a switch statement that determines the type of the object (which you
			//      can retrieve with getEntityType()) we are colliding with. For each case, add a console print out that 
			//      says what are you colliding with.
			switch (entity->getEntityType())
			{
			case EntityType::POTION:
			{
				// IX.F: This is a potion
				auto potion = dynamic_cast<Potion*>(entity.get());
				auto value = potion->getHealth();
				player->getHealthComp()->changeHealth(value);
				ServiceLocator::getAudio()->playSound("potion");
				std::cout << "Collide with potion, restore " << value << "Health, now Health=" << player->getHealthComp()->getHealth() << std::endl;
				potion->deleteEntity();
				// Increment the player's potion count and notify the achievement system
				player->incrementPotionCount();
				AchievementSystem::getInstance().notify(*player, "PotionCollected");
				break;
			}

			case EntityType::LOG:
			{
				// IX.G: This is a log
				if (player->isAttacking()
					&& player->getSpriteSheet()->getCurrentAnim()->getName() == "Attack"
					&& player->getSpriteSheet()->getCurrentAnim()->isInAction())
				{
					auto log = dynamic_cast<Log*>(entity.get());
					auto value = log->getWood();
					player->addWood(value);
					std::cout << "Collide with log, get " << value << "Wood, now Wood=" << player->getWood() << std::endl;
					log->deleteEntity();
				}
				break;
			}

			default:
				break;
			}
		}
	}
							


		// X.D Write a loop that iterates through all entities and removes them from the vector of entities.
		//     Use the function erase from std::vector, which receives an iterator. 
		//     Q? Should you ALWAYS advance the iterator in this loop?
	entities.erase(
		std::remove_if(entities.begin(), entities.end(), [this](const auto _Ent)
			{
				if (_Ent->isDeleted())
				{
					return true;
				}
	return false;
			}),
		entities.end());

	//Update the window for refreshing the graphics (leave this OUTSIDE the !paused block)
	window.update();
}

void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	// II.D Call the draw method of the board object passing a pointer to the window.
	board->draw(getWindow());

	// III.J Draw all units. Write a loop that iterates over all entities in this class's vector
	//       and calls the "draw" method in the entities.
	for (auto& entity : entities) {
		entity->draw(getWindow());
	}

	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

// III.G Return the current ID counter.
EntityID Game::getIDCounter()
{
	return idCounter;
	//return 0;  //you can delete this once III.G is complete.
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	// III.H Return the pointer to the entity which is in position "idx" of the vector.
	//       You must verify that the index is within the bounds of the vector.
	if (idx >= entities.size()) {
		std::cerr << "Index out of bounds error in getEntity()." << std::endl;
		return nullptr;
	}

	return entities[idx];   // Return the pointer to the entity at the specified index.

	//return nullptr;		//you can delete this once III.H is complete.
}

void Game::bigArray(float elapsed)
{
	auto systemIt = systems.begin();
	while (systemIt != systems.end())
	{
		auto entityIt = entities.begin();
		while (entityIt != entities.end())
		{
			if (!(*entityIt)->isDeleted() && (*systemIt)->validate(*entityIt))
			{
				(*systemIt)->update(this, *entityIt, elapsed);
			}
			++entityIt;
		}
		++systemIt;
	}
}