#include "stdafx.h"
#include "FBXMesh.h"

namespace QEngine 
{
	FBXMesh::FBXMesh(const char * fileName)
	{
		this->fileName = fileName;
	}

	FBXMesh::~FBXMesh() 
	{ 
		cout << "\nModel has been destroyed!";
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void FBXMesh::Initialise()
	{
		FbxManager*	manager = FbxManager::Create();

		FbxIOSettings*	ioSettings = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(ioSettings);

		FbxImporter* importer = FbxImporter::Create(manager, "");
		importer->Initialize(fileName, -1, manager->GetIOSettings());

		FbxScene* scene = FbxScene::Create(manager, "");
		importer->Import(scene);
		importer->Destroy();

		FbxNode* rootNode = scene->GetRootNode();
		FbxGeometryConverter converter(rootNode->GetFbxManager());

		if (!converter.Triangulate(scene, true))
			cout << "Error: Triangulation" << endl;

		if (rootNode)
			this->GetFBXInfo(rootNode);

		manager->Destroy();

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create vertex buffer 
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER,		(sizeof(GLfloat) * vertices.size()) + (sizeof(GLfloat) * normals.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (sizeof(GLfloat) * vertices.size()), &vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER,	(sizeof(GLfloat) * vertices.size()), (sizeof(GLfloat) * normals.size()), &normals[0]);

		// Specifies the location of the data within the buffer. 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)(sizeof(GLfloat) * (vertices.size())));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		numberVertices = vertices.size() / 3;
		vertices.clear();
		normals.clear();
		texcoords.clear();
	}

	void FBXMesh::Render()
	{
		// Bind the vertex array
		glBindVertexArray(vao);

		// Draw the mesh using the vertices
		glDrawArrays(GL_TRIANGLES, 0, numberVertices);

		// Unbind the vertex array
		glBindVertexArray(0);
	}

	void FBXMesh::GetFBXInfo(FbxNode* node)
	{
		int colldx		= 0;
		int numKids		= node->GetChildCount();

		FbxNode* childNode = 0;

		for (int i = 0; i < numKids; i++)
		{
			childNode	  = node->GetChild(i);
			FbxMesh* mesh = childNode->GetMesh();

			if (mesh != NULL)
			{
				FbxVector4* VertexArray	= NULL;

				const int VertexCount		= mesh->GetControlPointsCount();
				const int PolygonCount		= mesh->GetPolygonCount();

				VertexArray = new FbxVector4[VertexCount];
				memcpy(VertexArray, mesh->GetControlPoints(), VertexCount * sizeof(FbxVector4));

				for (int PolygonIndex = 0; PolygonIndex < PolygonCount; PolygonIndex++)
				{
					// We converted the data to triangles so we should get 3 of each for all the points
					const int VerticeCount = mesh->GetPolygonSize(PolygonIndex);

					for (int VerticeIndex = 0; VerticeIndex < VerticeCount; VerticeIndex++) {

						vertices.push_back(VertexArray[mesh->GetPolygonVertex(PolygonIndex, VerticeIndex)].mData[0]);
						vertices.push_back(VertexArray[mesh->GetPolygonVertex(PolygonIndex, VerticeIndex)].mData[1]);
						vertices.push_back(VertexArray[mesh->GetPolygonVertex(PolygonIndex, VerticeIndex)].mData[2]);

						FbxVector4 normal;
						mesh->GetPolygonVertexNormal(PolygonIndex, VerticeIndex, normal);

						normals.push_back(normal.mData[0]);
						normals.push_back(normal.mData[1]);
						normals.push_back(normal.mData[2]);
					}
				}
			}

			this->GetFBXInfo(childNode);
		}
	}
}