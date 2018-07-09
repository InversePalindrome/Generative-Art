/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SplashScene.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"

#include <cinder/Timer.h>
#include <cinder/gl/Texture.h>


class SplashScene : public Scene
{
public:
	explicit SplashScene(SceneManager& sceneManager);

	virtual void update() override;
	virtual void draw() override;

private:
	cinder::Timer timer;
	const double splashTime;

	cinder::gl::Texture2dRef& splashScreen;
};