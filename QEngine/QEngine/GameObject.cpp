#include "stdafx.h"
#include "GameObject.h"

namespace QEngine
{
	GameObject::GameObject(string name) :name(name)
	{
		cout << "Loading Game Object " << name << " into level." << endl;

		components	= new LinkedList<Component>();
		active		= true;
		tag			= "";

		rigidBody = 0;
	}

	/// x _
	/// y |
	/// z /
	GameObject::GameObject(string name, string tag, vec3 position, vec3 rotation, vec3 scale)
	{
		cout << "Loading Game Object " << name << " into level." << endl;

		components = new LinkedList<Component>();

		this->active = true;
		this->name	 = name;
		this->tag	 = tag;

		// Assign the transform of the gameObject
		transform = new Transform(this, position, rotation, scale);
		AddComponent(transform);
	}

	GameObject::~GameObject()
	{
		delete components;
	}

	void GameObject::Destroy()
	{
		active = false;
	}

	void GameObject::Initialise()
	{
		for (int i = 0; i < components->Count(); i++)
			components->Get(i)->Initialise();
	}

	bool GameObject::IsActive()
	{
		return active;
	}

	void GameObject::Update()
	{
		for (int i = 0; i < components->Count(); i++)
			components->Get(i)->Update();
	}

	void GameObject::SetTag(string tag)
	{
		this->tag = tag;
	}

	void GameObject::AddComponent(Component* component)
	{
		// Ensuring only one type of this component can be assigned to this GameObject
		if (typeid(RigidBody) == typeid(*component))
		{
			if (rigidBody == NULL)
			{
				rigidBody = (RigidBody*)component;

				component->gameObject = this;
				components->Insert(component);
			}

			return;
		}
		else if (typeid(PlayerController) == typeid(*component))
		{
			if (playerController == NULL)
			{
				playerController = (PlayerController*)component;

				component->gameObject = this;
				components->Insert(component);
			}

			return;
		}
		else if (typeid(Script) == typeid(*component))
		{
			if (script == NULL)
			{
				script = (Script*)component;

				component->gameObject = this;
				components->Insert(component);
			}

			return;
		}
		component->gameObject = this;
		components->Insert(component);
	}

	string GameObject::GetName()
	{
		return name;
	}

	string GameObject::GetTag()
	{
		return tag;
	}

	Transform * GameObject::GetTransform()
	{
		return transform;
	}

	RigidBody* GameObject::GetRigidBody()
	{
		return rigidBody;
	}

	PlayerController * GameObject::GetPlayerController()
	{
		return playerController;
	}

	Script* GameObject::GetScript()
	{
		return script;
	}
}