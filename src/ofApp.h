#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Player.h"
#include "Emitter.h"



class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
        ofxPanel gui;
        
        vector<Emitter*> emitters;
        Emitter* em = NULL;
    
        Player player;
        ofxFloatSlider scale;
        ofxFloatSlider life;
        ofxFloatSlider pRotationSpeed;
        ofxFloatSlider agentRotationSpeed;
        ofxFloatSlider rate;
        ofxIntField nEnergyParam;
    
        glm::vec3 mousePrevPos;
        //true when game started, false on title/game over until space pressed
        bool isGameRunning;
        bool isGameOver;
        ofSoundPlayer bgm;
        ofSoundPlayer explode;
        ofSoundStream stream;
    
        float textWndwWidth;
        float textWndwHeight;
    
        void resetGame();
		
};
