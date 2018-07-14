/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "Conversions.hpp"
#include "SceneManager.hpp"

#include <CinderImGui.h>


ArtScene::ArtScene(SceneManager& sceneManager) :
	Scene(sceneManager),
	particlesToAdd(0)
{
	timer.start();
}

void ArtScene::update()
{
	bool controlsOpened = true;
	ImGui::Begin("Particle System", &controlsOpened, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
	
	ImGui::SetWindowPos({ 0.f, 0.f });

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "Ctrl+O"))
			{
				particleSystem.load(cinder::app::getOpenFilePath().string());
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				particleSystem.save(cinder::app::getSaveFilePath().string());
			}
			if (ImGui::MenuItem("Set Texture"))
			{
				setTexture();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	if (ImGui::TreeNode("Particle System"))
	{
		if (ImGui::TreeNode("Affectors"))
		{
			ImGui::TreePop();
		}

		ImGui::SameLine();

		if (ImGui::Button("Add"))
		{
		
		}

		ImGui::SameLine();

		if (ImGui::Button("Clear"))
		{
			particleSystem.clearAffectors();
		}

		if (ImGui::TreeNode("Emitters"))
		{
			ImGui::TreePop();
		}

		ImGui::SameLine();

		if (ImGui::Button("Add"))
		{

		}

		ImGui::SameLine();
		
		if (ImGui::Button("Clear"))
		{
			particleSystem.clearEmitters();
		}


		ImGui::TreePop();
	}

	ImGui::End();

	particleSystem.update(timer.getSeconds());

	timer.start();
}

void ArtScene::draw()
{
	particleSystem.draw();
}

void ArtScene::setTexture()
{
    texturePath = cinder::app::getOpenFilePath();

	if (!texturePath.empty())
	{
		particleSystem.setTexture(cinder::gl::Texture2d::create(cinder::loadImage(texturePath)));
	}
}