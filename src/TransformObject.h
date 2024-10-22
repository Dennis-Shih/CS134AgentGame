//
//  TransformObject.h
//  CS134PursuitGame
//
//  Created by Dennis Shih on 10/21/24.
//

#pragma once
#include "ofMain.h"



class TransformObject {
protected:
    TransformObject();
    glm::vec3 position, scale;
    float    rotation;
    bool    bSelected;
    void setPosition(const glm::vec3 &);
};
