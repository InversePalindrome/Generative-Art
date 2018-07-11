/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"
#include "SplashScene.hpp"
#include "TextureManager.hpp"

#include <cinder/gl/wrapper.h>


void Application::initSettings(cinder::app::App::Settings* settings)
{
	settings->setTitle("Generative Art");
}

void Application::setup()
{
	TextureManager::getInstance().load("Textures.xml");

	sceneManager.pushScene<SplashScene>();
}

void Application::update() 
{
	sceneManager.update();
}

void Application::draw() 
{
	cinder::gl::clear();
	cinder::gl::setMatricesWindow(cinder::app::getWindowSize());
	
	sceneManager.draw();
}