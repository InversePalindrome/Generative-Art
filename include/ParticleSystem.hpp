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
	friend class ArtScene;

public:
	void load(const std::string& filename);
	void save(const std::string& filename);

	void update(float deltaTime);
	void draw();

	void emitParticle(const Particle& particle);

	void addAffector(std::unique_ptr<Affector> affector);
	void clearAffectors();
	
	void addEmitter(std::unique_ptr<Emitter> emitter);
	void clearEmitters();

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