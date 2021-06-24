
#include "GameObject.h"
#include "Behaviour.h"
#include <iostream>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{

	if (IsKeyDown(KEY_SPACE))
		return;

	m_debugForceLines.clear();

	if (m_behaviour != nullptr)
		m_behaviour->Update(this, deltaTime);

	// m_velocity += m_acceleration * deltaTime;
	// m_position += m_velocity * deltaTime;
	// AddForce( -m_velocity * m_friction); // apply friction
	auto frictionForce = Vector2Scale(Vector2Negate(m_velocity), m_friction);
	ApplyForce(frictionForce);

	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));
	
	
	
	float speed = Vector2Length(m_velocity);
	if (speed > GetMaxSpeed())
		m_velocity = Vector2Scale(Vector2Normalize(m_velocity), GetMaxSpeed());
	
	AddDebugLine(m_acceleration, RED, 2);
	AddDebugLine(m_velocity, BLACK, 1);

	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));

	// reset acceleration
	m_acceleration = { 0, 0 };
}

void GameObject::Draw()
{

	if (m_behaviour != nullptr)
		m_behaviour->Draw(this);

	DrawCircle(m_position.x, m_position.y, 8, GRAY);
	
	// Draw Debug Lines
	for (const auto& line : m_debugForceLines)
	{
		DrawLineEx(m_position, Vector2Add(m_position, line.vec), line.thickness, line.color);
	}
	
}

void GameObject::ApplyForce(const Vector2& force)
{
	// m_acceleration += force;
	m_acceleration = Vector2Add(m_acceleration, force);
}

void GameObject::AddDebugLine(const Vector2& vec, const Color& col, float thickness)
{
	m_debugForceLines.push_back({ vec, col, thickness });
}

// Getters
const Vector2& GameObject::GetPosition() const
{
	return m_position;
}
const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}
const float& GameObject::GetFriction() const
{
	return m_friction;
}

Behaviour* GameObject::GetBehaviour()
{
	return m_behaviour;
}

const float& GameObject::GetMaxSpeed() const
{
	return m_maxSpeed;
}

const float& GameObject::GetMaxForce() const
{
	return m_maxForce;
}

// Setters
void GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}
void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void GameObject::SetFriction(const float& friction)
{
	m_friction = friction;
}

void GameObject::SetBehaviour(Behaviour* behaviour)
{
	m_behaviour = behaviour;
}
void GameObject::SetMaxSpeed(const float& speed)
{
	m_maxSpeed = speed;
}

void GameObject::SetMaxForce(const float& force)
{
	m_maxForce = force;
}