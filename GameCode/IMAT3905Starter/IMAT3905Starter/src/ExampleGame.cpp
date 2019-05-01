#include "ExampleGame.h"

#include "ModelManager.h"
#include "Scene.h"

//needed for test code
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneStateComponent.h"


//#include <stdio.h>
#include <string>
//#include <vector>
//#include <iostream>
//#include <fstream>
#include <sstream>
//#include "InputHandler.h"

ExampleGame::ExampleGame(IEngineCore* engine) : Game(engine)
{
	Initialise();

}

bool m_bOnce = true; 

void ExampleGame::update(float dt) 
{
	m_scene->update(dt); 

	if (m_iMouseButtons == 1)
	{
		if (m_bOnce == true)
		{
			m_scene->m_AddArrow(1);

			m_bOnce = false; 
		}
	}
	else if (m_iMouseButtons == 0)
	{
		m_scene->m_SetArrowMoving();
	}

	int desiredSceneIndex = m_scene->getPlayer()->getComponent<SceneStateComponent>()->GetSceneIndex();

	if (desiredSceneIndex != m_sceneIndex)
	{
		delete m_scene;


		m_sceneIndex = desiredSceneIndex;

		m_scene = new Scene(m_sLevelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
		m_inputHandler = new InputHandler(m_scene->getPlayer());  // or have a set function perhaps better then a new instance!
	}
}

void ExampleGame::render() 
{
	m_scene->render(m_engineInterfacePtr);

	double frameDuration = m_engineInterfacePtr->getFrameDuration();

	if (frameDuration > 0)
	{
		glm::vec3 eulerAngles = m_scene->getPlayer()->getEulerAngles();

		// convert to deg
		eulerAngles.x = glm::degrees(eulerAngles.x);
		eulerAngles.y = glm::degrees(eulerAngles.y);
		eulerAngles.z = glm::degrees(eulerAngles.z);
		std::ostringstream oss;
		oss << " (" << eulerAngles.x << ", " << eulerAngles.y << ", " << eulerAngles.z << ")"; // fps:" << (1 / frameDuration);
		//oss << frameDuration;
		m_engineInterfacePtr->renderText(oss.str(), 0.01f, 0.01f, 1, glm::vec3(1, 1, 0));
	}
}

void ExampleGame::Initialise()
{
	m_theModelManager = new ModelManager();	// singleton later...
	m_scene = new Scene(m_sLevelNames[m_sceneIndex], m_theModelManager, m_engineInterfacePtr);
	m_inputHandler = new InputHandler(m_scene->getPlayer());

}

void ExampleGame::SetMouseInput(int mouseInput)
{
	m_iMouseButtons = mouseInput;
}

void ExampleGame::SetXY(double mouseX, double mouseY)
{
	m_dMouseX = mouseX;
	m_dMouseY = mouseY; 
}
