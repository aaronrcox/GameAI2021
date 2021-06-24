#pragma once

#include "raymath.h"
#include <vector>

class Behaviour;

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ApplyForce(const Vector2& force);

	// Getters
	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const float& GetFriction() const;
	const float& GetMaxSpeed() const;
	const float& GetMaxForce() const;

	Behaviour* GetBehaviour();

	// Setters
	void SetPosition(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& friction);
	void SetMaxSpeed(const float& speed);
	void SetMaxForce(const float& force);
	void SetBehaviour(Behaviour* behaviour);

	void AddDebugLine(const Vector2& vec, const Color& col, float thickness = 1.0f);

protected:

	Vector2 m_position = { 0.0f, 0.0f };
	Vector2 m_velocity = { 0.0f, 0.0f };
	Vector2 m_acceleration = { 0.0f, 0.0f };

	float m_friction = 0.0f;

	float m_maxSpeed = 100;
	float m_maxForce = 100;

	Behaviour* m_behaviour = nullptr;

private:

	struct DebugForceLines
	{
		Vector2 vec;
		Color color;
		float thickness;
	};

	std::vector< DebugForceLines > m_debugForceLines;

};
