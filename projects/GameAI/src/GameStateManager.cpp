#include "GameStateManager.h"

#include <assert.h>

//constructor
GameStateManager::GameStateManager()
{

}

//destructor
GameStateManager::~GameStateManager()
{
	ProcessCommands();
}

//should be called each frame by the "Game" class
void GameStateManager::UpdateGameStates(float dt)
{
	ProcessCommands();

	for (auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{
		bool isBlocked = false;

		// loop through all states above this one.
		for (auto itr1 = itr + 1; itr1 != m_gameStateStack.end(); itr1++)
			isBlocked = isBlocked || (*itr1)->IsUpdateBlocking();

		if (isBlocked)
			continue;

		(*itr)->Update(dt);
	}
}

void GameStateManager::DrawGameStates()
{

	for (auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{
		bool isBlocked = false;

		// loop through all states above this one.
		for (auto itr1 = itr + 1; itr1 != m_gameStateStack.end(); itr1++)
			isBlocked = isBlocked || (*itr1)->IsDrawBlocking();

		if (isBlocked)
			continue;

		(*itr)->Draw();
	}
}

void GameStateManager::ProcessCommands()
{
	for (unsigned int i = 0; i < m_commands.size(); i++)
	{
		if (m_commands[i].cmd == E_PUSH_BY_NAME)
		{
			auto iter = m_availableStates.find(m_commands[i].name);
			if (iter != m_availableStates.end())
			{
				m_gameStateStack.push_back(iter->second);
				iter->second->OnPush();
			}
		}
		else if (m_commands[i].cmd == E_PUSH_BY_PTR)
		{
			m_gameStateStack.back()->OnPush();
			m_gameStateStack.push_back(m_commands[i].pState);
		}
		else if (m_commands[i].cmd == E_POP)
		{
			if (m_gameStateStack.size() > 0)
			{
				m_gameStateStack.back()->OnPop();
				m_gameStateStack.pop_back();
			}
		}
		else if (m_commands[i].cmd == E_SET)
		{
			auto iter = m_availableStates.find(m_commands[i].name);

			if (iter != m_availableStates.end())
			{
				assert(IsStateOnStack(iter->second) == false && "Cannot Set State when it is currently on the stack");
				delete iter->second;
			}

			m_availableStates[m_commands[i].name] = m_commands[i].pState;
		}
		else if (m_commands[i].cmd == E_REMOVE_BY_NAME)
		{
			auto iter = m_availableStates.find(m_commands[i].name);
			if (iter != m_availableStates.end())
			{
				auto stateIter = std::find(m_gameStateStack.begin(), m_gameStateStack.end(), iter->second);
				if (stateIter != m_gameStateStack.end())
					m_gameStateStack.erase(stateIter);
			}
		}
		else if (m_commands[i].cmd == E_REMOVE_BY_PTR)
		{
			auto stateIter = std::find(m_gameStateStack.begin(), m_gameStateStack.end(), m_commands[i].pState);
			if (stateIter != m_gameStateStack.end())
				m_gameStateStack.erase(stateIter);
		}
	}

	//now that all commans have been processed, clear the list for the next frame...
	m_commands.clear();
}

IGameState* GameStateManager::GetStateFromStack(int index)
{
	int stackSize = (int)m_gameStateStack.size();
	if (index >= stackSize || index < -stackSize)
		return nullptr;

	if (index >= 0)
		return m_gameStateStack[index];

	return m_gameStateStack[m_gameStateStack.size() + index];

}

IGameState* GameStateManager::GetStateByName(const char* name)
{
	auto iter = m_availableStates.find(name);

	if (iter != m_availableStates.end())
		return iter->second;

	return nullptr;
}

bool GameStateManager::IsStateOnStack(const char* name)
{
	IGameState* state = GetStateByName(name);

	if (state == nullptr)
		return false;

	return IsStateOnStack(state);
}
bool GameStateManager::IsStateOnStack(IGameState* state)
{
	// loop through the game state stack
	for (auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{
		if ((*itr) == state)
			return true;
	}

	return false;
}

//used to manipulate the game state stack
void GameStateManager::SetState(const char* name, IGameState* pState)
{
	SCommand command;
	command.cmd = E_SET;
	command.name = name;
	command.pState = pState;
	m_commands.push_back(command);
}

void GameStateManager::PushState(const char* name)
{
	SCommand command;

	command.cmd = E_PUSH_BY_NAME;
	command.name = name;
	command.pState = nullptr;

	m_commands.push_back(command);
}

void GameStateManager::PushState(IGameState* pState)
{
	SCommand command;

	command.cmd = E_PUSH_BY_PTR;
	command.pState = pState;

	m_commands.push_back(command);
}

void GameStateManager::PopState()
{
	SCommand command;
	command.cmd = E_POP;
	command.name = "";
	command.pState = nullptr;
	m_commands.push_back(command);
}

void GameStateManager::RemoveState(const char* name)
{
	SCommand command;

	command.cmd = E_REMOVE_BY_NAME;
	command.name = name;

	m_commands.push_back(command);
}

void GameStateManager::RemoveState(IGameState* pState)
{
	SCommand command;

	command.cmd = E_REMOVE_BY_PTR;
	command.pState = pState;

	m_commands.push_back(command);
}

unsigned int GameStateManager::GetActiveStackSize()
{
	return (unsigned int)m_gameStateStack.size();
}