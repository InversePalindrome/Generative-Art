/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "Conversions.hpp"
#include "SceneManager.hpp"

#include <CinderImGui.h>

#include <pugixml.hpp>


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
				load();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				save();
			}
			if (ImGui::MenuItem("Set Texture"))
			{
				setTexture();
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::PushItemWidth(80.f);

	ImGui::InputFloat("Emission Rate", &particleSystem.emissionRate);

	ImGui::Separator();

	ImGui::InputFloat("Life Time", &particleSystem.totalLifeTime);

	ImGui::SameLine();

	ImGui::InputFloat("Life Time Variance", &particleSystem.lifeTimeVariance);

	ImGui::Separator();

	ImGui::InputFloat("X Position", &particleSystem.position.x);

	ImGui::SameLine();

	ImGui::InputFloat("X Position Variance", &particleSystem.positionVariance.x);

	ImGui::InputFloat("Y Position", &particleSystem.position.y);

	ImGui::SameLine();

	ImGui::InputFloat("Y Position Variance", &particleSystem.positionVariance.y);

	ImGui::Separator();

	ImGui::InputFloat("Width Scale", &particleSystem.scale.x);

	ImGui::SameLine();

	ImGui::InputFloat("Width Scale Variance", &particleSystem.scaleVariance.x);

	ImGui::InputFloat("Height Scale", &particleSystem.scale.y);

	ImGui::SameLine();

	ImGui::InputFloat("Height Scale Variance", &particleSystem.scaleVariance.y);

	ImGui::Separator();

	ImGui::InputFloat("Angle", &particleSystem.angle);

	ImGui::SameLine();

	ImGui::SliderFloat("Angle Variance", &particleSystem.angleVariance, 0.f, 180.f);

	ImGui::Separator();

	ImGui::InputFloat("X Linear Velocity", &particleSystem.linearVelocity.x);

	ImGui::SameLine();

	ImGui::InputFloat("X Linear Velocity Variance", &particleSystem.linearVelocityVariance.x);

	ImGui::InputFloat("Y Linear Velocity", &particleSystem.linearVelocity.y);

	ImGui::SameLine();

	ImGui::InputFloat("Y Linear Velocity Variance", &particleSystem.linearVelocityVariance.y);

	ImGui::Separator();

	ImGui::InputFloat("Angular Velocity", &particleSystem.angularVelocity);

	ImGui::SameLine();

	ImGui::InputFloat("Angular Velocity Variance", &particleSystem.angularVelocityVariance);

	ImGui::Separator();

	ImGui::ColorPicker3("Start Color", &particleSystem.startColor[0]);

	ImGui::SameLine();

	ImGui::ColorPicker3("Start Color Variance", &particleSystem.startColorVariance[0]);

	ImGui::ColorPicker3("End Color", &particleSystem.endColor[0]);

	ImGui::SameLine();

	ImGui::ColorPicker3("End Color Variance", &particleSystem.endColorVariance[0]);

	ImGui::Separator();
	
	ImGui::InputInt("", &particlesToAdd);

	ImGui::SameLine();

	if (ImGui::Button("Add Particles"))
	{
		particleSystem.addParticles(particlesToAdd);
	}
	
	ImGui::SameLine();

	if (ImGui::Button("Clear Particles"))
	{
		particleSystem.clearParticles();
	}

	ImGui::End();

	particleSystem.update(timer.getSeconds());

	timer.start();
}

void ArtScene::draw()
{
	particleSystem.draw();
}

