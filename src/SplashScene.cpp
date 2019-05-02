/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - SplashScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "SplashScene.hpp"
#include "SceneManager.hpp"
#include "TextureManager.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>


SplashScene::SplashScene(SceneManager& sceneManager) :
    Scene(sceneManager),
    splashTime(3.0),
    splashScreen(TextureManager::getInstance()[Texture::SplashScreen])
{
    timer.start();
}

void SplashScene::update()
{
    if (timer.getSeconds() >= splashTime)
    {
        sceneManager.popScene();
        sceneManager.pushScene<ArtScene>();
    }
}

void SplashScene::draw()
{
    cinder::gl::clear(cinder::ColorA::white());
    cinder::gl::draw(splashScreen, { (cinder::app::getWindowWidth() - splashScreen->getWidth()) / 2.f, (cinder::app::getWindowHeight() - splashScreen->getHeight()) / 2.f });
}