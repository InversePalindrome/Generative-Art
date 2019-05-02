/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Affector.hpp
InversePalindrome.com
*/


#pragma once

#include "Particle.hpp"

#include <pugixml.hpp>

#include <enum.h>


BETTER_ENUM(AffectorType, int, LifeTime, LinearVelocity, AngularVelocity, ColorGradient)

class Affector
{
public:
    explicit Affector(AffectorType affectorType);

    virtual void load(const pugi::xml_node& affectorNode);
    virtual void save(pugi::xml_node& affectorNode) const;
    virtual void update(Particle& particle, float deltaTime) = 0;

    AffectorType getAffectorType() const;

private:
    AffectorType affectorType;
};