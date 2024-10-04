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
    em = new Emitter();
    em->pos=glm::vec3(ofGetWindowWidth() / 4.0, ofGetWindowHeight() / 2.0, 0);
    emitters.push_back(em);
    
    
    gui.setup();
    //initialize scale to 100
    gui.add(player.sliderScale.setup("Scale", 1, 0.1, 2));
    
    gui.add(player.shapeToggle.setup("Shape Toggle", false));
    gui.add(scale.setup("Scale", 1, .05, 1.0));
    gui.add(rotationSpeed.setup("Rotation Speed (deg/Frame)", 0, 0, 10));
    
     
}


//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    for(int em = 0; em < emitters.size(); em++){
        emitters[em]->update();
        //emitters[em]->rot;
        //emitters[em]->sys->sprites[em].rotTowardsPlayer(player.pos);
        
        for (int i = 0; i < emitters[em]->sys->sprites.size(); i++) {

            // Get values from sliders and update sprites dynamically
            //
            float sc = scale;
            float rs = rotationSpeed;
            
                
            emitters[em]->sys->sprites[i].scale = glm::vec3(sc, sc, sc);
                
            
            emitters[em]->sys->sprites[i].rotationSpeed = rs;
            emitters[em]->sys->sprites[i].rotTowardsPlayer(player.pos);
           
            cout << emitters[em]->sys->sprites[i].scale << endl;
            
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
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

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    float minX=player.img.getWidth();
    float maxX=ofGetWindowWidth();
    float minY=player.img.getHeight();
    float maxY=ofGetWindowHeight();
    
    float knockBackMult=1.25f;
    
    switch (key) {
        case OF_KEY_UP:
            
            cout << "px" << player.pos.x << endl;
            cout << "x > minx" << (player.pos.x > minX) << endl;
            player.pos -= player.forward * player.speed;
            //kick player back if out of bounds, otherwise move normally
            if (player.pos.x < minX) {
                player.pos.x += knockBackMult * player.speed;
            } else if (player.pos.x > maxX) {
                player.pos.x -= knockBackMult * player.speed;
            }
            if (player.pos.y < minY || player.pos.y > maxY){
                player.pos.y += knockBackMult * player.speed;
            } else if (player.pos.y > maxY) {
                player.pos.y -= knockBackMult * player.speed;
            }
            
            break;
        case OF_KEY_DOWN:
            player.pos += player.forward * player.speed;
            if (player.pos.x < minX) {
                player.pos.x -= knockBackMult * player.speed;
            } else if (player.pos.x > maxX) {
                player.pos.x += knockBackMult * player.speed;
            }
            if (player.pos.y < minY || player.pos.y > maxY){
                player.pos.y -= knockBackMult * player.speed;
            } else if (player.pos.y > maxY) {
                player.pos.y += knockBackMult * player.speed;
            }
            
            break;
        case OF_KEY_LEFT:
            player.rotation-=5;
            break;
        case OF_KEY_RIGHT:
            player.rotation+=5;
            break;
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
