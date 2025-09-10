#pragma once

#include "GameManager.h"

template <class T>
void Alive::Attack()
{
    static_assert(std::is_base_of<Projectile, T>::value, "T must derive from Projectile");
    T* projectile = mp_gameManager->createObject<T>();
    &projectile->setPosition(this->m_position);
}