/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ResourceManager.hpp
InversePalindrome.com
*/


#pragma once

#include "Texture.hpp"
#include "EnumHash.hpp"

#include <cinder/gl/Texture.h>

#include <string>
#include <unordered_map>


class ResourceManager
{
public:
	void loadResources(const std::string& filename);

private:
	std::unordered_map<Texture, cinder::gl::Texture2dRef, EnumHash<Texture>> textures;
};