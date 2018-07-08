/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SceneManager.cpp
InversePalindrome.com
*/


#include "SceneManager.hpp"


void SceneManager::update()
{
	scenes.top()->update();
}

void SceneManager::draw()
{
	scenes.top()->draw();
}

void SceneManager::popScene()
{
	scenes.pop();
}