#include "stdafx.h"
#include "RigidBody.h"
#include "GameObject.h"

namespace QEngine
{
	RigidBody::RigidBody(GameObject* gameObject, btCollisionShape* shape, btDiscreteDynamicsWorld* pWorld, btScalar mass, btVector3* scale, btVector3* offset)
	{ 
		this->physicsWorld = pWorld;
		this->mass = mass;

		btTransform startTransform;
		startTransform.setIdentity();

		Transform* transform = gameObject->GetTransform();

		if (offset == NULL)
			startTransform.setOrigin(btVector3(transform->GetPosition().x, transform->GetPosition().y, transform->GetPosition().z));
		else
			startTransform.setOrigin(btVector3(transform->GetPosition().x + offset->x(), transform->GetPosition().y + offset->y(), transform->GetPosition().z + offset->z()));
	
		if (scale == NULL)
			shape->setLocalScaling(btVector3(transform->GetScale().x, transform->GetScale().y, transform->GetScale().z));
		else
			shape->setLocalScaling(*scale);

		isStatic = (mass == 0.0f);
		btVector3 localInertia(0, 0, 0);

		if (isStatic)
			shape->calculateLocalInertia(mass, localInertia);

		motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);

		rb = new btRigidBody(rbInfo);
		rb->setRestitution(.95f);
		rb->setFriction(1.2f);
		physicsWorld->addRigidBody(rb);
	}

	RigidBody::~RigidBody() 
	{
		physicsWorld->removeCollisionObject(rb);
		delete motionState;
		delete rb;
	}

	void RigidBody::Initialise() { }

	bool RigidBody::IsStatic()
	{
		return isStatic;
	}

	void RigidBody::Update() { }

	void RigidBody::GetPhysicsObjectTransform(btScalar* transform)
	{
		btTransform trans;
		motionState->getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}

	btRigidBody* RigidBody::GetPhysicsRigidBody()
	{
		return rb;
	}
}