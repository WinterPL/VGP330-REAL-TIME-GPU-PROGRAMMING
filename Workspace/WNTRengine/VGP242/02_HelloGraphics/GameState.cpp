#include "GameState.h"

using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize()
{
    GraphicsSystem::Get()->SetClearColor(Colors::Black);
}
void GameState::Update(float deltaTime)  // read input and GraphicsSystem::Get->SetClearColor(Colors::red)...press another, set another color
{
    if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::ONE))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Red);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::TWO))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Green);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::THREE))
    {
        GraphicsSystem::Get()->SetClearColor(Colors::Blue);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::FOUR))
    {
        GraphicsSystem::Get()->SetClearColor(WNTRengine::Colors::Yellow);
    }
    else if (InputSystem::Get()->IsKeyPressed(Input::KeyCode::FIVE))
    {
        GraphicsSystem::Get()->SetClearColor(WNTRengine::Colors::Black);
    }
}