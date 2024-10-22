

#include "ParticleSystem.h"

void ParticleSystem::add(const Particle &p) {
    particles.push_back(p);
}

void ParticleSystem::addForce(ParticleForce *f) {
    forces.push_back(f);
}

void ParticleSystem::remove(int i) {
    particles.erase(particles.begin() + i);
}

void ParticleSystem::update() {
    // check if empty and just return
    if (particles.size() == 0) return;

    vector<Particle>::iterator p = particles.begin();
    vector<Particle>::iterator tmp;

    // check which particles have exceed their lifespan and delete
    // from list.  When deleting multiple objects from a vector while
    // traversing at the same time, we need to use an iterator.
    //
    while (p != particles.end()) {
        if (p->lifespan != -1 && p->age() > p->lifespan) {
            tmp = particles.erase(p);
            p = tmp;
        }
        else p++;
    }

    // update forces on all particles first
    //
    for (int i = 0; i < particles.size(); i++) {
        for (int k = 0; k < forces.size(); k++) {
            forces[k]->updateForce( &particles[i] );
        }
    }

    // integrate all the particles in the store
    //
    for (int i = 0; i < particles.size(); i++)
        particles[i].integrate();

}

// remove all particlies within "dist" of point
//
int ParticleSystem::removeNear(const ofVec3f & point, float dist) { return 0; }

//  draw the ParticleRay cloud
//
void ParticleSystem::draw() {
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
}




void GravityForce::updateForce(Particle * Particle) {
    //
    // f = mg
    //
    Particle->forces += gravity * Particle->mass;
}

void GravityForce::setForce(float f){
    gravity = ofVec3f(0,f,0);
}

// Turbulence Force Field
//
TurbulenceForce::TurbulenceForce(const ofVec3f &min, const ofVec3f &max) {
    tmin = min;
    tmax = max;
}

void TurbulenceForce::updateForce(Particle * Particle) {
    //
    // We are going to add a little "noise" to a particles
    // forces to achieve a more natual look to the motion
    //
    Particle->forces.x += ofRandom(tmin.x, tmax.x);
    Particle->forces.y += ofRandom(tmin.y, tmax.y);
    
}

void TurbulenceForce::set(const ofVec3f min, const ofVec3f max){
    tmin=min;
    tmax=max;
}


