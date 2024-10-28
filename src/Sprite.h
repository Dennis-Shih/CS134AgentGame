#pragma once

#include "Shape.h"



// Base class for a Sprite. Can be instantiated on it's own (deafult)
// or subclassed to create a custom sprite.  Includes Shape transformations.
// If the sprite has no image set on it, then a simple triangle will be drawn.
//

class Sprite : public Shape {
public:
	Sprite() {
		// default geometry (triangle) if no image attached.
		//
		verts.push_back(glm::vec3(-20, 20, 0));
		verts.push_back(glm::vec3(20, 20, 0));
		verts.push_back(glm::vec3(0, -20, 0));
	}
	
	
	void draw() {
		if (bShowImage) {
			ofPushMatrix();
			ofSetColor(ofColor::white);
			ofMultMatrix(getTransform());
            
			spriteImage.draw(-spriteImage.getWidth() / 2, -spriteImage.getHeight() / 2.0);
            
			ofPopMatrix();
		}
		else
		{
			ofSetColor(ofColor::yellow);
			ofPushMatrix();
			ofMultMatrix(getTransform());
			ofDrawTriangle(verts[0], verts[1], verts[2]);
			ofPopMatrix();
		}
        /* header for ref
        ofSetColor(0, 255, 0);
        ofDrawLine(pos,pos - velocity * 20);
         */
	}

	float age() {
		return (ofGetElapsedTimeMillis() - birthtime);
	}

	void setImage(ofImage img) {
		spriteImage = img;
		bShowImage = true;
		width = img.getWidth();
		height = img.getHeight();
	}

	virtual bool inside(const glm::vec3 p);
	
    void integrate();
    void update();
	bool insideTriangle(const glm::vec3 p);
    void rotTowardsPlayer(const glm::vec3 p);
    

	void setSelected(bool state) { bSelected = state; }
	void setHighlight(bool state) { bHighlight = state; }
	bool isSelected() { return bSelected; }
	bool isHighlight() { return bHighlight; }
    

	bool bHighlight = false;
	bool bSelected = false;
	bool bShowImage = false;
    //glm::vec3 forward;
    float speed;
    glm::vec3 forward = glm::vec3(0, 0, 0);
	glm::vec3 velocity = glm::vec3(0, 0, 0);
    glm::vec3 accel = glm::vec3(0, 0, 0);
    glm::vec3 force = glm::vec3(0, 0, 0);
    float rotationSpeed = 0.0;
    float rotDir=0;
	float birthtime = 0; // elapsed time in ms
	float lifespan = -3;  //  time in ms
	string name =  "UnammedSprite";
	float width=100;
	float height=100;
    
    float mass=1.0f;
    float damping=0.99f;
    
    
    float proxRadius;
    
    //for erasing when hit
    bool intersectedParticle;
    bool intersectedPlayer;
    
    
	ofImage spriteImage;

	// default verts for polyline shape if no image on sprite
	//
	vector<glm::vec3> verts;
    
};

