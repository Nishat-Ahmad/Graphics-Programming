#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"

// Game-related State data
SpriteRenderer *Renderer;
GameObject      *Player;
BallObject      *Ball;

// -----------------------------------------------------------
// COLLISION DETECTION FUNCTION (AABB - Circle)
// -----------------------------------------------------------
bool CheckCollision(BallObject &one, GameObject &two)
{
    // 1. Get center point of the circle (Ball)
    glm::vec2 center(one.Position + one.Radius);
    
    // 2. Calculate AABB info (center, half-extents) for the Box (Brick)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    
    // 3. Get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    
    // 4. Clamp the difference vector to the AABB half-extents
    //    (This finds the point on the AABB closest to the circle)
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    
    // 5. Add clamped value to AABB_center so we get the value of the closest point on the box
    glm::vec2 closest = aabb_center + clamped;
    
    // 6. Get vector between center circle and closest point AABB
    difference = closest - center;
    
    // 7. If length < radius, we have a collision
    return glm::length(difference) < one.Radius;
}
// -----------------------------------------------------------


Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 
}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Ball;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    
    // load textures
    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");

    // load levels
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    // configure player
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - 50.0f, this->Height - 20.0f);
    Player = new GameObject(playerPos, glm::vec2(100.0f, 20.0f), ResourceManager::GetTexture("paddle"));

    // configure ball
    glm::vec2 ballPos = playerPos + glm::vec2(100.0f / 2.0f - 12.5f, -12.5f * 2.0f);
    Ball = new BallObject(ballPos, 12.5f, glm::vec2(100.0f, -350.0f), ResourceManager::GetTexture("face"));
}

void Game::Update(float dt)
{
    // update objects
    Ball->Move(dt, this->Width);
    
    // check for collisions
    this->DoCollisions();
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = 500.0f * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }
}

void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), 
            glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f
        );
        this->Levels[this->Level].Draw(*Renderer);
        Player->Draw(*Renderer);
        Ball->Draw(*Renderer);
    }
}

// NEW: Function Implementation
void Game::DoCollisions()
{
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            if (CheckCollision(*Ball, box))
            {
                if (!box.IsSolid)
                    box.Destroyed = true;
            }
        }
    }
}