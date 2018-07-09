/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SceneManager.cpp
InversePalindrome.com
*/


#include "SceneManager.hpp"


void SceneManager::update()
{
	for (const auto& sceneTransition : sceneTransitions)
	{
		sceneTransition();
	}

    sceneTransitions.clear();

	scenes.back()->update();
}

void SceneManager::draw()
{
	scenes.back()->draw();
}

void SceneManager::popScene()
{
	sceneTransitions.push_back([this]() 
	{
		scenes.back()->onExit();

		scenes.pop_back(); 
	});
}