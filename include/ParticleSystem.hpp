/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Emitter.hpp"
#include "Affector.hpp"
#include "Particle.hpp"

#include <cinder/gl/Texture.h>

#include <vector>
#include <memory>


class ParticleSystem
{
public:
	void load(const std::string& filename);
	void save(const std::string& filename) const;

	void update(float deltaTime);
	void draw();

	void addParticle(const Particle& particle);
	void clearParticles();

	void addAffector(std::unique_ptr<Affector> affector);
	void clearAffectors();
	
	const std::vector<std::unique_ptr<Affector>>& getAffectors() const;

	void addEmitter(std::unique_ptr<Emitter> emitter);
	void clearEmitters();

	const std::vector<std::unique_ptr<Emitter>>& getEmitters() const;

	void setTexture(cinder::gl::Texture2dRef texture);

private:
	std::vector<Particle> particles;
	std::vector<std::unique_ptr<Affector>> affectors;
	std::vector<std::unique_ptr<Emitter>> emitters;

	cinder::gl::Texture2dRef texture;

	void updateAffectors(float deltaTime);
	void updateEmitters(float deltaTime);
	void removeDeadParticles();
};