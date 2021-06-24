#pragma once

#include "Behaviour.h"
#include "raymath.h"

class Path;

class FollowPathBehaviour : public Behaviour
{
public:

	FollowPathBehaviour();
	virtual ~FollowPathBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);


	Path* GetPath();
	void SetPath(Path* path);


protected:

	Path* m_path = nullptr;
	int m_currentPathIndex = 0;

private:
};