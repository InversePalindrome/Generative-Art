/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Particle.hpp
InversePalindrome.com
*/


#pragma once

#include <cinder/Vector.h>

#include <chrono>


class Particle
{
public:
	explicit Particle(const cinder::vec2& position);

	cinder::vec2 getPosition() const;
	void setPosition(const cinder::vec2& position);

	cinder::vec2 getVelocity() const;
	void setVelocity(const cinder::vec2& velocity);

	std::chrono::milliseconds getLifeTime() const;
	void setLifeTime(const std::chrono::milliseconds& lifeTime);

private:
	cinder::vec2 position;
	cinder::vec2 velocity;

	std::chrono::milliseconds lifeTime;
};