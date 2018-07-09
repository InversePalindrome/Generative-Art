/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"
#include "ParticleSystem.hpp"

#include <pretzel/PretzelGui.h>


class ArtScene : public Scene
{
public:
	explicit ArtScene(SceneManager& sceneManager);

	virtual void update() override;
	virtual void draw() override;

private:
	ParticleSystem particleSystem;

	pretzel::PretzelGuiRef gui;

	float emissionRate;

	std::string lifeTime;
	std::string lifeTimeVariance;

	std::string xPosition;
	std::string yPosition;

	std::string xPositionVariance;
    std::string yPositionVariance;

    std::string widthScale;
	std::string heightScale;

	float widthScaleVariance;
	float heightScaleVariance;

	std::string angle;
	float angleVariance;

	std::string xLinearVelocity;
	std::string ylinearVelocity;
	
	std::string xLinearVelocityVariance;
	std::string yLinearVelocityVariance;
	
	std::string angularVelocity;
	std::string angularVelocityVariance;
};