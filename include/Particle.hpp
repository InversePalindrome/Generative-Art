/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Particle.hpp
InversePalindrome.com
*/


#pragma once

#include <cinder/Color.h>
#include <cinder/Vector.h>


class Particle
{
public:
	Particle();

	float getTotalLifeTime() const;
	void setTotalLifeTime(float totalLifeTime);

	float getCurrentLifeTime() const;
	void setCurrentLifeTime(float currentLifeTime);

	cinder::vec2 getPosition() const;
	void setPosition(const cinder::vec2& position);

	cinder::vec2 getScale() const;
	void setScale(const cinder::vec2& scale);

	float getAngle() const;
	void setAngle(float angle);

	cinder::vec2 getLinearVelocity() const;
	void setLinearVelocity(const cinder::vec2& linearVelocity);

	float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);

	cinder::ColorA getColor() const;
	void setColor(const cinder::ColorA& color);

	cinder::ColorA getEndColor() const;
	void setEndColor(const cinder::ColorA& endColor);

private:
	float totalLifeTime;
	float currentLifeTime;

	cinder::vec2 position;
	cinder::vec2 scale;
	float angle;

	cinder::vec2 linearVelocity;
	float angularVelocity;

	cinder::ColorA color;
	cinder::ColorA endColor;
};