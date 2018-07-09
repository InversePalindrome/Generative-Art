/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Scene.hpp
InversePalindrome.com
*/


#pragma once

class SceneManager;


class Scene
{
public:
	explicit Scene(SceneManager& sceneManager);

	virtual void onEnter();
	virtual void onExit();

	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	SceneManager& sceneManager;
};