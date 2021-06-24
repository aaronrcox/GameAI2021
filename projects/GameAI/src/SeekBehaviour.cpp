#include "SeekBehaviour.h"
#include "GameObject.h"
#include "raylib.h"
#include <algorithm>

SeekBehaviour::SeekBehaviour() : Behaviour()
{

}

SeekBehaviour::~SeekBehaviour()
{

}

void SeekBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(m_target, obj->GetPosition());
	if (distToTarget < m_range)
	{
		if (m_onArriveFn)
			m_onArriveFn();
	}

	// get the heading position
	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());


	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());

	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());

	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), 
		obj->GetMaxForce());
	obj->AddDebugLine(forceDir, BLUE);

	obj->ApplyForce(forceDir);
}

void SeekBehaviour::Draw(GameObject* obj)
{

	DrawCircle(m_target.x, m_target.y, m_range, LIGHTGRAY);
	DrawCircle(m_target.x, m_target.y, 4, GRAY);
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;
}
void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& SeekBehaviour::GetRange() const
{
	return m_range;
}
void SeekBehaviour::SetRange(const float& range)
{
	m_range = range;
}

void SeekBehaviour::OnTargetArrive(OnArriveFn callback)
{
	m_onArriveFn = callback;
}