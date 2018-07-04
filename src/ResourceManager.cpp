/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ResourceManager.cpp
InversePalindrome.com
*/


#include "ResourceManager.hpp"

#include <cinder/app/App.h>
#include <cinder/app/Platform.h>

#include <pugixml.hpp>


void ResourceManager::loadResources(const std::string& filename)
{
	pugi::xml_document doc;

	if (doc.load_file((cinder::app::Platform::get()->getResourceDirectory().string() + filename).c_str()))
	{
		if (const auto resourcesNode = doc.child("Resources"))
		{
			for (const auto resourceNode : resourcesNode.children())
			{
				textures.emplace(Texture::_from_string(resourceNode.name()), cinder::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset(resourceNode.text().as_string()))));
			}
		}
	}
}