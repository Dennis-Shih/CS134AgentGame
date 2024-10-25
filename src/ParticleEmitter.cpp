


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
    //pos = position;
}



void ParticleEmitter::draw() {
    //draw particles
    sys->draw();
}
void ParticleEmitter::start() {
    started = true;
    lastSpawned = ofGetElapsedTimeMillis();
}

void ParticleEmitter::stop() {
    started = false;
}
void ParticleEmitter::update() {
    if (!started) return;

    float time = ofGetElapsedTimeMillis();
    
    
    
    /*
    Particle particle;
    
    
    particle.position = pos;
    cout << position << endl;
    */
    
    // other particle attributes
    //
    /*
    particle.lifespan = lifespan;
    particle.birthtime = time;
    particle.radius = particleRadius;
    particle.velocity=velocity;
    */
    // add to system
    //
    /*
    sys->add(particle);
    lastSpawned = time;
    */

    sys->update();
}
void ParticleEmitter::spawnParticle(float damping) {
    

    float time = ofGetElapsedTimeMillis();
    
    
    // spawn a new particle
    //
    Particle particle;
    
    
    particle.position = pos;
    
    
    // other particle attributes
    //
    particle.lifespan = lifespan;
    particle.birthtime = time;
    particle.radius = particleRadius;
    particle.velocity=velocity;
    particle.damping=damping;
    // add to system
    //
    
    sys->add(particle);
    lastSpawned = time;
    
}
void ParticleEmitter::spawnParticle() {
    

    float time = ofGetElapsedTimeMillis();
    
    
    // spawn a new particle
    //
    Particle particle;
    
    
    particle.position = pos;
    
    
    // other particle attributes
    //
    particle.lifespan = lifespan;
    particle.birthtime = time;
    particle.radius = particleRadius;
    particle.velocity=velocity;
    
    // add to system
    //
    
    sys->add(particle);
    lastSpawned = time;
    
}


