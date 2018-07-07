/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"
#include "TextureManager.hpp"

#include <cinder/gl/wrapper.h>


void Application::initSettings(cinder::app::App::Settings* settings)
{
	settings->setTitle("Generative Art");
}

void Application::setup()
{
	TextureManager::getInstance().load("Textures.xml");
	particleSystem.load("Particles.xml");

	timer.start();
}

void Application::update() 
{
	particleSystem.update(timer.getSeconds());

	timer.start();
}

void Application::draw() 
{
	cinder::gl::clear();
	cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

	particleSystem.draw();
}