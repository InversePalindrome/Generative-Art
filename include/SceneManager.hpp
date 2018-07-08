/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SceneManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"
#include "ArtCreatorScene.hpp"

#include <stack>
#include <memory>


class SceneManager
{
public:
	void update();
	void draw();

	template<typename T>
	void pushScene();

	void popScene();

private:
	std::stack<std::unique_ptr<Scene>> scenes;
};

template<typename T>
void SceneManager::pushScene()
{
	scenes.push(std::make_unique<T>(*this));
}