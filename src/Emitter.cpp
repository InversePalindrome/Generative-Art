/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Emitter.cpp
InversePalindrome.com
*/


#include "Emitter.hpp"


Emitter::Emitter(EmitterType emitterType) :
	emitterType(emitterType),
	emissionRate(5.f),
	totalLifeTime(100.f),
	lifeTimeVariance(0.f),
	position(0.f, 0.f),
	positionVariance(400.f, 400.f),
	scale(1.f, 1.f),
	scaleVariance(0.f, 0.f),
	angle(0.f),
	angleVariance(0.f),
	linearVelocity(0.f, 0.f),
	linearVelocityVariance(0.f, 0.f),
	angularVelocity(0.f),
	angularVelocityVariance(0.f),
	startColor(cinder::ColorA::white()),
	startColorVariance(cinder::ColorA::white()),
	endColor(cinder::ColorA::white()),
	endColorVariance(cinder::ColorA::white())
{
}

void Emitter::load(const pugi::xml_node& emitterNode)
{
	if (const auto emissionRateAttribute = emitterNode.attribute("emissionRate"))
	{
		setEmissionRate(emissionRateAttribute.as_float());
	}
	if (const auto totalLifeTimeAttribute = emitterNode.attribute("totalLifeTime"))
	{
		setTotalLifeTime(totalLifeTimeAttribute.as_float());
	}
	if (const auto lifeTimeVarianceAttribute = emitterNode.attribute("lifeTimeVariance"))
	{
		setLifeTimeVariance(lifeTimeVarianceAttribute.as_float());
	}
	const auto xPositionAttribute = emitterNode.attribute("xPosition");
	const auto yPositionAttribute = emitterNode.attribute("yPosition");

	if (xPositionAttribute && yPositionAttribute)
	{
		setPosition({ xPositionAttribute.as_float(), yPositionAttribute.as_float() });
	}

	const auto xPositionVarianceAttribute = emitterNode.attribute("xPositionVariance");
	const auto yPositionVarianceAttribute = emitterNode.attribute("yPositionVariance");

	if (xPositionVarianceAttribute && yPositionVarianceAttribute)
	{
		setPositionVariance({ xPositionVarianceAttribute.as_float(), yPositionVarianceAttribute.as_float() });
	}

	const auto widthScaleAttribute = emitterNode.attribute("widthScale");
	const auto heightScaleAttribute = emitterNode.attribute("heightScale");

	if (widthScaleAttribute && heightScaleAttribute)
	{
		setScale({ widthScaleAttribute.as_float(), heightScaleAttribute.as_float() });
	}

	const auto widthScaleVarianceAttribute = emitterNode.attribute("widthScaleVariance");
	const auto heightScaleVarianceAttribute = emitterNode.attribute("heightScaleVariance");

	if (widthScaleVarianceAttribute && heightScaleVarianceAttribute)
	{
		setScaleVariance({ widthScaleVarianceAttribute.as_float(), heightScaleVarianceAttribute.as_float() });
	}

	if (const auto angleAttribute = emitterNode.attribute("angle"))
	{
		setAngle(angleAttribute.as_float());
	}
	if (const auto angleVarianceAttribute = emitterNode.attribute("angleVariance"))
	{
		setAngleVariance(angleVarianceAttribute.as_float());
	}

	const auto xLinearVelocityAttribute = emitterNode.attribute("xlinearVelocity");
	const auto yLinearVelocityAttribute = emitterNode.attribute("yLinearVelocity");

	if (xLinearVelocityAttribute && yLinearVelocityAttribute)
	{
		setLinearVelocity({ xLinearVelocityAttribute.as_float(), yLinearVelocityAttribute.as_float() });
	}

	const auto xLinearVelocityVarianceAttribute = emitterNode.attribute("xLinearVelocityVariance");
	const auto yLinearVelocityVarianceAttribute = emitterNode.attribute("yLinearVelocityVariance");

	if (xLinearVelocityVarianceAttribute && yLinearVelocityVarianceAttribute)
	{
		setLinearVelocityVariance({ xLinearVelocityVarianceAttribute.as_float(), yLinearVelocityAttribute.as_float() });
	}

	if (const auto angularVelocityAttribute = emitterNode.attribute("angularVelocity"))
	{
		setAngularVelocity(angularVelocityAttribute.as_float());
	}
	if (const auto angularVelocityVarianceAttribute = emitterNode.attribute("angularVelocityVariance"))
	{
		setAngularVelocityVariance(angularVelocityVarianceAttribute.as_float());
	}

	const auto startRColorAttribute = emitterNode.attribute("startRColor");
	const auto startGColorAttribute = emitterNode.attribute("startGColor");
	const auto startBColorAttribute = emitterNode.attribute("startBColor");

	if (startRColorAttribute && startGColorAttribute && startBColorAttribute)
	{
		setStartColor({ startRColorAttribute.as_float(), startGColorAttribute.as_float(), startBColorAttribute.as_float() });
	}

	const auto startRColorVarianceAttribute = emitterNode.attribute("startRColorVariance");
	const auto startGColorVarianceAttribute = emitterNode.attribute("startGColorVariance");
	const auto startBColorVarianceAttribute = emitterNode.attribute("startBColorVariance");

	if (startRColorVarianceAttribute && startGColorVarianceAttribute && startBColorVarianceAttribute)
	{
		setStartColorVariance({ startRColorVarianceAttribute.as_float(), startGColorVarianceAttribute.as_float(), startBColorVarianceAttribute.as_float() });
	}

	const auto endRColorAttribute = emitterNode.attribute("endRColor");
	const auto endGColorAttribute = emitterNode.attribute("endGColor");
	const auto endBColorAttribute = emitterNode.attribute("endBColor");

	if (endRColorAttribute && endGColorAttribute && endBColorAttribute)
	{
		setEndColor({ endRColorAttribute.as_float(), endGColorAttribute.as_float(), endBColorAttribute.as_float() });
	}

	const auto endRColorVarianceAttribute = emitterNode.attribute("endRColorVariance");
	const auto endGColorVarianceAttribute = emitterNode.attribute("endGColorVariance");
	const auto endBColorVarianceAttribute = emitterNode.attribute("endBColorVariance");

	if (endRColorVarianceAttribute && endGColorVarianceAttribute && endBColorVarianceAttribute)
	{
		setEndColorVariance({ endRColorVarianceAttribute.as_float(), endGColorVarianceAttribute.as_float(), endBColorVarianceAttribute.as_float() });
	}
}

