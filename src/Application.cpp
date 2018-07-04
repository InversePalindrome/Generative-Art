/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Application.cpp
InversePalindrome.com
*/


#include "Application.hpp"

#include <cinder/gl/wrapper.h>


void Application::initSettings(cinder::app::App::Settings* settings)
{
	settings->setTitle("Generative Art");
}

void Application::setup()
{
	resourceManager.loadResources("Resources.xml");

	particleSystem.addParticles(50);
}

void Application::update() 
{
	particleSystem.update();
}

void Application::draw() 
{
	cinder::gl::clear();

	particleSystem.draw();
}