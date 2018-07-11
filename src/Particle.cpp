/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Particle.cpp
InversePalindrome.com
*/


#include "Particle.hpp"


Particle::Particle() :
	totalLifeTime(100.f),
	currentLifeTime(0.f),
	position(0.f, 0.f),
	scale(1.f, 1.f),
	angle(0.f),
	linearVelocity(0.f, 0.f),
	angularVelocity(0.f),
	color(cinder::ColorA::white()),
	endColor(cinder::ColorA::white())
{
}

float Particle::getTotalLifeTime() const
{
	return totalLifeTime;
}

void Particle::setTotalLifeTime(float totalLifeTime)
{
	this->totalLifeTime = totalLifeTime;
}

float Particle::getCurrentLifeTime() const
{
	return currentLifeTime;
}

void Particle::setCurrentLifeTime(float currentLifeTime)
{
	this->currentLifeTime = currentLifeTime;
}

cinder::vec2 Particle::getPosition() const
{
	return position;
}

void Particle::setPosition(const cinder::vec2& position)
{
	this->position = position;
}

cinder::vec2 Particle::getScale() const
{
	return scale;
}

void Particle::setScale(const cinder::vec2& scale)
{
	this->scale = scale;
}

float Particle::getAngle() const
{
	return angle;
}

void Particle::setAngle(float angle)
{
	this->angle = angle;
}

cinder::vec2 Particle::getLinearVelocity() const
{
	return linearVelocity;
}

void Particle::setLinearVelocity(const cinder::vec2& linearVelocity)
{
	this->linearVelocity = linearVelocity;
}

float Particle::getAngularVelocity() const
{
	return angularVelocity;
}

void Particle::setAngularVelocity(float angularVelocity)
{
	this->angularVelocity = angularVelocity;
}

cinder::ColorA Particle::getColor() const
{
	return color;
}

void Particle::setColor(const cinder::ColorA& color)
{
	this->color = color;
}

cinder::ColorA Particle::getEndColor() const
{
	return endColor;
}

void Particle::setEndColor(const cinder::ColorA& endColor)
{
	this->endColor = endColor;
}