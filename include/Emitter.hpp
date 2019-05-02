/*
Copyright (c) 2018 Inverse Palindrome
GenerativeArt - Emitter.hpp
InversePalindrome.com
*/


#pragma once

#include <cinder/Color.h>
#include <cinder/Vector.h>

#include <pugixml.hpp>

#include <enum.h>


BETTER_ENUM(EmitterType, int, Default);

class ParticleSystem;

class Emitter
{
    friend class ArtScene;

public:
    explicit Emitter(EmitterType emitterType);

    virtual void load(const pugi::xml_node& emitterNode);
    virtual void save(pugi::xml_node& emitterNode) const;
    virtual void update(ParticleSystem& particleSystem, float deltaTime) = 0;

    EmitterType getEmitterType() const;

    float getEmissionRate() const;
    void setEmissionRate(float emissionRate);

    int getTextureIndex() const;
    void setTextureIndex(int textureIndex);

    int getTextureIndexVariance() const;
    void setTextureIndexVariance(int textureIndexVariance);

    float getTotalLifeTime() const;
    void setTotalLifeTime(float totalLifeTime);

    float getLifeTimeVariance() const;
    void setLifeTimeVariance(float lifeTimeVariance);

    cinder::vec2 getPosition() const;
    void setPosition(const cinder::vec2& position);

    cinder::vec2 getPositionVariance() const;
    void setPositionVariance(const cinder::vec2& positionVariance);

    cinder::vec2 getScale() const;
    void setScale(const cinder::vec2& scale);

    cinder::vec2 getScaleVariance() const;
    void setScaleVariance(const cinder::vec2& scaleVariance);

    float getAngle() const;
    void setAngle(float angle);

    float getAngleVariance() const;
    void setAngleVariance(float angleVariance);

    cinder::vec2 getLinearVelocity() const;
    void setLinearVelocity(const cinder::vec2& linearVelocity);

    cinder::vec2 getLinearVelocityVariance() const;
    void setLinearVelocityVariance(const cinder::vec2& linearVelocityVariance);

    float getAngularVelocity() const;
    void setAngularVelocity(float angularVelocity);

    float getAngularVelocityVariance() const;
    void setAngularVelocityVariance(float angularVelocityVariance);

    cinder::ColorA getStartColor() const;
    void setStartColor(const cinder::ColorA& startColor);

    cinder::ColorA getStartColorVariance() const;
    void setStartColorVariance(const cinder::ColorA& startColorVariance);

    cinder::ColorA getEndColor() const;
    void setEndColor(const cinder::ColorA& endColor);

    cinder::ColorA getEndColorVariance() const;
    void setEndColorVariance(const cinder::ColorA& endColorVariance);

private:
    EmitterType emitterType;

    float emissionRate;

    int textureIndex;
    int textureIndexVariance;

    float totalLifeTime;
    float lifeTimeVariance;

    cinder::vec2 position;
    cinder::vec2 positionVariance;

    cinder::vec2 scale;
    cinder::vec2 scaleVariance;

    float angle;
    float angleVariance;

    cinder::vec2 linearVelocity;
    cinder::vec2 linearVelocityVariance;

    float angularVelocity;
    float angularVelocityVariance;

    cinder::ColorA startColor;
    cinder::ColorA startColorVariance;

    cinder::ColorA endColor;
    cinder::ColorA endColorVariance;
};