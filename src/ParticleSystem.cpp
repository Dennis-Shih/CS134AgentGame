

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
void ParticleSystem::removeAll() {
    particles.erase(particles.begin(), particles.end());
    
}

void ParticleSystem::update() {
    // check if empty and just return
    if (particles.size() == 0) return;

    vector<Particle>::iterator p = particles.begin();
    vector<Particle>::iterator tmp;

    // Delete particle if lifespan exceeded or if it has intersected an agent.
    //
    while (p != particles.end()) {
        if ((p->lifespan != -1 && p->age() > p->lifespan) || p->intersected) {
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


ImpulseRadialForce::ImpulseRadialForce(float magnitude) {
    this->magnitude = magnitude;
    applyOnce = true;
    height=1;
}

void ImpulseRadialForce::updateForce(Particle * particle) {

    // we basically create a random direction for each particle
    // the force is only added once after it is triggered.
    //
    ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-height, height), ofRandom(-1, 1));
    particle->forces += dir.getNormalized() * magnitude;
}
void ImpulseRadialForce::set(float f){
    magnitude=f;
}
void ImpulseRadialForce::setHeight(float h){
    height=h;
}


