#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../components/PositionComponent.h"
#include "../components/Components.h" 
#include "../utils/Bitmask.h" 
#include "../components/TTLComponent.h"


class PositionComponent;

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, float scale);
	void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void update(Game* game, float elapsed = 1.0f);
	void draw(Window* window);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	//void setVelocity(const Vector2f& v) { velocity.x = v.x; velocity.y = v.y; }
	//const Vector2f& getPosition() const { return position; }
	const Vector2f& getPosition() const;

	//const Vector2f& getVelocity() const { return velocity; }
	Rectangle& getBoundingBox() { return boundingBox; };
	const sf::Vector2f& getSpriteScale() const;
	sf::Vector2i getTextureSize() const;
	EntityType getEntityType() const { return type; }
	const SpriteSheet* getSpriteSheet() const { return &spriteSheet; }
	//float getSpeed() const { return speed; }
	bool isSpriteSheetEntity() const { return isSpriteSheet; }

	
	// X.C  Add two helper functions. One that returns the value of the deleted flag, another one that 
	//      "deletes" the entity by setting this flag to true. (Q: one of this functions should be "const", which one?).
	bool isDeleted() const { return deleted; }
	void deleteEntity() { deleted = true; }

	PositionComponent& getPositionComponent() {
		return *position;
	}

	// Add the getComponentSet() function
	const Bitmask& getComponentSet() const {
		return componentSet;
	}

	// Add the addComponent() function
	void addComponent(std::shared_ptr<Component> component) {
		componentSet.turnOnBit(static_cast<unsigned int>(component->getID()));
	}

	bool hasComponent(Bitmask mask) const;
	virtual std::shared_ptr<TTLComponent> getTTLComponent();

protected:

	EntityType type;
	EntityID id;

	//Position and velocity
	//Vector2f position;
	std::shared_ptr<PositionComponent> position;

	//Vector2f velocity;
	//float speed;

	//Collision
	Rectangle boundingBox;
	Vector2f bboxSize;

	//Graphics-related variables.
	bool isSpriteSheet;
	SpriteSheet spriteSheet;
	sf::Texture texture;
	sf::Sprite sprite;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;

	// Add the Bitmask member variable
	Bitmask componentSet;

};

