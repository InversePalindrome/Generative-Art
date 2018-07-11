/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SceneManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Scene.hpp"

#include <vector>
#include <memory>
#include <functional>


class SceneManager
{
public:
	void update();
	void draw();

	template<typename T, typename... Ts>
	void pushScene(Ts... params);

	void popScene();

private:
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::function<void()>> sceneTransitions;
};

template<typename T, typename ...Ts>
void SceneManager::pushScene(Ts... params)
{
	sceneTransitions.push_back([this, params...]() {scenes.push_back(std::make_unique<T>(*this, params...)); });
}
