#pragma once
#include "Game.h"

#include "Defs.h"
#include "MouseInputs.h"
#include "../CameraObject.h"

class ModelManager;

/*! \class A game created with the game engine's functionality. */
class ExampleGame : public Game
{
public:

	/*! \fn Constructor */
	ExampleGame(IEngineCore* engine);

	/*! \fn Used to update this class every frame.
	*Param One float The current delta (change in) time since last frame.
	*/
	void update(float dt) override;

	/*! \fn Used to render all game objects into the current scene. */
	void render() override;

	/*! \fn Used for setting up the game. */
	void Initialise();

	void SetMouseInput(int mouseInput);

	void SetXY(double mouseX, double mouseY);

private:

	/*! \var This will manage all of teh models used within this game. */
	ModelManager* m_theModelManager;

	MouseInputs temp; 

	/*! \var Used to keep track of the current scene or level. */
	int m_sceneIndex{ 0 };

	//these could be loaded from a file...
	/*! \var A list of levels via their file path. */
	std::string m_levelNames[2] = {
		"assets/levels/testLevel.json",
		"assets/levels/testLevel2.json"
	};

	int m_mouseButtons;
	double m_mouseX;
	double m_mouseY;
};