void Emitter::save(pugi::xml_node& emitterNode) const
{
	emitterNode.append_attribute("type") = emitterType._to_string();
	emitterNode.append_attribute("emissionRate") = emissionRate;
	emitterNode.append_attribute("totalLifeTime") = totalLifeTime;;
	emitterNode.append_attribute("xPosition") = position.x;
	emitterNode.append_attribute("yPosition") = position.y;
	emitterNode.append_attribute("xPositionVariance") = positionVariance.x;
	emitterNode.append_attribute("yPositionVariance") = positionVariance.y;
	emitterNode.append_attribute("widthScale") = scale.x;
	emitterNode.append_attribute("heightScale") = scale.y;
	emitterNode.append_attribute("widthScaleVariance") = scaleVariance.x;
	emitterNode.append_attribute("heightScaleVariance") = scaleVariance.y;
	emitterNode.append_attribute("angle") = angle;
	emitterNode.append_attribute("angleVariance") = angleVariance;
	emitterNode.append_attribute("xLinearVelocity") = linearVelocity.x;
	emitterNode.append_attribute("yLinearVelocity") = linearVelocity.y;
	emitterNode.append_attribute("xLinearVelocityVariance") = linearVelocityVariance.x;
	emitterNode.append_attribute("yLinearVelocityVariance") = linearVelocityVariance.y;
	emitterNode.append_attribute("angularVelocity") = angularVelocity;
	emitterNode.append_attribute("angularVelocityVariance")= angularVelocityVariance;
	emitterNode.append_attribute("startRColor") = startColor.r;
	emitterNode.append_attribute("startGColor") = startColor.g;
	emitterNode.append_attribute("startBColor") = startColor.b;
	emitterNode.append_attribute("startRColorVariance") = startColorVariance.r;
	emitterNode.append_attribute("startGColorVariance") = startColorVariance.g;
	emitterNode.append_attribute("startBColorVariance") = startColorVariance.b;
	emitterNode.append_attribute("endRColor") = endColor.r;
	emitterNode.append_attribute("endGColor") = endColor.g;
	emitterNode.append_attribute("endBColor") = endColor.b;
	emitterNode.append_attribute("endRColorVariance") = endColorVariance.r;
	emitterNode.append_attribute("endGColorVariance") = endColorVariance.g;
	emitterNode.append_attribute("endBColorVariance") = endColorVariance.b;
}

