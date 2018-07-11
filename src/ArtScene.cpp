/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ArtScene.cpp
InversePalindrome.com
*/


#include "ArtScene.hpp"
#include "Conversions.hpp"
#include "SceneManager.hpp"

#include <pugixml.hpp>


ArtScene::ArtScene(SceneManager& sceneManager) :
	Scene(sceneManager),
	controlWindow(cinder::app::App::get()->createWindow(cinder::app::Window::Format().title("Art Creator").resizable(false))),
	particlesToAdd("0"),
	emissionRate("1"),
	totalLifeTime("10"),
	lifeTimeVariance("0"),
	xPosition("0"),
	yPosition("0"),
	xPositionVariance("100"),
	yPositionVariance("100"),
	widthScale("1"),
	heightScale("1"),
	widthScaleVariance(0.f),
	heightScaleVariance(0.f),
	angle("0"),
	angleVariance(0.f),
	xLinearVelocity("0"),
	ylinearVelocity("0"),
	xLinearVelocityVariance("0"),
	yLinearVelocityVariance("0"),
	angularVelocity("0"),
	angularVelocityVariance("0"),
	startColor(cinder::ColorA::white()),
	startColorVariance(cinder::ColorA::white()),
	endColor(cinder::ColorA::white()),
	endColorVariance(cinder::ColorA::white())
{
	auto mainWindow = cinder::app::getWindow();
	mainGui = pretzel::PretzelGui::create("Art");
	mainGui->setVisible(false);

	controlWindow->setSize(mainWindow->getWidth() / 3, mainWindow->getHeight());
	controlWindow->setPos(mainWindow->getPos().x - controlWindow->getWidth(), mainWindow->getPos().y);
	
	controlGui = pretzel::PretzelGui::create("Controls", controlWindow->getWidth(), controlWindow->getHeight(), controlWindow);
	controlGui->setPos({ 0.f, 0.f });
	controlGui->addButton("Load", &ArtScene::load, this);
	controlGui->addButton("Save", &ArtScene::save, this);
	controlGui->addTextField("Particles to Add", &particlesToAdd);
	controlGui->addButton("Add Particles", &ArtScene::addParticles, this);
	controlGui->addButton("Clear Particles", &ArtScene::clearParticles, this);
	controlGui->addButton("Set Texture", &ArtScene::setTexture, this);
	controlGui->addTextField("Emission Rate", &emissionRate);
	controlGui->addTextField("Life Time", &totalLifeTime);
	controlGui->addTextField("Life Time Variance", &lifeTimeVariance);
	controlGui->addTextField("X Position", &xPosition, true);
	controlGui->addTextField("Y Position", &yPosition, true);
	controlGui->addTextField("X Position Variance", &xPositionVariance);
	controlGui->addTextField("Y Position Variance", &yPositionVariance);
	controlGui->addTextField("Width Scale", &widthScale);
	controlGui->addTextField("Height Scale", &heightScale);
	controlGui->addSlider("Width Scale Variance", &widthScaleVariance, 0.f, 0.5f);
	controlGui->addSlider("Height Scale Variance", &heightScaleVariance, 0.f, 0.5f);
	controlGui->addTextField("Angle", &angle);
	controlGui->addSlider("Angle Variance", &angleVariance, 0.f, 180.f);
	controlGui->addTextField("X Linear Velocity", &xLinearVelocity);
	controlGui->addTextField("Y Linear Velocity", &ylinearVelocity);
	controlGui->addTextField("X Linear Velocity Variance", &xLinearVelocityVariance);
	controlGui->addTextField("Y Linear Velocity Variance", &yLinearVelocityVariance);
	controlGui->addTextField("Angular Velocity", &angularVelocity);
	controlGui->addTextField("Angular Velocity Variance", &angularVelocityVariance);
	controlGui->addColorPicker("Start Color", &startColor);
	controlGui->addColorPicker("Start Color Variance", &startColorVariance);
	controlGui->addColorPicker("End Color", &endColor);
	controlGui->addColorPicker("End Color Variance", &endColorVariance);
	
	timer.start();
}

void ArtScene::update()
{
	particleSystem.setEmissionRate(Conversions::stringToFloat(emissionRate));
	particleSystem.setTotalLifeTime(Conversions::stringToFloat(totalLifeTime, 10.f));
	particleSystem.setLifeTimeVariance(Conversions::stringToFloat(lifeTimeVariance));
	particleSystem.setPosition({ Conversions::stringToFloat(xPosition), Conversions::stringToFloat(yPosition) });
	particleSystem.setPositionVariance({ Conversions::stringToFloat(xPositionVariance, 100.f), Conversions::stringToFloat(yPositionVariance, 100.f) });
	particleSystem.setScale({ Conversions::stringToFloat(widthScale, 1.f), Conversions::stringToFloat(heightScale, 1.f) });
	particleSystem.setScaleVariance({ widthScaleVariance, heightScaleVariance });
	particleSystem.setAngle(Conversions::stringToFloat(angle));
	particleSystem.setAngleVariance(angleVariance);
	particleSystem.setLinearVelocity({ Conversions::stringToFloat(xLinearVelocity), Conversions::stringToFloat(ylinearVelocity) });
	particleSystem.setLinearVelocityVariance({ Conversions::stringToFloat(xLinearVelocityVariance), Conversions::stringToFloat(yLinearVelocityVariance) });
	particleSystem.setAngularVelocity(Conversions::stringToFloat(angularVelocity));
	particleSystem.setAngularVelocityVariance(Conversions::stringToFloat(angularVelocityVariance));
	particleSystem.setStartColor(startColor);
	particleSystem.setStartColorVariance(startColorVariance);
	particleSystem.setEndColor(endColor);
	particleSystem.setEndColorVariance(endColorVariance);
	
	particleSystem.update(timer.getSeconds());

	timer.start();
}

void ArtScene::draw()
{
	particleSystem.draw();
	
	controlGui->drawAll();
}

void ArtScene::load()
{
	pugi::xml_document doc;
	
	if (doc.load_file(cinder::app::getOpenFilePath().c_str()))
	{
		if (const auto particleSystemNode = doc.child("ParticleSystem"))
		{
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

void ArtScene::save()
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto particleSystemNode = doc.append_child("ParticleSystem");
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

void ArtScene::addParticles()
{
	particleSystem.addParticles(Conversions::stringToFloat(particlesToAdd));
}

void ArtScene::clearParticles()
{
	particleSystem.clearParticles();
}

void ArtScene::setTexture()
{
	const auto path = cinder::app::getOpenFilePath();

	if (!path.empty())
	{
		particleSystem.setTexture(path);
	}
}
