/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - ParticleSystem.cpp
InversePalindrome.com
*/


#include "ParticleSystem.hpp"
#include "DefaultEmitter.hpp"
#include "LifeTimeAffector.hpp"
#include "ColorGradientAffector.hpp"
#include "LinearVelocityAffector.hpp"
#include "AngularVelocityAffector.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>

#include <pugixml.hpp>


void ParticleSystem::load(const std::string& filename)
{
	pugi::xml_document doc;
	
	if (doc.load_file(filename.c_str()))
	{
		if (const auto particleSystemNode = doc.child("ParticleSystem"))
		{
			for (const auto affectorNode : particleSystemNode.children("Affector"))
			{
				if (const auto affectorTypeAttribute = affectorNode.attribute("type"))
				{
					switch (AffectorType::_from_string(affectorTypeAttribute.as_string()))
					{
					case AffectorType::LifeTime:
						affectors.push_back(std::make_unique<LifeTimeAffector>());
						break;
					case AffectorType::LinearVelocity:
						affectors.push_back(std::make_unique<LinearVelocityAffector>());
						break;
					case AffectorType::AngularVelocity:
						affectors.push_back(std::make_unique<AngularVelocityAffector>());
						break;
					case AffectorType::ColorGradient:
						affectors.push_back(std::make_unique<ColorGradientAffector>());
						break;
					}
				}
			}

			for (const auto emitterNode : particleSystemNode.children("Emitter"))
			{
				if (const auto emitterTypeAttribute = emitterNode.attribute("type"))
				{
					switch (EmitterType::_from_string(emitterTypeAttribute.as_string()))
					{
					case EmitterType::Default:
						DefaultEmitter defaultEmitter;
						defaultEmitter.load(emitterNode);

						emitters.push_back(std::make_unique<DefaultEmitter>());
						break;
					}
				}
			}
		}
	}
}

void ParticleSystem::save(const std::string& filename) const
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto particleSystemNode = doc.append_child("ParticleSystem");

	for (const auto& affector : affectors)
	{
		affector->save(particleSystemNode.append_child("Affector"));
	}
	for (const auto& emitter : emitters)
	{
		emitter->save(particleSystemNode.append_child("Emitter"));
	}

	doc.save_file(filename.c_str());
}

void ParticleSystem::update(float deltaTime)
{
	updateAffectors(deltaTime);
	updateEmitters(deltaTime);

	removeDeadParticles();
}

void ParticleSystem::draw()
{
	for (const auto& particle : particles)
	{
		cinder::gl::pushModelMatrix();

		cinder::gl::translate(particle.getPosition().x, particle.getPosition().y);
		cinder::gl::scale(particle.getScale());
		cinder::gl::rotate(particle.getAngle());
		cinder::gl::color(particle.getColor());

		cinder::gl::draw(texture);
		
		cinder::gl::popModelMatrix();
	}
}

void ParticleSystem::addParticle(const Particle& particle)
{
	particles.push_back(particle);
}

void ParticleSystem::clearParticles()
{
	particles.clear();
}

void ParticleSystem::addAffector(std::unique_ptr<Affector> affector)
{
	affectors.push_back(std::move(affector));
}

void ParticleSystem::clearAffectors()
{
	affectors.clear();
}

const std::vector<std::unique_ptr<Affector>>& ParticleSystem::getAffectors() const
{
	return affectors;
}

void ParticleSystem::addEmitter(std::unique_ptr<Emitter> emitter)
{
	emitters.push_back(std::move(emitter));
}

void ParticleSystem::clearEmitters()
{
	emitters.clear();
}

const std::vector<std::unique_ptr<Emitter>>& ParticleSystem::getEmitters() const
{
	return emitters;
}

void ParticleSystem::setTexture(cinder::gl::Texture2dRef texture)
{
	this->texture = texture;
}

void ParticleSystem::updateAffectors(float deltaTime)
{
	for (auto& particle : particles)
	{
		for (auto& affector : affectors)
		{
			affector->update(particle, deltaTime);
		}
	}
}

void ParticleSystem::updateEmitters(float deltaTime)
{
	for (auto& emitter : emitters)
	{
		emitter->update(*this, deltaTime);
	}
}

void ParticleSystem::removeDeadParticles()
{
	particles.erase(std::remove_if(std::begin(particles), std::end(particles), [](const auto& particle) { return particle.getCurrentLifeTime() >= particle.getTotalLifeTime(); }), std::end(particles));
}