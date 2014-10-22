#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "defines.hpp"
#include "entity.hpp"
#include "game.hpp"

class Player : public BoxEntity
{
public:
    Player(const b2Vec2 &position);
    ~Player();

    void initialize();
    void draw();

private:
    static const float WIDTH;
    static const float HEIGHT;

    Game::Event::Handle _eventHandles[4];
};

#endif
