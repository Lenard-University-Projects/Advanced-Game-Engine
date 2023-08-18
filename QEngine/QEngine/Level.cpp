#include "stdafx.h"
#include "Level.h"
#include "Camera.h"
#include "light.h"
#include "shader.h"
#include "material.h"
#include "MeshRenderer.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "RigidBody.h"
#include "FBXMesh.h"
#include "Script.h"
#include "PlayerController.h"

#include <btKinematicCharacterController.h>
#include <btGhostObject.h>

namespace QEngine
{
	Level::Level(string name, lua_State* L)
	{
		physics = new Physics(gameObjects);

		this->name = name;
		gameObjects = new LinkedList<GameObject>();

		Shader* textureShader	= new Shader("../Assets/Shaders/TexturedPointLight.vert", "../Assets/Shaders/TexturedPointLight.frag");
		Shader* materialShader	= new Shader("../Assets/Shaders/PointLight.vert", "../Assets/Shaders/PointLight.frag");

		Material* crateMaterial = new Material(textureShader, "../Assets/Textures/crate.bmp",		Material::woodMaterial);
		Material* floorMaterial = new Material(textureShader, "../Assets/Textures/floor.bmp",		Material::brassMaterial);
		Material* ceilgMaterial = new Material(textureShader, "../Assets/Textures/Wall/wall.bmp",	Material::brassMaterial);
		Material* brickMaterial = new Material(textureShader, "../Assets/Textures/brick.bmp",		Material::brassMaterial);
	
		Material* redMaterial  = new Material(materialShader, NULL, Material::redPlasticMaterial);

		GameObject* camera = new GameObject("Main Camera", "camera", vec3(0, 0, 450));
		camera->AddComponent(new Script(camera, "../Assets/Scripts/CameraScript.lua", L));

		//Pass near and far planes
		Camera* cameraComponent = new Camera(camera, 0.1, 10000.0);
		camera->AddComponent(cameraComponent);

		//Assign primary camera
		Graphics::SetMainCamera(cameraComponent);

		// Lighting only appears to work when first in the list for updating!!!
		GameObject* light = new GameObject("Light", "light", vec3(0.0, 0.0, 100.0));
		  
		//Pass the light object and set the property to duskLight
		Light* lightComponent = new Light(light, Light::duskLight);
		light->AddComponent(lightComponent);
		gameObjects->Insert(light);

		//Assign primary camera
		Graphics::SetLight(lightComponent);

		// Creating objects to display in the scene

		/* Steps
			-> Create new GameObjects
			-> Add components to the gameObjects
			-> Add the gameObject in the level's list (GameObjects in the level)
		*/
		
		GameObject* box = new GameObject("box", "", vec3(210.0, -90.0, -100.0), vec3(0, 0, 0), vec3(50, 50, 50));
		box->AddComponent(new MeshRenderer(box, new CubeMesh(), crateMaterial));
		box->AddComponent(new RigidBody(box, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		gameObjects->Insert(box);

		GameObject* floor = new GameObject("Floor", "room", vec3(0, -150, 0), vec3(0, 0, 0), vec3(290, 10, 200));
		floor->AddComponent(new MeshRenderer(floor, new CubeMesh(), floorMaterial));
		floor->AddComponent(new RigidBody(floor, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		gameObjects->Insert(floor);

		GameObject* backWall = new GameObject("Back Wall", "room", vec3(0, 0, -200), vec3(0, 0, 0), vec3(400, 160, 10));
		backWall->AddComponent(new MeshRenderer(backWall, new CubeMesh(), brickMaterial));
		backWall->AddComponent(new RigidBody(backWall, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		gameObjects->Insert(backWall);

		GameObject* rightWall = new GameObject("Right wall", "room", vec3(300, 0, 0), vec3(0, 0, 0), vec3(10, 160, 200));
		rightWall->AddComponent(new MeshRenderer(rightWall, new CubeMesh(), brickMaterial));
		rightWall->AddComponent(new RigidBody(rightWall, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		gameObjects->Insert(rightWall);

		GameObject* leftWall = new GameObject("Left Wall", "room", vec3(-300, 0, 0), vec3(0, 0, 0), vec3(10, 160, 200));
		leftWall->AddComponent(new RigidBody(leftWall, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		leftWall->AddComponent(new MeshRenderer(leftWall, new CubeMesh(), brickMaterial));
		gameObjects->Insert(leftWall);

		GameObject* ceiling = new GameObject("Ceiling", "room", vec3(0, 150, 0), vec3(0, 0, 0), vec3(290, 10, 200));
		ceiling->AddComponent(new RigidBody(ceiling, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		ceiling->AddComponent(new MeshRenderer(ceiling, new CubeMesh(), brickMaterial));
		gameObjects->Insert(ceiling);

		// Creating the character
		btCapsuleShape* shape						= new btCapsuleShape(1.75, 1.75);
		btPairCachingGhostObject* ghost				= new btPairCachingGhostObject();
		btKinematicCharacterController* controller	= new btKinematicCharacterController(ghost, shape, 0.5);

		GameObject* peasant = new GameObject("Peasant", "player", vec3(-100, -149, 0));
		peasant->AddComponent(new MeshRenderer(peasant, new FBXMesh("../Assets/Models/Peasant/Peasant_Man.fbx"), redMaterial));
		//peasant->AddComponent(new RigidBody(peasant, shape, physics->GetPhysicsWorld(), 10, NULL, NULL));
		//peasant->AddComponent(new PlayerController(peasant, controller));
		peasant->AddComponent(new Script(peasant, "../Assets/Scripts/Character.lua", L));
		gameObjects->Insert(peasant);

		ghost->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-100, -150, 0)));
		ghost->setCollisionShape(shape);
		ghost->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

		physics->GetPhysicsWorld()->addAction(controller);
		physics->GetPhysicsWorld()->addCharacter(controller);
		physics->GetPhysicsWorld()->addCollisionObject(ghost, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
		physics->GetPhysicsWorld()->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

		GameObject* table = new GameObject("Table", "prop", vec3(-150, -140, -100), vec3(-90, -90, 0));
		table->AddComponent(new MeshRenderer(table, new FBXMesh("../Assets/Models/Table/Table_Wood.fbx"), crateMaterial));
		table->AddComponent(new RigidBody(table, new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(1.0))), physics->GetPhysicsWorld(), 0.0f, NULL, NULL));
		gameObjects->Insert(table);

		// Spawn 50 balls into the level
		for (int i = 0; i < 50; i++)
		{
			GameObject * sphere = new GameObject("Sphere", "ball", glm::vec3(i - 50, 15, 100), glm::vec3(0, 0, 0), glm::vec3(15, 15, 15));
			sphere->AddComponent(new MeshRenderer(sphere, new SphereMesh(), redMaterial));
			sphere->AddComponent(new RigidBody(sphere, new btSphereShape(btScalar(1.0)), physics->GetPhysicsWorld(), 10, NULL, NULL));
			gameObjects->Insert(sphere);
		}
	}

	Level::~Level()
	{
		delete gameObjects;
	}

	void Level::Initialise()
	{
		// Initialise all game objects
		GameObject *obj = gameObjects->first;

		while (obj != NULL)
		{
			obj->Initialise();
			obj = obj->next;
		}

		Graphics::GetMainCamera()->Initialise();
	}

	void Level::Update()
	{
		// Update the camera
		Graphics::GetMainCamera()->gameObject->Update();

		//Update all gameObjects
		GameObject *obj = gameObjects->first;

		while (obj != NULL)
		{
			obj->Update();

			// Remove inactive GameObjects
			if (!obj->IsActive())
			{
				gameObjects->Delete(obj);
				GameObject *temp = obj->next;

				delete obj;

				obj = temp->next;
			}
			else
				obj = obj->next;
		}
	}

	string Level::GetName()
	{
		return name;
	}
}