/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"
#include "ParticleSystem.hpp"

#include <cinder/Timer.h>


class ArtScene : public Scene
{
public:
	explicit ArtScene(SceneManager& sceneManager);

	virtual void update() override;
	virtual void draw() override;

private:
	cinder::Timer timer;

	ParticleSystem particleSystem;

	int particlesToAdd;
	int currentAffectorType;
	int currentEmitterType;

	void setTexture();

	void addMenuBar();

	void addParticleSystemTree();
	void addClearParticles();
	void addAffectorNode();
	void addEmitterNode();
};