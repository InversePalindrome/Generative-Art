/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "SceneManager.hpp"
#include "DefaultEmitter.hpp"
#include "LifeTimeAffector.hpp"
#include "ColorGradientAffector.hpp"
#include "LinearVelocityAffector.hpp"
#include "AngularVelocityAffector.hpp"

#include <CinderImGui.h>

#include <cinder/app/AppBase.h>


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

	updateRemovals();

	particleSystem.update(static_cast<float>(timer.getSeconds()));

	timer.start();
}

void ArtScene::draw()
{
	particleSystem.draw();
}

void ArtScene::addTexture()
{
	particleSystem.addTexture(cinder::app::getOpenFilePath().string());
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
			
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void ArtScene::addParticleSystemTree()
{
	if (ImGui::TreeNode("Particle System"))
	{
		addClearParticles();
		addAffectorsNode();
		addEmittersNode();
		addTexturesNode();

		ImGui::TreePop();
	}
}

void ArtScene::addClearParticles()
{
	ImGui::SameLine();

	if (ImGui::Button("Clear"))
	{
		particleSystem.clearParticles();
	}
}

void ArtScene::addAffectorsNode()
{
	auto isAffectorsOpen = ImGui::TreeNode("Affectors");

	ImGui::SameLine();

	if (ImGui::Button("Add##openAddAffector"))
	{
		ImGui::OpenPopup("Add Affector");
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear##clearAffector"))
	{
		particleSystem.clearAffectors();
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

	if (isAffectorsOpen)
	{
		std::size_t affectorID = 0;

		for (const auto& affector : particleSystem.getAffectors())
		{
			ImGui::Text(affector->getAffectorType()._to_string());

			ImGui::SameLine();

			ImGui::PushID(++affectorID);

			if (ImGui::Button("Remove##removeAffector"))
			{
				removalCallbacks.push_back([this, &affector]() { particleSystem.removeAffector(affector); });
			}

			ImGui::PopID();
		}

		ImGui::TreePop();
	}
}

void ArtScene::addEmittersNode()
{
	auto isEmittersOpen = ImGui::TreeNode("Emitters");

	ImGui::SameLine();

	if (ImGui::Button("Add##openAddEmitter"))
	{
		ImGui::OpenPopup("Add Emitter");
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear##clearEmitter"))
	{
		particleSystem.clearEmitters();
	}

	auto isAddEmitterOpen = true;

	if (ImGui::BeginPopupModal("Add Emitter", &isAddEmitterOpen, ImGuiWindowFlags_AlwaysAutoResize))
	{
		const char* emitterTypes[] = { "Default" };

		ImGui::Combo("Emitter Types", &currentEmitterType, emitterTypes, 1);

		if (ImGui::Button("Add##addEmitter"))
		{
			switch (currentEmitterType)
			{
			case 0:
				particleSystem.addEmitter(std::make_unique<DefaultEmitter>());
				break;
			}

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	if (isEmittersOpen)
	{
		std::size_t emitterID = 0;

		for (auto& emitter : particleSystem.getEmitters())
		{
			ImGui::PushID(++emitterID);

			auto isEmitterOpen = ImGui::TreeNode(emitter->getEmitterType()._to_string());

			ImGui::SameLine();

			if (ImGui::Button("Remove##removeEmitter"))
			{
				removalCallbacks.push_back([this, &emitter]() { particleSystem.removeEmitter(emitter); });
			}

			if (isEmitterOpen)
			{
				ImGui::InputFloat("Emission Rate", &emitter->emissionRate);

				ImGui::InputInt("Texture Index", &emitter->textureIndex);

				ImGui::SameLine();

				ImGui::InputInt("Texture Index Variance", &emitter->textureIndexVariance);

				ImGui::InputFloat("Life Time", &emitter->totalLifeTime);

				ImGui::SameLine();

				ImGui::InputFloat("Life Time Variance", &emitter->lifeTimeVariance);

				ImGui::InputFloat2("Position(x, y)", &emitter->position[0]);

				ImGui::SameLine();

				ImGui::InputFloat2("Position Variance(x, y)", &emitter->positionVariance[0]);

				ImGui::InputFloat2("Scale(width, height)", &emitter->scale[0]);

				ImGui::SameLine();

				ImGui::InputFloat2("Scale Variance(width, height)", &emitter->scaleVariance[0]);

				ImGui::InputFloat("Angle", &emitter->angle);

				ImGui::SameLine();

				ImGui::InputFloat("Angle Variance", &emitter->angleVariance);

				ImGui::InputFloat2("Linear Velocity", &emitter->linearVelocity[0]);

				ImGui::SameLine();

				ImGui::InputFloat2("Linear Velocity Variance", &emitter->linearVelocityVariance[0]);

				ImGui::InputFloat("Angular Velocity", &emitter->angularVelocity);

				ImGui::SameLine();

				ImGui::InputFloat("Angular Velocity Variance", &emitter->angularVelocityVariance);

				ImGui::ColorEdit3("Start Color", &emitter->startColor[0]);

				ImGui::SameLine();

				ImGui::ColorEdit3("Start Color Variance", &emitter->startColorVariance[0]);

				ImGui::ColorEdit3("End Color", &emitter->endColor[0]);

				ImGui::SameLine();

				ImGui::ColorEdit3("End Color Variance", &emitter->endColorVariance[0]);

				ImGui::TreePop();
			}

			ImGui::PopID();
		}

		ImGui::TreePop();
	}
}

void ArtScene::addTexturesNode()
{
	auto isTexturesOpen = ImGui::TreeNode("Textures");

	ImGui::SameLine();

	if (ImGui::Button("Add##addTexture"))
	{
		addTexture();
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear##clearTextures"))
	{
		particleSystem.clearTextures();
	}

	if (isTexturesOpen)
	{
		std::size_t textureIndex = 0;

		for (const auto& texture : particleSystem.getTextures())
		{
			ImGui::Image(texture.second, texture.second->getSize());

			ImGui::SameLine();

			ImGui::PushID(textureIndex++);
			
			if (ImGui::Button("Remove##removeTexture"))
			{
				removalCallbacks.push_back([this, &texture]() { particleSystem.removeTexture(texture.second); });
			}

			ImGui::PopID();
		}

		ImGui::TreePop();
	}
}

void ArtScene::updateRemovals()
{
	for (const auto& removal : removalCallbacks)
	{
		removal();
	}

	removalCallbacks.clear();
}