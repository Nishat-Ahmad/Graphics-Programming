#include "game.h"
#include "resource_manager.h"

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Game::~Game()
{
    delete this;
}

void Game::Init()
{
    // Load shaders
    // ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    
    // Configure shaders
    // ...
    
    // Load textures
    // ...
}

void Game::Update(float dt)
{
    
}

void Game::ProcessInput(float dt)
{
    
}

void Game::Render()
{
    
}