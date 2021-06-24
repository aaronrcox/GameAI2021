#pragma once

#include "GameObject.h"

class SeekBehaviour;
class KeyboardBehaviour;
class FollowPathBehaviour;
class Path;

namespace Demo1
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Update(float deltaTime);
		virtual void Draw();

	protected:

		KeyboardBehaviour* m_keyboardController = nullptr;
		SeekBehaviour* m_seekBehaviour = nullptr;
		FollowPathBehaviour* m_followPath = nullptr;

		Path* m_path;

	private:
	};
}
