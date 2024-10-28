#pragma once

#include "ofMain.h"
#include "Particle.h"



class ParticleForce {
public:
    virtual void updateForce(Particle *) = 0;
    bool applyOnce = false;
    bool applied = false;
};

class ParticleSystem {
public:
    void add(const Particle &);
    void addForce(ParticleForce *);
    void remove(int);
    void update();
    int removeNear(const ofVec3f & point, float dist);
    void draw();
    vector<Particle> particles;
    vector<ParticleForce *> forces;
};



// Some convenient built-in forces
//
class GravityForce: public ParticleForce {
    ofVec3f gravity;
public:
    GravityForce(const ofVec3f & gravity);
    void updateForce(Particle *);
    void setForce(float f);
};

class TurbulenceForce : public ParticleForce {
    ofVec3f tmin, tmax;
public:
    TurbulenceForce(const ofVec3f & min, const ofVec3f &max);
    void updateForce(Particle *);
    void set(const ofVec3f min, const ofVec3f max);
};

//NoiseForce
class NoiseForce : public ParticleForce {
    ofVec3f noiseVec;
public:
    NoiseForce(const ofVec3f & noise);
    void updateForce(Particle *);
    void set(const ofVec3f noise);
};

class ImpulseRadialForce : public ParticleForce {
    float magnitude;
    float height;
public:
    ImpulseRadialForce(float magnitude);
    void updateForce(Particle *);
    void set(float val);
    void setHeight(float h);
};

