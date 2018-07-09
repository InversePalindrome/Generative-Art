/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SplashScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "SplashScene.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"


SplashScene::SplashScene(SceneManager& sceneManager) :
	Scene(sceneManager),
	splashTime(3.0),
	splashScreen(TextureManager::getInstance()[Texture::SplashScreen])
{
	timer.start();
}

void SplashScene::update()
{
	if (timer.getSeconds() >= splashTime)
	{
		sceneManager.popScene();
		sceneManager.pushScene<ArtScene>();
	}
}

void SplashScene::draw()
{
	cinder::gl::clear(cinder::ColorA::white());
	cinder::gl::draw(splashScreen);
}