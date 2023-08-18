#include "stdafx.h"
#include "Physics.h"
#include "GameObject.h"
#include "Script.h"

namespace QEngine
{
	float Physics::step = 1.0 / 50.0;

	Physics::Physics(LinkedList<GameObject>* objects)
	{
		renderedObjects = objects;

		btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher				= new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache	= new btDbvtBroadphase();
		solver					= new btSequentialImpulseConstraintSolver;

		physicsWorld = new btDiscreteDynamicsWorld(
				dispatcher, 
				overlappingPairCache, 
				NULL, 
				collisionConfiguration
		);

		physicsWorld->setGravity(btVector3(0, -100, 0));
	}

	Physics::~Physics()
	{
		delete physicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
	}

	void Physics::UpdatePhysics(float deltaTime)
	{
		physicsWorld->stepSimulation(deltaTime);
	}

	btDiscreteDynamicsWorld * Physics::GetPhysicsWorld()
	{
		return physicsWorld;
	}
}
