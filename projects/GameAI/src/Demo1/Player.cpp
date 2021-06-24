#include "Demo1/Player.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "FollowPathBehaviour.h"
#include "Path.h"

using Demo1::Player;

Player::Player() : GameObject()
{
	m_path = new Path();
	m_path->Add({ 100, 100 });
	m_path->Add({ 200, 100 });
	m_path->Add({ 300, 100 });
	m_path->Add({ 400, 100 });
	m_path->Add({ 500, 100 });
	m_path->Add({ 600, 100 });
	m_path->Add({ 700, 100 });
	m_path->Add({ 700, 200 });
	m_path->Add({ 700, 300 });
	m_path->Add({ 600, 300 });
	m_path->Add({ 500, 300 });
	m_path->Add({ 400, 300 });
	m_path->Add({ 300, 300 });
	m_path->Add({ 200, 300 });
	m_path->Add({ 100, 300 });
	m_path->Add({ 100, 200 });
	m_path->Add({ 100, 200 });


	m_keyboardController = new KeyboardBehaviour();

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetRange(20);

	m_seekBehaviour->OnTargetArrive([this]() {
		SetBehaviour(m_keyboardController);
	});

	m_followPath = new FollowPathBehaviour();
	m_followPath->SetPath(m_path);

	SetBehaviour(m_followPath);
	SetFriction(1.0f);
	SetMaxSpeed(300);
	SetMaxForce(300);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_followPath;
	delete m_seekBehaviour;
	delete m_keyboardController;

	delete m_path;
}

void Player::Update(float deltaTime)
{
	// check left mouse button pressed
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		m_seekBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_seekBehaviour);
	}

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		m_followPath->SetPath(m_path);
		SetBehaviour(m_followPath);
	}

	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}