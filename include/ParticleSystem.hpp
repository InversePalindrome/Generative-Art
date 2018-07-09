/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Particle.hpp"

#include <cinder/gl/Texture.h>

#include <string>
#include <vector>
#include <random>


class ParticleSystem
{
public:
	ParticleSystem();
	explicit ParticleSystem(const std::string& filename);

	void load(const std::string & filename);

	void update(float deltaTime);
	void draw();

	void addParticles(std::size_t particleCount);
	void clearParticles();

	float getEmissionRate() const;
	void setEmissionRate(float emissionRate);

	float getLifeTime() const;
	void setLifeTime(float lifeTime);

	float getLifeTimeVariance() const;
	void setLifeTimeVariance(float lifeTimeVariance);

	cinder::vec2 getPosition() const;
	void setPosition(const cinder::vec2& position);

	cinder::vec2 getPositionVariance() const;
	void setPositionVariance(const cinder::vec2& positionVariance);

	cinder::vec2 getScale() const;
	void setScale(const cinder::vec2& scale);

	cinder::vec2 getScaleVariance() const;
	void setScaleVariance(const cinder::vec2& scaleVariance);

	float getAngle() const;
	void setAngle(float angle);

	float getAngleVariance() const;
	void setAngleVariance(float angleVariance);

	cinder::vec2 getLinearVelocity() const;
	void setLinearVelocity(const cinder::vec2& linearVelocity);

	cinder::vec2 getLinearVelocityVariance() const;
	void setLinearVelocityVariance(const cinder::vec2& linearVelocityVariance);

	float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);

	float getAngularVelocityVariance() const;
	void setAngularVelocityVariance(float angularVelocityVariance);

private:
	std::vector<Particle> particles;

	std::vector<cinder::gl::Texture2dRef*> textures;
	std::vector<std::size_t> textureWeights;
	std::mt19937 randomEngine;

	float emissionRate;
	float emissionDifference;

	float lifeTime;
	float lifeTimeVariance;

	cinder::vec2 position;
	cinder::vec2 positionVariance;

	cinder::vec2 scale;
	cinder::vec2 scaleVariance;

	float angle;
	float angleVariance;

	cinder::vec2 linearVelocity;
	cinder::vec2 linearVelocityVariance;

	float angularVelocity;
	float angularVelocityVariance;

	void createParticles(float deltaTime);
	void removeDeadParticles();
};