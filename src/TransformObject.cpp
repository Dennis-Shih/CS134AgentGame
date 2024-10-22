//
//  TransformObject.cpp
//  CS134PursuitGame
//
//  Created by Dennis Shih on 10/21/24.
//

#pragma once
#include "TransformObject.h"

//  Base class for any object that needs a transform.
//
TransformObject::TransformObject() {
    position = ofVec3f(0, 0, 0);
    scale = ofVec3f(1, 1, 1);
    rotation = 0;
}

void TransformObject::setPosition(const glm::vec3 & pos) {
    position = pos;
}
