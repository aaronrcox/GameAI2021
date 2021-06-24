#include "FollowPathBehaviour.h"
#include "Path.h"
#include "GameObject.h"
#include <algorithm>


FollowPathBehaviour::FollowPathBehaviour()
{

}

FollowPathBehaviour::~FollowPathBehaviour()
{

}

void FollowPathBehaviour::Update(GameObject* obj, float deltaTime)
{
	Vector2 p1 = (*m_path)[m_currentPathIndex];
	float dist = Vector2Distance(obj->GetPosition(), p1);

	if (dist < 20)
	{
		m_currentPathIndex = (m_currentPathIndex + 1) % m_path->Count();
		p1 = (*m_path)[m_currentPathIndex];
	}

	// get the heading position
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());
	

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(p1, obj->GetPosition()));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());

	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());

	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());
	obj->AddDebugLine(forceDir, BLUE, 2);

	obj->ApplyForce(forceDir);
}
void FollowPathBehaviour::Draw(GameObject* obj) {
	m_path->Draw();
}

Path* FollowPathBehaviour::GetPath()
{
	return m_path;
}

void FollowPathBehaviour::SetPath(Path* path) {
	m_path = path;
}