/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - TextureManager.cpp
InversePalindrome.com
*/


#include "TextureManager.hpp"

#include <cinder/app/App.h>

#include <pugixml.hpp>


TextureManager& TextureManager::getInstance()
{
	static TextureManager textureManager;

	return textureManager;
}

void TextureManager::load(const std::string& filename)
{
	pugi::xml_document doc;

	if (doc.load_file(cinder::app::getAssetPath(filename).c_str()))
	{
		if (const auto texturesNode = doc.child("Textures"))
		{
			for (const auto textureNode : texturesNode.children())
			{
				textures.emplace(Texture::_from_string(textureNode.name()), cinder::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset(textureNode.text().as_string()))));
			}
		}
	}
}

cinder::gl::Texture2dRef& TextureManager::operator[](Texture texture)
{
	return textures.at(texture);
}

const cinder::gl::Texture2dRef& TextureManager::operator[](Texture texture) const
{
	return textures.at(texture);
}