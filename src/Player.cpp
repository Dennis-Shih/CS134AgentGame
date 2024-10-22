//
//  Player.cpp
//  CS134PursuitGame
//
//  Created by Dennis Shih on 9/29/24.
//

#include "ofApp.h"
#include "Player.h"

bool Player::inside(glm::vec3 p0) {
    glm::vec3 p = glm::inverse(getTransform()) * glm::vec4(p0, 1);
    glm::vec3 v1 = glm::normalize(verts[0] - p);
    glm::vec3 v2 = glm::normalize(verts[1] - p);
    glm::vec3 v3 = glm::normalize(verts[2] - p);
    float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
    float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
    float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
    
    if (a1 < 0 && a2 < 0 && a3 < 0) return true;
    else return false;
}


Player::Player() {
    
    verts.push_back(glm::vec3(1, 1, 0));
    verts.push_back(glm::vec3(0, -2, 0));
    verts.push_back(glm::vec3(-1, 1, 0));
    
   // scale = glm::vec3(1, 1, 1);
    scale = glm::vec3(1, 1, 1);
    nEnergy = 5;
    pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
    speed = 300.0f;
    mass=1.0f;
    
    damping= 0.99;
    
    knockBackMult=1.25f;
    moveDir = 0;
    rotDir=0;
    rotationSpeed = 0;
    shotFired=false;
}


void Player::draw() {
   
    float sl=sliderScale;
    ofPushMatrix();
    ofMultMatrix(getTransform());
    
    ofFill();
    //ofSetColor(color);
    //ofDrawTriangle(verts[0], verts[1], verts[2]);
    
    if (shapeToggle) {
         ofScale(sl*100, sl*100);
         
         
         ofDrawTriangle(verts[0], verts[1], verts[2]);
         
     } else {
         ofScale(sliderScale, sliderScale );
         
         img.draw(-img.getWidth()/2, -img.getHeight()/2);
     }
    
    
    
    /*
    ofScale(sliderScale, sliderScale);
    img.draw(-img.getWidth()/2, -img.getHeight()/2);
    */
    
    ofPopMatrix();
    
    
    
    
    
}

void Player::update() {
    
    float minX=img.getWidth() / scale.length();
    float maxX=ofGetWindowWidth() - minX;
    float minY=img.getHeight() / scale.length();
    float maxY=ofGetWindowHeight() - minY;
    /*
    if (rotDir<0) {
        //left
        rot-=rotationSpeed;
        //right
    } else if (rotDir>0) rot+=rotationSpeed;
    */
    
    forward= glm::normalize(glm::vec3(sin(glm::radians(-rot)), cos(glm::radians(-rot)), 0));
    force = forward * moveDir * speed;
    //pos -= forward * speed * moveDir;
    
    integrate();
    
    if (pos.x < minX) {
        pos.x += knockBackMult * minX;
    } else if (pos.x > maxX) {
        pos.x -= knockBackMult * minX;
    }
    if (pos.y < minY){
       pos.y += knockBackMult * minY;
    } else if (pos.y > maxY) {
        pos.y -= knockBackMult * minY;
    }
    
}

void Player::integrate(){
    float dt = ofGetLastFrameTime();
    pos-=velocity * dt;
    
    accel=(1/mass) * force;
    velocity+=accel * dt;
    velocity *=damping;
    
    rotationSpeed*=rotDir;
    rot+=rotationSpeed;
    /*
    if (rotDir!=0) {
        rotationSpeed*=rotDir;
        rot+=rotationSpeed;
        
    } else rot+=rotationSpeed;
    */
}

glm::mat4 Player::getTransform() {
    glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
    /*
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation),
                                glm::vec3(0, 0, 1));
     */
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(this->rot),
                                glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(glm::mat4(1.0), this->scale);
    return (trans * rot * scale);
}

void Player::setup() {
    Player();
    if (img.load("images/PlayerSprites/Player1.png")) {
        cout << "image loaded" << endl;
    }
    
    w = img.getWidth();
    h = img.getHeight();
    
    cout << "image width " << w << endl;
    cout << "image height " << h << endl;
    ofColor color = img.getColor(w / 2.0, h / 2.0);
    cout << "pixel color at middle of image " << color << endl;
    ofColor color2 = img.getColor(0, 0);
    cout << "pixel color at edge of image " << color2 << endl;
    ofSetVerticalSync(true);
    
    
    
}

    

void Player:: reset(){
    scale = glm::vec3(1, 1, 1);
    nEnergy = 5;
    pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
    speed = 3.0f;
    rot=0;
    
}