EmitterType Emitter::getEmitterType() const
{
	return emitterType;
}

float Emitter::getEmissionRate() const
{
	return emissionRate;
}

void Emitter::setEmissionRate(float emissionRate)
{
	this->emissionRate = emissionRate;
}

float Emitter::getTotalLifeTime() const
{
	return totalLifeTime;
}

void Emitter::setTotalLifeTime(float totalLifeTime)
{
	this->totalLifeTime = totalLifeTime;
}

float Emitter::getLifeTimeVariance() const
{
	return lifeTimeVariance;
}

void Emitter::setLifeTimeVariance(float lifeTimeVariance)
{
	this->lifeTimeVariance = lifeTimeVariance;
}

cinder::vec2 Emitter::getPosition() const
{
	return position;
}

void Emitter::setPosition(const cinder::vec2& pPosition)
{
	this->position = position;
}

cinder::vec2 Emitter::getPositionVariance() const
{
	return positionVariance;
}

void Emitter::setPositionVariance(const cinder::vec2& positionVariance)
{
	this->positionVariance = positionVariance;
}

cinder::vec2 Emitter::getScale() const
{
	return scale;
}

void Emitter::setScale(const cinder::vec2& scale)
{
	this->scale = scale;
}

cinder::vec2 Emitter::getScaleVariance() const
{
	return scaleVariance;
}

void Emitter::setScaleVariance(const cinder::vec2& scaleVariance)
{
	this->scaleVariance = scaleVariance;
}

float Emitter::getAngle() const
{
	return angle;
}

void Emitter::setAngle(float angle)
{
	this->angle = angle;
}

float Emitter::getAngleVariance() const
{
	return angleVariance;
}

void Emitter::setAngleVariance(float angleVariance)
{
	this->angleVariance = angleVariance;
}

cinder::vec2 Emitter::getLinearVelocity() const
{
	return linearVelocity;
}

void Emitter::setLinearVelocity(const cinder::vec2& linearVelocity)
{
	this->linearVelocity = linearVelocity;
}

cinder::vec2 Emitter::getLinearVelocityVariance() const
{
	return linearVelocityVariance;
}

void Emitter::setLinearVelocityVariance(const cinder::vec2& linearVelocityVariance)
{
	this->linearVelocityVariance = linearVelocityVariance;
}

float Emitter::getAngularVelocity() const
{
	return angularVelocity;
}

void Emitter::setAngularVelocity(float angularVelocity)
{
	this->angularVelocity = angularVelocity;
}

float Emitter::getAngularVelocityVariance() const
{
	return angularVelocityVariance;
}

void Emitter::setAngularVelocityVariance(float angularVelocityVariance)
{
	this->angularVelocityVariance = angularVelocityVariance;
}

cinder::ColorA Emitter::getStartColor() const
{
	return startColor;
}

void Emitter::setStartColor(const cinder::ColorA& startColor)
{
	this->startColor = startColor;
}

cinder::ColorA Emitter::getStartColorVariance() const
{
	return startColorVariance;
}

void Emitter::setStartColorVariance(const cinder::ColorA& startColorVariance)
{
	this->startColorVariance = startColorVariance;
}

cinder::ColorA Emitter::getEndColor() const
{
	return endColor;
}

void Emitter::setEndColor(const cinder::ColorA& endColor)
{
	this->endColor = endColor;
}

cinder::ColorA Emitter::getEndColorVariance() const
{
	return endColorVariance;
}

void Emitter::setEndColorVariance(const cinder::ColorA& endColorVariance)
{
	this->endColorVariance = endColorVariance;
}