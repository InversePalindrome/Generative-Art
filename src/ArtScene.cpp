/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "SceneManager.hpp"
#include "LifeTimeAffector.hpp"
#include "ColorGradientAffector.hpp"
#include "LinearVelocityAffector.hpp"
#include "AngularVelocityAffector.hpp"

#include <CinderImGui.h>


ArtScene::ArtScene(SceneManager& sceneManager) :
	Scene(sceneManager),
	particlesToAdd(0),
	currentAffectorType(0),
	currentEmitterType(0)
{
	timer.start();
}

void ArtScene::update()
{
	auto isParticleSystemOpen = true;

	ImGui::Begin("Particle System", &isParticleSystemOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
	
	ImGui::SetWindowPos({ 0.f, 0.f });

	addMenuBar();

	addParticleSystemTree();

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

void ArtScene::addMenuBar()
{
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
}

void ArtScene::addParticleSystemTree()
{
	if (ImGui::TreeNode("Particle System"))
	{
		addAffectorNode();
		addEmitterNode();

		ImGui::TreePop();
	}
}

void ArtScene::addAffectorNode()
{
	auto isAffectorsOpen = ImGui::TreeNode("Affectors");

	ImGui::SameLine();

	if (ImGui::Button("Add##openAddAffector"))
	{
		ImGui::OpenPopup("Add Affector");
	}

	auto isAddAffectorOpen = true;

	if (ImGui::BeginPopupModal("Add Affector", &isAddAffectorOpen, ImGuiWindowFlags_AlwaysAutoResize))
	{
		const char* affectorTypes[] = { "Life Time", "Linear Velocity", "Angular Velocity", "Color Gradient" };

		ImGui::Combo("Affector Types", &currentAffectorType, affectorTypes, 4);

		if (ImGui::Button("Add##addAffector"))
		{
			switch (currentAffectorType)
			{
			case 0:
				particleSystem.addAffector(std::make_unique<LifeTimeAffector>());
				break;
			case 1:
				particleSystem.addAffector(std::make_unique<LinearVelocityAffector>());
				break;
			case 2:
				particleSystem.addAffector(std::make_unique<AngularVelocityAffector>());
				break;
			case 3:
				particleSystem.addAffector(std::make_unique<ColorGradientAffector>());
				break;
			}

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear##clearAffector"))
	{
		particleSystem.clearAffectors();
	}

	if (isAffectorsOpen)
	{
		for (const auto& affector : particleSystem.getAffectors())
		{
			ImGui::Text(affector->getAffectorType()._to_string());
		}

		ImGui::TreePop();
	}
}

void ArtScene::addEmitterNode()
{
	auto isEmittersOpen = ImGui::TreeNode("Emitters");

	ImGui::SameLine();

	if (ImGui::Button("Add##openAddEmitter"))
	{
		ImGui::OpenPopup("Add Emitter");
	}

	auto isAddEmitterOpen = true;

	if (ImGui::BeginPopupModal("Add Emitter", &isAddEmitterOpen, ImGuiWindowFlags_AlwaysAutoResize))
	{

		ImGui::EndPopup();
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear##clearEmitter"))
	{
		particleSystem.clearEmitters();
	}

	if (isEmittersOpen)
	{
		for (auto& emitter : particleSystem.getEmitters())
		{

		}

		ImGui::TreePop();
	}
}