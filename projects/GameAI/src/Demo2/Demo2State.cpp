#include "Demo2/Demo2State.h"

#include "Game.h"
#include "AssetManager.h"
#include "GameStateManager.h"
#include "raylib.h"

#include "Graph2D.h"
#include "Graph2DEditor.h"

using namespace Demo2;

Demo2State::Demo2State(Game* app) : IGameState(app)
{
	m_graph = new Graph2D();


	int numRows = 4;
	int numCols = 6;
	float xOffset = 100;
	float yOffset = 100;
	float spacing = 50;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			m_graph->AddNode({
				x * spacing + xOffset,
				y * spacing + yOffset
				});
		}
	}


	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(node->data, 60, nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node)
				continue;

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}
	}




	m_graphEditor = new Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);
}

Demo2State::~Demo2State()
{
	delete m_graphEditor;
	m_graphEditor = nullptr;

	delete m_graph;
	m_graph = nullptr;
}

void Demo2State::Update(float deltaTime)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		m_app->GSM()->PopState();
		m_app->GSM()->PushState("Menu");
	}

	m_graphEditor->Update(deltaTime);
}

void Demo2State::Draw()
{
	DrawTextEx(AssetManager::GetInstance()->fntDeltaGothicOne, "Demo 2", { 10, 10 }, 48, 0, GRAY);

	m_graphEditor->Draw();
}