void ArtScene::save()
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto particleSystemNode = doc.append_child("ParticleSystem");
	particleSystemNode.append_attribute("texture") = texturePath.string().c_str();
	particleSystemNode.append_attribute("emissionRate") = particleSystem.getEmissionRate();
	particleSystemNode.append_attribute("totalLifeTime") = particleSystem.getTotalLifeTime();
	particleSystemNode.append_attribute("xPosition") = particleSystem.getPosition().x;
	particleSystemNode.append_attribute("yPosition") = particleSystem.getPosition().y;
	particleSystemNode.append_attribute("xPositionVariance") = particleSystem.getPositionVariance().x;
	particleSystemNode.append_attribute("yPositionVariance") = particleSystem.getPositionVariance().y;
	particleSystemNode.append_attribute("widthScale") = particleSystem.getScale().x;
	particleSystemNode.append_attribute("heightScale") = particleSystem.getScale().y;
	particleSystemNode.append_attribute("widthScaleVariance") = particleSystem.getScaleVariance().x;
	particleSystemNode.append_attribute("heightScaleVariance") = particleSystem.getScaleVariance().y;
	particleSystemNode.append_attribute("angle") = particleSystem.getAngle();
	particleSystemNode.append_attribute("angleVariance") = particleSystem.getAngleVariance();
	particleSystemNode.append_attribute("xLinearVelocity") = particleSystem.getLinearVelocity().x;
	particleSystemNode.append_attribute("yLinearVelocity") = particleSystem.getLinearVelocity().y;
	particleSystemNode.append_attribute("xLinearVelocityVariance") = particleSystem.getLinearVelocityVariance().x;
	particleSystemNode.append_attribute("yLinearVelocityVariance") = particleSystem.getLinearVelocityVariance().y;
	particleSystemNode.append_attribute("angularVelocity") = particleSystem.getAngularVelocity();
	particleSystemNode.append_attribute("angularVelocityVariance") = particleSystem.getAngularVelocityVariance();
	particleSystemNode.append_attribute("startRColor") = particleSystem.getStartColor().r;
	particleSystemNode.append_attribute("startGColor") = particleSystem.getStartColor().g;
	particleSystemNode.append_attribute("startBColor") = particleSystem.getStartColor().b;
	particleSystemNode.append_attribute("startRColorVariance") = particleSystem.getStartColorVariance().r;
	particleSystemNode.append_attribute("startGColorVariance") = particleSystem.getStartColorVariance().g;
	particleSystemNode.append_attribute("startBColorVariance") = particleSystem.getStartColorVariance().b;
	particleSystemNode.append_attribute("endRColor") = particleSystem.getEndColor().r;
	particleSystemNode.append_attribute("endGColor") = particleSystem.getEndColor().g;
	particleSystemNode.append_attribute("endBColor") = particleSystem.getEndColor().b;
	particleSystemNode.append_attribute("endRColorVariance") = particleSystem.getEndColorVariance().r;
	particleSystemNode.append_attribute("endGColorVariance") = particleSystem.getEndColorVariance().g;
	particleSystemNode.append_attribute("endBColorVariance") = particleSystem.getEndColorVariance().b;

	doc.save_file(cinder::app::getSaveFilePath().c_str());
}

