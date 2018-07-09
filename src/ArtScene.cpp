/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "Conversions.hpp"
#include "SceneManager.hpp"

#include <cinder/app/App.h>


ArtScene::ArtScene(SceneManager& sceneManager) :
	Scene(sceneManager),
	gui(pretzel::PretzelGui::create("Art Creator")),
	emissionRate(0.f),
	xPosition("0"),
	yPosition("0"),
	xPositionVariance("0"),
	yPositionVariance("0"),
	widthScale("1"),
	heightScale("1"),
	widthScaleVariance(0.f),
	heightScaleVariance(0.f),
	angle("0"),
	angleVariance(0.f),
	xLinearVelocity("0"),
	ylinearVelocity("0"),
	xLinearVelocityVariance("0"),
	yLinearVelocityVariance("0"),
	angularVelocity("0"),
	angularVelocityVariance("0")
{
	gui->setPos({ 0.f, 0.f });
	gui->addSlider("Emission Rate", &emissionRate, 0.f, 1000.f);
	gui->addTextField("Life Time", &lifeTime);
	gui->addTextField("Life Time Variance", &lifeTimeVariance);
	gui->addTextField("X Position", &xPosition, true);
	gui->addTextField("Y Position", &yPosition, true);
	gui->addTextField("X Position Variance", &xPositionVariance);
	gui->addTextField("Y Position Variance", &yPositionVariance);
	gui->addTextField("Width Scale", &widthScale);
	gui->addTextField("Height Scale", &heightScale);
	gui->addSlider("Width Scale Variance", &widthScaleVariance, 0.f, 0.5f);
	gui->addSlider("Height Scale Variance", &heightScaleVariance, 0.f, 0.5f);
	gui->addTextField("Angle", &angle);
	gui->addSlider("Angle Variance", &angleVariance, 0.f, 180.f);
	gui->addTextField("X Linear Velocity", &xLinearVelocity);
	gui->addTextField("Y Linear Velocity", &ylinearVelocity);
	gui->addTextField("X Linear Velocity Variance", &xLinearVelocityVariance);
	gui->addTextField("Y Linear Velocity Variance", &yLinearVelocityVariance);
	gui->addTextField("Angular Velocity", &angularVelocity);
	gui->addTextField("Angular Velocity Variance", &angularVelocityVariance);
}

void ArtScene::update()
{
	particleSystem.setEmissionRate(emissionRate);
	particleSystem.setLifeTime(Conversions::stringToFloat(lifeTime, 10.f));
	particleSystem.setLifeTimeVariance(Conversions::stringToFloat(lifeTimeVariance));
	particleSystem.setPosition({ Conversions::stringToFloat(xPosition), Conversions::stringToFloat(yPosition) });
	particleSystem.setPositionVariance({ Conversions::stringToFloat(xPositionVariance), Conversions::stringToFloat(yPositionVariance) });
	particleSystem.setScale({ Conversions::stringToFloat(widthScale, 1.f), Conversions::stringToFloat(heightScale, 1.f) });
	particleSystem.setScaleVariance({ widthScaleVariance, heightScaleVariance });
	particleSystem.setAngle(Conversions::stringToFloat(angle));
	particleSystem.setAngleVariance(angleVariance);
	particleSystem.setLinearVelocity({ Conversions::stringToFloat(xLinearVelocity), Conversions::stringToFloat(ylinearVelocity) });
	particleSystem.setLinearVelocityVariance({ Conversions::stringToFloat(xLinearVelocityVariance), Conversions::stringToFloat(yLinearVelocityVariance) });
	particleSystem.setAngularVelocity(Conversions::stringToFloat(angularVelocity));
	particleSystem.setAngularVelocityVariance(Conversions::stringToFloat(angularVelocityVariance));
}

void ArtScene::draw()
{
	particleSystem.draw();

	gui->drawAll();
}