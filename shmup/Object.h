#pragma once

#include "Sprite.h"

class GameManager;

class Object
{
public:
    Object();
    virtual ~Object();

    static constexpr float CONTACT_EPS = 1.0f;
    
    sf::Vector2f m_position;
    Sprite* mp_sprite;

    // rotation
    //float m_rotation;

    // scale
    float getWidth() { return mp_width; }
    float getHeight() { return mp_height; }
    void setWidth(float width);
    void setHeight(float height);

    void setSize(sf::Vector2f size);
    sf::Vector2f getSize();

    virtual void start();
    virtual void update();

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    // function rotate
    //void rotate(float rotation);

    static float getDistance(Object* objectA, Object* objectB);
    static float getDistance(sf::Vector2f* aPosition, sf::Vector2f* bPosition);

    static bool isOverlappingStrict(sf::Vector2f aPos, sf::Vector2f aSize,
                                    sf::Vector2f bPos, sf::Vector2f bSize);

    static bool isTouchingOrOverlapping(sf::Vector2f aPos, sf::Vector2f aSize,
                                        sf::Vector2f bPos, sf::Vector2f bSize,
                                        float eps = CONTACT_EPS);
    
    static bool isColliding(sf::Vector2f aPos, sf::Vector2f aSize,
                            sf::Vector2f bPos, sf::Vector2f bSize);
    static bool isColliding(Object* a, Object* b);
    bool isCollidingWith(Object* objectB);
    bool isCollidingWithAnyObstacle();
    bool wouldCollideAt(const sf::Vector2f& aPosition, const sf::Vector2f& aSize) const;

    virtual void onCollisionEnter(Object* other) {}
    virtual void onCollisionStay(Object* other) {}
    virtual void onCollisionExit(Object* other) {}

    enum ObjectType
    {
        TObstacle = 0,
        TPlayer = 1,
        TProjectile = 2,
        TEnemy = 3,
        TCollectible = 4,
        TWall = 5
    };

    ObjectType getType() { return mp_objectType; }
    void setType(ObjectType type) { mp_objectType = type; }

protected:
    GameManager* mp_gameManager = nullptr;
    ObjectType mp_objectType;

private:
    float mp_width;
    float mp_height;
};
