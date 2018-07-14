/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - DefaultEmitter.hpp
InversePalindrome.com
*/


#pragma once

#include "Emitter.hpp"


class DefaultEmitter : public Emitter
{
public:
	DefaultEmitter();

	virtual void update(ParticleSystem& particleSystem, float deltaTime) override;
	
private:
	float emissionDifference;

	std::size_t numberOfEmittedParticles(float deltaTime);
};