#pragma once

#pragma once

#include "IGameState.h"
class Graph2DEditor;
class Graph2D;

namespace Demo2
{
	class Demo2State : public IGameState
	{
	public:

		Demo2State(Game* app);
		virtual ~Demo2State();

		virtual void Update(float deltaTime);
		virtual void Draw();

	private:

		Graph2DEditor* m_graphEditor = nullptr;
		Graph2D* m_graph = nullptr;
	};
}
