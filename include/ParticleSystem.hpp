/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Particle.hpp"

#include <vector>


class ParticleSystem
{
public:
	ParticleSystem();

	void update();
	void draw();

	void addParticles(std::size_t particleCount);
	void clearParticles();

	cinder::vec2 getSourcePosition() const;
	void setSourcePosition(const cinder::vec2& sourcePosition);

	cinder::vec2 getRange() const;
	void setRange(const cinder::vec2& range);

private:
	std::vector<Particle> particles;

	cinder::vec2 sourcePosition;
	cinder::vec2 range;
};