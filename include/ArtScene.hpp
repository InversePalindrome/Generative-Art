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

	std::experimental::filesystem::path texturePath;

	int particlesToAdd;

	void setTexture();
};