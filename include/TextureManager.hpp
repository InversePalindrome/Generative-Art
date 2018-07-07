/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - TextureManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Texture.hpp"

#include <cinder/gl/Texture.h>

#include <EnumHash.hpp>

#include <string>
#include <unordered_map>


class TextureManager
{
public:
	static TextureManager& getInstance();

	void load(const std::string& filename);

	cinder::gl::Texture2dRef& operator[](Texture texture);
	const cinder::gl::Texture2dRef& operator[](Texture texture) const;

private:
	std::unordered_map<Texture, cinder::gl::Texture2dRef, EnumHash<Texture>> textures;
};