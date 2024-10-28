#include "ofApp.h"



//----------------------------------------------------------------------------------
//Agent emitter



//  Add a Sprite to the Sprite System
//
void SpriteList::add(Sprite s) {
	sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteList::remove(int i) {
	sprites.erase(sprites.begin() + i);
}



//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void SpriteList::update() {

	if (sprites.size() == 0) return;
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;
    

    
	//
    /*
	while (s != sprites.end()) {
        
        
        
        //check which sprites have exceeded their lifespan and deletefrom list
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}
    */

	//  Move sprite
	//
	/*
    for (int i = 0; i < sprites.size(); i++) {
		sprites[i].pos += sprites[i].velocity / ofGetFrameRate();
        
	}
    */
}

//  Render all the sprites
//
void SpriteList::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
        
	}
}



Emitter::Emitter() {
	sys = new SpriteList();
	init();
}


void Emitter::init() {
    
    ofSetVerticalSync(true);

    // create an image for sprites being spawned by emitter
    //
    
    if (image.load("images/AgentSprites/Agent.png")) {
        imageLoaded = true;
    }
    else {
        cout << "Can't open image file" << endl;
        //ofExit();
    }
    
    imgs.push_back(ofImage("images/AgentSprites/Agent.png"));
    imgs.push_back(ofImage("images/AgentSprites/Agent1.png"));
    
    

    ofSetBackgroundColor(ofColor::black);
    
    drawable = true;
    setChildImage(imgs[0]);
    //setChildImage(image);
    start();
    
    
	lifespan = 9000;    // default milliseconds
	

	lastSpawned = 0;
    
	rate = 1;    // sprites/sec
	haveChildImage = true;
	haveImage = false;
    lastSpriteImgTime=0;
    
	//velocity = ofVec3f(0, -200, 0);
	drawable = true;
	
}



//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
    
	// draw sprite system
	//
    
	sys->draw();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
    
    if (!started) {
        cout << "not started" << endl;
        return;
    }
    
    
    
     
    
    
	float time = ofGetElapsedTimeMillis();

	if ((time - lastSpawned) > (1000.0 / rate)) {

		// call virtual to spawn a new sprite
		//
        
        //cout << "spawn agent" << endl;
        for (int i = 0;i<nAgents; i++){
            spawnSprite();
        }
        lastSpawned = time;
        
        
        
	}
    
    if (lastSpriteImgTime>=0.1){
        childImage=imgs[1];
        lastSpriteImgTime=0;
    } else childImage=imgs[0];
    
    lastSpriteImgTime+=ofGetLastFrameTime();

	// update sprite list
	//
	if (sys->sprites.size() == 0) return;
	vector<Sprite>::iterator s = sys->sprites.begin();
	vector<Sprite>::iterator tmp;

	// check which sprites have exceed their lifespan or have touched the player and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sys->sprites.end()) {
        if ((s->lifespan != -1 && s->age() > s->lifespan) || s->intersectedParticle || s->intersectedPlayer) {
			//			cout << "deleting sprite: " << s->name << endl;
            
			tmp = sys->sprites.erase(s);
			s = tmp;
		}
		else s++;
	}

    
	for (int i = 0; i < sys->sprites.size(); i++) {
        
   
        sys->sprites[i].setImage(childImage);
        sys->sprites[i].update();
		moveSprite(&sys->sprites[i]);
	}
	
}


void Emitter::moveSprite(Sprite *sprite) {
    sprite->integrate();
    //sprite->pos -= (sprite->velocity * sprite->speed / ofGetFrameRate()) / 4;
   
}



//
void Emitter::spawnSprite() {
	Sprite sprite;
	if (haveChildImage) sprite.setImage(childImage);
	//sprite.velocity = velocity;
	sprite.lifespan = lifespan;
	//sprite.pos = pos;
    sprite.scale = glm::vec3(1,1,1);
    sprite.pos = glm::vec3(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()), 0);
	sprite.birthtime = ofGetElapsedTimeMillis();
    sprite.rot = ofRandom(360);
    sprite.speed = 200;
    sprite.proxRadius=sprite.width/2;
    
    
	sys->add(sprite);
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
	started = false;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(const glm::vec3 v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}

void Emitter::setImage(ofImage img) {
	image = img;
}

void Emitter::setRate(float r) {
	rate = r;
}

void Emitter::setNAgents(float n) {
    nAgents = n;
}
