


#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() {
    sys = new ParticleSystem();
    createdSys = true;
    init();
}

ParticleEmitter::ParticleEmitter(ParticleSystem *s) {
    if (s == NULL)
    {
        cout << "fatal error: null particle system passed to ParticleEmitter()" << endl;
        ofExit();
    }
    sys = s;
    createdSys = false;
    init();
}

ParticleEmitter::~ParticleEmitter() {

    // deallocate particle system if emitter created one internally
    //
    if (createdSys) delete sys;
}

void ParticleEmitter::init() {
    rate = 1;
    velocity = glm::vec3(0, 0, 0);
    lifespan = 3;
    started = false;
    lastSpawned = 0;
    radius = 1;
    particleRadius = 1;
    visible = true;
    speed = 500;
    type = DirectionalEmitter;
    groupSize = 1;
    pos = position;
}



void ParticleEmitter::draw() {
    //draw particles
    if (visible) {
        switch (type) {
        case DirectionalEmitter:
            //ofDrawSphere(position, radius/10);  // just draw a small sphere for point emitters
            break;
        case SphereEmitter:
        case RadialEmitter:
                
            //ofDrawSphere(position, radius);  // just draw a small sphere as a placeholder
            break;
        default:
            break;
        }
    }
    sys->draw();
}
void ParticleEmitter::start() {
    started = true;
    
    lastSpawned = ofGetElapsedTimeMillis();
    
}

void ParticleEmitter::stop() {
    started = false;
    fired = false;
}
void ParticleEmitter::update() {

    float time = ofGetElapsedTimeMillis();
    if (oneShot && started) {
        if (!fired) {

            // spawn a new particle(s)
            //
            for (int i = 0; i < groupSize; i++)
                spawn(time);

            lastSpawned = time;
        }
        fired = true;
        stop();
    }

    else if (((time - lastSpawned) > (1000.0 / rate)) && started) {

        // spawn a new particle(s)
        //
        for (int i= 0; i < groupSize; i++)
            spawn(time);
    
        lastSpawned = time;
    }

    sys->update();
}

void ParticleEmitter::spawn(float time) {

    Particle particle;

    // set initial velocity and position
    // based on emitter type
    //
    switch (type) {
    case RadialEmitter:
    {
        ofColor col(255,0,0);
        ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
        float speed = velocity.length();
        particle.velocity = dir.getNormalized() * speed;
        particle.position.set(pos);
        particle.forces+=particle.velocity*dir.getNormalized();
        particle.color=col;
        
    }
    break;
    case SphereEmitter:
        break;
    case DirectionalEmitter:
        particle.velocity = velocity;
        particle.position.set(pos);
            particle.damping=1;
        break;
    }

    // other particle attributes
    //
    particle.lifespan = lifespan;
    particle.birthtime = time;
    particle.radius = particleRadius;
    
    // add to system
    //
    sys->add(particle);
}




