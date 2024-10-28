
#pragma once


#include "TransformObject.h"
#include "ParticleSystem.h"

typedef enum { DirectionalEmitter, RadialEmitter, SphereEmitter } EmitterType;

//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class ParticleEmitter : public TransformObject {
public:
    ParticleEmitter();
    ParticleEmitter(ParticleSystem *s);
    ~ParticleEmitter();
    void init();
    void draw();
    void start();
    void stop();
    void setLifespan(const float life)   { lifespan = life; }
    void setVelocity(const ofVec3f &vel) { velocity = vel; }
    void setRate(const float r) { rate = r; }
    void setParticleRadius(const float r) { particleRadius = r; }
    void setEmitterType(EmitterType t) { type = t; }
    
    void setGroupSize(int s) { groupSize = s; }
    void setOneShot(bool s) { oneShot = s; }
    void update();
    void spawn(float time);
    void spawnParticle();
    void spawnParticle(float damping);
    ParticleSystem *sys;
    float rate;         // per sec
    ofVec3f velocity;
    ofVec3f pos;
    float lifespan;     // sec
    bool started;
    float lastSpawned;  // ms
    float particleRadius;
    float radius;
    float speed;
    bool visible;
    bool createdSys;
    bool oneShot;
    bool fired;
    int groupSize;
    EmitterType type;
};

