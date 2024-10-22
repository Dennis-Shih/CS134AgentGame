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
    
    
    //agent.setup();
    
    em = new Emitter();
    em->pos=glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
    emitters.push_back(em);
    
    pem=new ParticleEmitter();
    pem->pos=player.pos;
    pem->start();
   
    
    
    gui.setup();
    
    gui.add(player.sliderScale.setup("Player Scale", 1, 0.1, 2));
    gui.add(player.shapeToggle.setup("Shape Toggle", false));
    
    
    gui.add(life.setup("Agent Life", emitters[0]->lifespan, 500, 10000));
    gui.add(pSpeed.setup("Player Speed", player.speed, 50, 500));
    gui.add(pRotationSpeed.setup("Player Rotation Speed (deg/Frame)", 1, 1, 10));
    gui.add(agentRotationSpeed.setup("Agent Rotation Speed (deg/Frame)", 1, 1, 10));
    gui.add(nAgents.setup("nAgents ", 1, 1, 5));
    gui.add(rate.setup("Rate", 1, 1, 10));
    
    gui.add(nEnergyParam.setup("Default Energy Level", player.nEnergy, 1, 10));
    
    
    explode.load("audio/explode.wav");
    bgm.load("audio/bgm.wav");
    bgm.setVolume(0.2);
    bgm.setLoop(true);
    bgm.play();
    shoot.load("audio/shoot.mp3");
    shoot.setVolume(1.2);
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
    timeSeconds=ofGetElapsedTimef();
    //player.nEnergy = nEnergyParam;
    player.speed = pSpeed;
    player.rotationSpeed=pRotationSpeed;
    player.update();
    
    
    
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->update();
        emitters[em]->setRate(rate);
        emitters[em]->setNAgents(nAgents);
        //emitters[em]->rot;
        //emitters[em]->sys->sprites[em].rotTowardsPlayer(player.pos);
        
        for (int i = 0; i < emitters[em]->sys->sprites.size(); i++) {
            
            // Get values from sliders and update sprites dynamically
            //
            float lf = life;
            float rs = agentRotationSpeed;
            
            
            emitters[em]->lifespan = lf;
            
            emitters[em]->sys->sprites[i].rotationSpeed = rs;
            emitters[em]->sys->sprites[i].rotTowardsPlayer(player.pos);
            
            //check if sprite intersect player
            bool intersect=emitters[em]->sys->sprites[i].insideTriangle(player.pos);
            //bool intersect=player.inside(emitters[em]->sys->sprites[i].pos);
            emitters[em]->sys->sprites[i].intersectedPlayer=intersect;
            
            if (intersect) {
                explode.play();
                
                
                if (--player.nEnergy <=0){
                    isGameOver=true;
                    isGameRunning=false;
                    timeSeconds=ofGetElapsedTimef();
                }
            }
        }
    }
    
    //particleray
    pem->pos=player.pos;
    pem->setVelocity(player.forward * player.speed*2);
    
    pem->setLifespan(10);
    pem->update();
    
    if (player.shotFired){
        pem->spawnParticle();
        player.shotFired=!player.shotFired;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (!isGameRunning) {
        //display the game start instructuions
        ofSetColor(ofColor::gray);
        ofDrawRectangle(ofGetWindowWidth()/2 - textWndwWidth / 2, ofGetWindowHeight()/2 - textWndwHeight / 2, textWndwWidth, textWndwHeight);
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
    
    ofSetColor(ofColor::gray);
    ofDrawRectangle(ofGetWindowWidth()/2 - textWndwWidth / 2, ofGetWindowHeight()/10, textWndwWidth, textWndwHeight);
    ofSetColor(ofColor::white);
    string energy = ofToString(player.nEnergy);
    ofDrawBitmapString("Energy levels:", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/8);
    ofDrawBitmapString(energy, ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/7);
    ofDrawBitmapString("Time elapsed (s):", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/6);
    ofDrawBitmapString(timeSeconds, ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/5.5);
    ofDrawBitmapString("Framerate:", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/4);
    ofDrawBitmapString(ofGetFrameRate(), ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/3.5);
    
    ofSetColor(ofColor::white);
    
    player.draw();
    //use emitter for agents
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->draw();
        
    }
    pem->draw();
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
        
            
            break;
        case OF_KEY_DOWN:
            player.moveDir = -1;
            
            
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
            
            /*
            if (isGameRunning){
                //shoot particle ray
                
                
                shoot.play();
            }
            
            else*/ isGameRunning=true;
            
            break;
        case 's':
            
            if (isGameRunning && !player.shotFired){
                //shoot particle ray
                //cout << "sdown" << endl;
                player.shotFired=true;
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
    
    player.speed=pSpeed;
    player.nEnergy=nEnergyParam;
    
    emitters.clear();
    setup();
}


