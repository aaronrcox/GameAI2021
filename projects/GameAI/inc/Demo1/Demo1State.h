#pragma once

#pragma once

#include "IGameState.h"

namespace Demo1
{
	class Player;

	class Demo1State : public IGameState
	{
	public:

		Demo1State(Game* app);
		virtual ~Demo1State();

		virtual void Update(float deltaTime);
		virtual void Draw();

	private:

		Player* m_player = nullptr;
	};
}
