#include "ofApp.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "Player.h"


//--------------------------------------------------------------
void ofApp::setup(){
    player.setup();
    
    //agent.setup();
    
    em = new Emitter();
    em->pos=glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
    emitters.push_back(em);
   
    
    
    gui.setup();
    
    gui.add(player.sliderScale.setup("Player Scale", 1, 0.1, 2));
    
    gui.add(player.shapeToggle.setup("Shape Toggle", false));
    gui.add(life.setup("Agent Life", 3000, 1, 10000));
    gui.add(pRotationSpeed.setup("Player Rotation Speed (deg/Frame)", 1, 1, 10));
    gui.add(agentRotationSpeed.setup("Agent Rotation Speed (deg/Frame)", 1, 1, 10));
    gui.add(rate.setup("Rate", 1, 1, 10));
    
    gui.add(nEnergyParam.setup("Default Energy Level", player.nEnergy, 1, 10));
    explode.load("audio/explode.wav");
    bgm.load("audio/bgm.wav");
    bgm.setVolume(0.4);
    bgm.setLoop(true);
    bgm.play();
    
    textWndwWidth = 200;
    textWndwHeight = 100;
   
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    if (!isGameRunning) {
        ofClear(0, 0, 0);
        return;
    }
    //player.nEnergy = nEnergyParam;
    player.rotationSpeed=pRotationSpeed;
    player.update();
    
    
    
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->update();
        emitters[em]->setRate(rate);
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
            emitters[em]->sys->sprites[i].intersectedPlayer=intersect;
            
            if (intersect) {
                explode.play();
                cout << intersect << endl;
                
                if (--player.nEnergy <=0){
                    isGameOver=true;
                    isGameRunning=false;
                }
            }
        }
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
            ofDrawBitmapString("Press SPACE to start\nPress Q to exit", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/2 - textWndwHeight/ 4);
            
        } else {
            ofDrawBitmapString("GAME OVER", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/2 - textWndwHeight/ 4);
            ofDrawBitmapString("Press SPACE to restart\nPress Q to exit", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/2 );
            
        }
        return;
    }
    ofSetColor(ofColor::gray);
    ofDrawRectangle(ofGetWindowWidth()/2 - textWndwWidth / 2, ofGetWindowHeight()/10, textWndwWidth, textWndwHeight);
    ofSetColor(ofColor::white);
    string energy = ofToString(player.nEnergy);
    ofDrawBitmapString("Energy levels:", ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/8);
    ofDrawBitmapString(energy, ofGetWindowWidth()/2 - textWndwWidth / 2.5, ofGetWindowHeight()/7);
    ofSetColor(ofColor::white);
    player.draw();
    //use emitter for agents
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->draw();
        
    }
    
    gui.draw();
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
                player.nEnergy=nEnergyParam;
                resetGame();
            }
            isGameRunning=true;
            
            break;
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
        case 'q':
        case 'Q':
            exit();
            break;
        default:
            
            break;
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
        default:
            player.moveDir = 0;
            player.rotDir=0;
            break;
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
    bool inDrag;
    glm::vec3 mousePos = glm::vec3(x, y, 0);
    
    inDrag = player.inside(mousePos);
    if (inDrag) {
        cout << "inside" << endl;
        mousePrevPos = mousePos;
    } else cout << "outside" << endl;
    
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
    
    emitters.clear();
    setup();
}


