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
	std::vector<std::function<void()>> removalCallbacks;

	int particlesToAdd;
	int currentAffectorType;
	int currentEmitterType;

	void addTexture();

	void addMenuBar();
	void addParticleSystemTree();
	void addPauseParticles();
	void addClearParticles();
	void addAffectorsNode();
	void addEmittersNode();
	void addTexturesNode();

	void updateRemovals();
};