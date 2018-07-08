/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtCreatorScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"

#include <pretzel/PretzelGui.h>


class ArtCreatorScene : public Scene
{
public:
	explicit ArtCreatorScene(SceneManager& sceneManager);

private:
	pretzel::PretzelGuiRef creatorGui;

	float emissionRate;
	float minLifeTime;
	float maxLifeTime;
	std::string xPosition;
	std::string yPosition;

	virtual void update() override;
	virtual void draw() override;
};