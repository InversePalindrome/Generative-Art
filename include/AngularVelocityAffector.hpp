/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - AngularVelocityAffector.hpp
InversePalindrome.com
*/


#pragma once

#include "Affector.hpp"


class AngularVelocityAffector : public Affector
{
public:
    AngularVelocityAffector();

    virtual void update(Particle& particle, float deltaTime) override;
};