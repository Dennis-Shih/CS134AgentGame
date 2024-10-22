//
//  Particle.cpp
//  CS134PursuitGame
//
//  Created by Dennis Shih on 10/21/24.
//
#include "Particle.h"


Particle::Particle() {
    velocity.set(0, 0, 0);
    acceleration.set(0, 0, 0);
    position.set(0, 0, 0);
    forces.set(0, 0, 0);
    lifespan = 5;
    birthtime = 0;
    radius = .1;
    damping = .99;
    mass = 1;
    color = ofColor::aquamarine;
}

void Particle::draw() {
    ofSetColor(color);
    ofDrawSphere(position, radius);
    
}

//particle integrator
void Particle::integrate() {

    
    // interval for this step
    //
    float dt = 1.0 / ofGetFrameRate();

    // update position based on velocity
    //
    position -= (velocity * dt);

    // update acceleration with accumulated paritcles forces
    // remember :  (f = ma) OR (a = 1/m * f)
    //
    ofVec3f accel = acceleration;    // start with any acceleration already on the particle
    accel += (forces * (1.0 / mass));
    velocity += accel * dt;
    cout << velocity << endl;

    // add a little damping for good measure
    //
    velocity *= damping;

    // clear forces on particle (they get re-added each step)
    //
    forces.set(0, 0, 0);
}

//  return age in seconds
//
float Particle::age() {
    return (ofGetElapsedTimeMillis() - birthtime)/1000.0;
}



