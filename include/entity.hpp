#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include <cstdint>
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include <string>

#include "colors.hpp"

// Base virtual entity class
class Entity
{
public:
    // Entity types, for collision handling purposes
    enum Type
    {
        BARRIER = 0x1,
        PADDLE  = 0x2,
        BALL    = 0x4,
        BLOCK   = 0x8
    };

    // Constructor/destructor
    Entity(const std::string &name, Type type = Type::BARRIER);
    virtual ~Entity();

    // Update and draw functions, called in every tick of the loop
    virtual void update(float dt) {}
    virtual void draw() = 0;

    // Collision handlers
    virtual void startContact(const Entity *other, const b2Fixture *otherFixture) {}
    virtual void endContact(const Entity *other, const b2Fixture *otherFixture) {}

    // Various getters
    inline std::string getName() const { return _name; }
    Type getType() const { return _type; }
    bool isMarkedForDeath() const { return _markedForDeath; }
    virtual std::string toString() const;

protected:
    // This is the most badass function name ever
    void markForDeath() { _markedForDeath = true; }

private:
    std::string _name;
    Type _type;
    bool _markedForDeath;
};

// Helper stream operators
template <class T>
inline std::ostream &operator<<(std::ostream &stream, const Entity &e)
{
    stream << e.toString();
    return stream;
}

inline MAKE_LOGGABLE(Entity, e, stream)
{
    stream << e.toString();
    return stream;
}

#endif
