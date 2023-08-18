#include "stdafx.h"
#include "PlayerController.h"

#include <btGhostObject.h>

namespace QEngine
{
	PlayerController::PlayerController(GameObject* gameObject, btKinematicCharacterController* pController)
	{
		this->gameObject = gameObject;
		controller = pController;
	}

	PlayerController::PlayerController() { }
	PlayerController::~PlayerController() { }

	void PlayerController::Initialise() 
	{
		if (controller != nullptr)
			printf("Controller not null");
		else
			printf("Controller is null");
	}

	void PlayerController::Update() 
	{
		if (gameObject != nullptr)
			MoveForward(1, 5);
		else
			printf("GameObject is null");
	}

	void PlayerController::MoveForward(int dir, float Speed)
	{
		forwardDir = controller->getGhostObject()->getWorldTransform().getBasis()[2];
		forwardDir.normalize();

		if (dir == 1)
			direction += forwardDir;
		else if (dir == -1)
			direction -= forwardDir;

		controller->setWalkDirection(direction * (btScalar(1.1) * Speed));
	}

	void PlayerController::MoveLeft(int dir, float Speed)
	{
		strafingDir = controller->getGhostObject()->getWorldTransform().getBasis()[0];
		strafingDir.normalize();

		if(dir == 1)
			direction += strafingDir;
		else if(dir == -1)
			direction -= strafingDir;

		controller->setWalkDirection(direction * (btScalar(1.1) * Speed));
	}
}