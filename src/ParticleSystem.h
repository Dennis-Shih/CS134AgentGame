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
    void removeAll();
    void update();
    int removeNear(const ofVec3f & point, float dist);
    void draw();
    vector<Particle> particles;
    vector<ParticleForce *> forces;
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

