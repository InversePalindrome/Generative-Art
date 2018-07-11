/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"
#include "ParticleSystem.hpp"

#include <pretzel/PretzelGui.h>

#include <cinder/Timer.h>
#include <cinder/app/App.h>


class ArtScene : public Scene
{
public:
	explicit ArtScene(SceneManager& sceneManager);

	virtual void update() override;
	virtual void draw() override;

private:
	cinder::Timer timer;
	cinder::app::WindowRef controlWindow;

	pretzel::PretzelGuiRef mainGui;
	pretzel::PretzelGuiRef controlGui;

	ParticleSystem particleSystem;

	std::string particlesToAdd;

	std::string emissionRate;

	std::string totalLifeTime;
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

	cinder::ColorA startColor;
	cinder::ColorA startColorVariance;

	cinder::ColorA endColor;
	cinder::ColorA endColorVariance;

	void load();
	void save();

	void addParticles();
	void clearParticles();

	void setTexture();
};