void ArtScene::load()
{
	pugi::xml_document doc;
	
	if (doc.load_file(cinder::app::getOpenFilePath().c_str()))
	{
		if (const auto particleSystemNode = doc.child("ParticleSystem"))
		{
			if (const auto textureAttribute = particleSystemNode.attribute("texture"))
			{
				texturePath = textureAttribute.as_string();

				particleSystem.setTexture(cinder::gl::Texture2d::create(cinder::loadImage(texturePath)));
			}
			if (const auto emissionRateAttribute = particleSystemNode.attribute("emissionRate"))
			{
				particleSystem.setEmissionRate(emissionRateAttribute.as_float());
			}
			if (const auto totalLifeTimeAttribute = particleSystemNode.attribute("totalLifeTime"))
			{
				particleSystem.setTotalLifeTime(totalLifeTimeAttribute.as_float());
			}
			if (const auto lifeTimeVarianceAttribute = particleSystemNode.attribute("lifeTimeVariance"))
			{
				particleSystem.setLifeTimeVariance(lifeTimeVarianceAttribute.as_float());
			}
			const auto xPositionAttribute = particleSystemNode.attribute("xPosition");
			const auto yPositionAttribute = particleSystemNode.attribute("yPosition");

			if (xPositionAttribute && yPositionAttribute)
			{
				particleSystem.setPosition({ xPositionAttribute.as_float(), yPositionAttribute.as_float() });
			}
		
			const auto xPositionVarianceAttribute = particleSystemNode.attribute("xPositionVariance");
			const auto yPositionVarianceAttribute = particleSystemNode.attribute("yPositionVariance");

			if (xPositionVarianceAttribute && yPositionVarianceAttribute)
			{
				particleSystem.setPositionVariance({ xPositionVarianceAttribute.as_float(), yPositionVarianceAttribute.as_float() });
			}

			const auto widthScaleAttribute = particleSystemNode.attribute("widthScale");	
			const auto heightScaleAttribute = particleSystemNode.attribute("heightScale");

			if (widthScaleAttribute && heightScaleAttribute)
			{
				particleSystem.setScale({ widthScaleAttribute.as_float(), heightScaleAttribute.as_float() });
			}
			
			const auto widthScaleVarianceAttribute = particleSystemNode.attribute("widthScaleVariance");
			const auto heightScaleVarianceAttribute = particleSystemNode.attribute("heightScaleVariance");

			if (widthScaleVarianceAttribute && heightScaleVarianceAttribute)
			{
				particleSystem.setScaleVariance({ widthScaleVarianceAttribute.as_float(), heightScaleVarianceAttribute.as_float() });
			}

			if (const auto angleAttribute = particleSystemNode.attribute("angle"))
			{
				particleSystem.setAngle(angleAttribute.as_float());
			}
			if (const auto angleVarianceAttribute = particleSystemNode.attribute("angleVariance"))
			{
				particleSystem.setAngleVariance(angleVarianceAttribute.as_float());
			}

			const auto xLinearVelocityAttribute = particleSystemNode.attribute("xlinearVelocity");
			const auto yLinearVelocityAttribute = particleSystemNode.attribute("yLinearVelocity");

			if (xLinearVelocityAttribute && yLinearVelocityAttribute)
			{
				particleSystem.setLinearVelocity({ xLinearVelocityAttribute.as_float(), yLinearVelocityAttribute.as_float() });
			}

			const auto xLinearVelocityVarianceAttribute = particleSystemNode.attribute("xLinearVelocityVariance");
			const auto yLinearVelocityVarianceAttribute = particleSystemNode.attribute("yLinearVelocityVariance");

			if (xLinearVelocityVarianceAttribute && yLinearVelocityVarianceAttribute)
			{
				particleSystem.setLinearVelocityVariance({ xLinearVelocityVarianceAttribute.as_float(), yLinearVelocityAttribute.as_float() });
			}
			
			if (const auto angularVelocityAttribute = particleSystemNode.attribute("angularVelocity"))
			{
				particleSystem.setAngularVelocity(angularVelocityAttribute.as_float());
			}
			if (const auto angularVelocityVarianceAttribute = particleSystemNode.attribute("angularVelocityVariance"))
			{
				particleSystem.setAngularVelocityVariance(angularVelocityVarianceAttribute.as_float());
			}

			const auto startRColorAttribute = particleSystemNode.attribute("startRColor");	
			const auto startGColorAttribute = particleSystemNode.attribute("startGColor");	
			const auto startBColorAttribute = particleSystemNode.attribute("startBColor");

			if (startRColorAttribute && startGColorAttribute && startBColorAttribute)
			{
				particleSystem.setStartColor({ startRColorAttribute.as_float(), startGColorAttribute.as_float(), startBColorAttribute.as_float() });
			}
			
			const auto startRColorVarianceAttribute = particleSystemNode.attribute("startRColorVariance");
			const auto startGColorVarianceAttribute = particleSystemNode.attribute("startGColorVariance");
		    const auto startBColorVarianceAttribute = particleSystemNode.attribute("startBColorVariance");

			if (startRColorVarianceAttribute && startGColorVarianceAttribute && startBColorVarianceAttribute)
			{
				particleSystem.setStartColorVariance({ startRColorVarianceAttribute.as_float(), startGColorVarianceAttribute.as_float(), startBColorVarianceAttribute.as_float() });
			}
			
			const auto endRColorAttribute = particleSystemNode.attribute("endRColor");
			const auto endGColorAttribute = particleSystemNode.attribute("endGColor");
			const auto endBColorAttribute = particleSystemNode.attribute("endBColor");

			if (endRColorAttribute && endGColorAttribute && endBColorAttribute)
			{
				particleSystem.setEndColor({ endRColorAttribute.as_float(), endGColorAttribute.as_float(), endBColorAttribute.as_float() });
			}
			
			const auto endRColorVarianceAttribute = particleSystemNode.attribute("endRColorVariance");
			const auto endGColorVarianceAttribute = particleSystemNode.attribute("endGColorVariance");
			const auto endBColorVarianceAttribute = particleSystemNode.attribute("endBColorVariance");

			if (endRColorVarianceAttribute && endGColorVarianceAttribute && endBColorVarianceAttribute)
			{
				particleSystem.setEndColorVariance({ endRColorVarianceAttribute.as_float(), endGColorVarianceAttribute.as_float(), endBColorVarianceAttribute.as_float() });
			}
		}
	}
}

void ArtScene::setTexture()
{
    texturePath = cinder::app::getOpenFilePath();

	if (!texturePath.empty())
	{
		particleSystem.setTexture(cinder::gl::Texture2d::create(cinder::loadImage(texturePath)));
	}
}