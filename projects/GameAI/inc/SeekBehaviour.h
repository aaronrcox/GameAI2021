#pragma once

#include "Behaviour.h"
#include "raymath.h"
#include <functional>

class SeekBehaviour : public Behaviour
{
public:

	typedef std::function<void()> OnArriveFn;

	SeekBehaviour();
	virtual ~SeekBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetRange() const;
	void SetRange(const float& range);

	void OnTargetArrive(OnArriveFn callback);

protected:

	Vector2 m_target = { 0, 0 };
	float m_range = 0;

	OnArriveFn m_onArriveFn;

private:
};