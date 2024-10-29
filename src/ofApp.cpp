#include "ofApp.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Player.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    if (bg.load("images/background.png")) {
        cout << "bg loaded" << endl;
    }
    
    player.setup();
    
    
    
    
    em = new Emitter();
    em->pos=glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
    
    
    
    
    
    pem=new ParticleEmitter();
    pem->pos=player.pos;
    
    
   
    radialForce = new ImpulseRadialForce(100.0);
    explEm.setEmitterType(RadialEmitter);
    explEm.sys->addForce(radialForce);
    explEm.setOneShot(true);
    explEm.pos=player.pos;
    
    explEm.setGroupSize(50);
    
    
    gui.setup();
    
    
    gui.add(player.sliderScale.setup("Player Scale", 1, 0.1, 2));
    //change to a general toggle in ofapp that sets a bool in player (same for agent)
    //gui.add(player.shapeToggle.setup("Shape Toggle", false));
    gui.add(shapeToggle.setup("Shape Toggle", false));
    
    gui.add(life.setup("Agent Life", em->lifespan, 500, 10000));
    gui.add(pSpeed.setup("Player Speed", player.speed, 50, 500));
    gui.add(pRotationSpeed.setup("Player Rotation Speed (deg/Frame)", 1, 1, 10));
    gui.add(agentRotationSpeed.setup("Agent Rotation Speed (deg/Frame)", 1, 1, 10));
    gui.add(nAgents.setup("nAgents ", 1, 1, 5));
    gui.add(rate.setup("Rate", 1, 1, 10));
    
    gui.add(nEnergyParam.setup("Default Energy Level", player.nEnergy, 1, 10));
    
    gui.add(levelSlider.setup("Difficulty Level", 1, 1, 3));
    
    
    agentRotDefault=agentRotationSpeed;
    nAgentsDefault=nAgents;
    rateDefault=rate;
    
    
    
    
    player.maxEnergy=nEnergyParam;
    //load sounds
    collide.load("audio/collide.mp3");
    explode.load("audio/explode.wav");
    explode.setVolume(0.5);
    bgm.load("audio/bgm.wav");
    bgm.setVolume(0.2);
    bgm.setLoop(true);
    bgm.play();
    shoot.load("audio/shoot.mp3");
    forAccel.load("audio/forwardaccel.mp3");
    backAccel.load("audio/backwardaccel.mp3");
    shoot.setLoop(false);
    
    
    textWndwWidth = 200;
    textWndwHeight = 200;
   
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    if (!isGameRunning) {
        
        ofClear(0, 0, 0);
        return;
    }
    
    agentRotationSpeed=levelSlider;
    nAgents=levelSlider;
    rate=levelSlider;
    
    timeSeconds=ofGetElapsedTimef();
    //player.nEnergy = nEnergyParam;
    player.shapeMode=shapeToggle;
    player.speed = pSpeed;
    player.rotationSpeed=pRotationSpeed;
    player.update();
    
    //particleray
    pem->pos=player.pos;
    //pem->setVelocity(player.forward * player.speed*2);
    pem->setVelocity(player.forward * pem->speed*2);
    pem->setLifespan(10);
    pem->setOneShot(true);
    pem->update();
    
   
    explEm.setLifespan(5);
    explEm.setVelocity(ofVec3f(10, 10, 0));
    
    explEm.setParticleRadius(15);

    explEm.update();
   
    em->update();
    em->setRate(rate);
    em->setNAgents(nAgents);
    for (int i = 0; i < em->sys->sprites.size(); i++) {
        
        // Get values from sliders and update sprites dynamically
        //
        float lf = life;
        float rs = agentRotationSpeed;
        
        em->sys->sprites[i].bShowImage=!shapeToggle;
        em->setLifespan(lf);
        
        em->sys->sprites[i].rotationSpeed = rs;
        em->sys->sprites[i].rotTowardsPlayer(player.pos);
        
        //check if sprite intersect player
        
        bool collidePlayer =glm::length(glm::vec3(em->sys->sprites[i].pos - player.pos))< (em->sys->sprites[i].proxRadius + player.proxRadius);
        
        
        em->sys->sprites[i].intersectedPlayer=collidePlayer;
        if (collidePlayer) {
            collide.play();
            
            if (--player.nEnergy <=0){
                isGameOver=true;
                isGameRunning=false;
                timeSeconds=ofGetElapsedTimef();
            }
        }
        
        //check if particle intercects agent
        
        for (Particle &p: pem->sys->particles){
            bool collideParticle=em->sys->sprites[i].inside(p.position);
            em->sys->sprites[i].intersectedParticle=collideParticle;
            
            if (collideParticle) {
                p.intersected = true;
                //explosion
                explEm.pos=p.position;
                explEm.start();
                explode.play();
                //gain energy level (unless at max)
                player.gainEn();
                
                break;

            }
        }
    }
    
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (!isGameRunning) {
        //display the game start instructuions
        //ofSetColor(ofColor::gray);
        //ofDrawRectangle(ofGetWindowWidth()/2 - textWndwWidth / 2, ofGetWindowHeight()/2 - textWndwHeight / 2, textWndwWidth, textWndwHeight);
        ofSetColor(ofColor::white);
        if (!isGameOver){
            ofDrawBitmapString("Press SPACE to start\nPress H to hide GUI\nPress Q to exit", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/2 - textWndwHeight/ 4);
            
        } else {
            ofDrawBitmapString("GAME OVER", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/2 - textWndwHeight/ 4);
            ofDrawBitmapString("Time survived: " + ofToString(timeSeconds), ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/3.5);
            
            ofDrawBitmapString("Press SPACE to restart\nPress Q to exit", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/2 );
            
        }
        return;
    }
    ofSetColor(ofColor::white);
    bg.draw(0,0, ofGetWidth(), ofGetHeight());
    
    //ofSetColor(ofColor::gray);
    //ofDrawRectangle(ofGetWindowWidth()/2 - textWndwWidth / 2, ofGetWindowHeight()/10, textWndwWidth, textWndwHeight);
    ofSetColor(ofColor::white);
    string energy = ofToString(player.nEnergy);
    ofDrawBitmapString("Energy levels:", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/8);
    ofDrawBitmapString(energy, ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/7);
    ofDrawBitmapString(" / ", ofGetWindowWidth()/2 - textWndwWidth /3, ofGetWindowHeight()/7);
    float maxEnergy=nEnergyParam;
    ofDrawBitmapString(maxEnergy, ofGetWindowWidth()/2- textWndwWidth /4, ofGetWindowHeight()/7);
    
    ofDrawBitmapString("Time elapsed (s):", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/6);
    ofDrawBitmapString(timeSeconds, ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/5.5);
    ofDrawBitmapString("Framerate:", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/4);
    ofDrawBitmapString(ofGetFrameRate(), ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/3.5);
    
    ofSetColor(ofColor::white);
    
    player.draw();
    
    //use emitter for agents
    //for(int em = 0; em < emitters.size(); em++){
    em->draw();
        
    //}
    pem->draw();
    explEm.draw();
    if (!hideGui){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    bgm.stop();
    ofExit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    switch (key) {
        case OF_KEY_UP:
           
            player.moveDir = 1;
            if (!forAccel.isPlaying()) forAccel.play();
            
            break;
        case OF_KEY_DOWN:
            player.moveDir = -1;
            if (!backAccel.isPlaying()) backAccel.play();
            
            break;
        case OF_KEY_LEFT:
            player.rotDir=-1;
            //player.rot-=pRotationSpeed;
            break;
        case OF_KEY_RIGHT:
            player.rotDir=1;
            //player.rot+=pRotationSpeed;
            break;
        //Spacebar to start game
        case ' ':
            if (isGameOver){
                
                isGameOver = false;
                
                resetGame();
            }
            
             isGameRunning=true;
            
            break;
        case 's':
            if (isGameRunning){
                //shoot particle ray
                //cout << "sdown" << endl;
                pem->start();
                
                //player.shotFired=true;
                shoot.play();
            }
            
             
            break;
        case 'h':
        case 'H':
            hideGui=!hideGui;
            break;
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
        case 'q':
        case 'Q':
            exit();
            break;
            
            /*
        default:
            
            break;
            */
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_UP:
        case OF_KEY_DOWN:
            forAccel.stop();
            backAccel.stop();
            player.moveDir = 0;
            break;
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
            player.rotDir = 0;
            break;
        /*case 's':
            player.shotFired=false;*/
        default:
            break;
            
            /*
        default:
            player.moveDir = 0;
            player.rotDir=0;
            break;
             */
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    /*
    bool inShape;
    glm::vec3 mousePos = glm::vec3(x, y, 0);
    
    inShape = player.inside(mousePos);
    if (inShape) {
        cout << "inside" << endl;
        mousePrevPos = mousePos;
    } else cout << "outside" << endl;
    */
    /*
    if (isGameRunning){
        //shoot particle ray
        
        
        shoot.play();
    }
    */
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::resetGame(){
    ofResetElapsedTimeCounter();
    player.reset();
    //em->sys->e
    player.speed=pSpeed;
    player.nEnergy=nEnergyParam;
    explEm.sys->removeAll();
    //emitters.clear();
    setup();
}





