#pragma once

#include "IGameState.h"

namespace Menu
{
	class MenuState : public IGameState
	{
	public:

		MenuState(Game* gsm);
		virtual ~MenuState();

		virtual void Update(float deltaTime);
		virtual void Draw();

	private:

	};
}