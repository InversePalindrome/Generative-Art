/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtCreatorScene.cpp
InversePalindrome.com
*/


#include "SceneManager.hpp"
#include "ArtCreatorScene.hpp"

#include <cinder/app/App.h>


ArtCreatorScene::ArtCreatorScene(SceneManager& sceneManager) :
	Scene(sceneManager),
	creatorGui(pretzel::PretzelGui::create("Art Creator", cinder::app::getWindowWidth(), cinder::app::getWindowHeight()))
{
	creatorGui->setPos({ 0.f, 0.f });

	creatorGui->addSlider("Emission Rate", &emissionRate, 0.f, 1000.f);
	creatorGui->addTextField("X Position", &xPosition, true);
	creatorGui->addTextField("Y Position", &yPosition, true);
}

void ArtCreatorScene::update()
{
	
}

void ArtCreatorScene::draw()
{
	creatorGui->draw();
}