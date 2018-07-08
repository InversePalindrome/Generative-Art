/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Application.hpp
InversePalindrome.com
*/


#pragma once

#include "SceneManager.hpp"
#include "ParticleSystem.hpp"

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>


class Application : public cinder::app::App
{
public:
	static void initSettings(cinder::app::App::Settings* settings);

	virtual void setup() override;
	virtual void update() override;
	virtual void draw() override;

private:
	SceneManager sceneManager;
};

CINDER_APP(Application, cinder::app::RendererGl, Application::initSettings)