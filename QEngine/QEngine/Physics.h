#pragma once
#include "btBulletDynamicsCommon.h"
#include "GameObject.h"

namespace QEngine
{
	class Physics
	{
	public:
		Physics(LinkedList<GameObject>* objects);
		~Physics();

	public:
		static float step;

	private:
		LinkedList<GameObject>* renderedObjects;

		btDiscreteDynamicsWorld* physicsWorld;
		btBroadphaseInterface* overlappingPairCache;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;

	public:	
		void UpdatePhysics(float deltaTime);

		btDiscreteDynamicsWorld* GetPhysicsWorld();
	};
}
