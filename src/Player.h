#pragma once

#include "ofMain.h"
#include "Shape.h"

//
//  Player.h
//  CS134PursuitGame
//
//  Created by Dennis Shih on 9/29/24.
//
class Player : public Shape {
    public:
        Player();
        glm::mat4 getTransform();
        
        glm::vec3 pos = glm::vec3(0, 0, 0);
        
        glm::vec3 scale = glm::vec3(1, 1, 1);
        
        glm::vec3 forward;
        
        int nEnergy;
        float speed;
        float rotationSpeed;
        ofImage img;
        ofxFloatSlider sliderScale;
        ofxToggle shapeToggle;
        
        bool inside(glm::vec3 p);
        void setup();
        void draw();
        void update();
        ofColor color = ofColor::blue;
        vector<glm::vec3> verts;
    
        //for moveDir, 1 = up and -1 = down
        float moveDir;
        //for rotDir, -1 = left and 1 = right
        float rotDir;
        //keep player from going OOB
        float knockBackMult;
};
