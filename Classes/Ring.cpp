//
//  Ring.cpp
//  puzzleTest
//
//  Created by Zach Erdmann on 4/17/14.
//
//


#include "Ring.h"

USING_NS_CC;

Ring::Ring(void) {
    setNumPoints(1);
    _currentPoint = 0;
}

Ring::~Ring(void) {
    
}

Ring::Ring(int num){
    setNumPoints(num);
}

void Ring::setNumPoints(int num) {
    _numPoints = num;
    this->randomPoint();
    _angleOfRotation = 360/(num);
    _currentAngle = _angleOfRotation * _currentPoint;
}

int Ring::getNumPoints() {
    return _numPoints;
}

float Ring::getAngle() {
    return  _angleOfRotation * _currentPoint;
;
}

Ring* Ring::ringSpriteWithFileAndNumber(std::string pszFileName, int num) {
    Ring * ring = new Ring();
    if (ring && ring->initWithFile(pszFileName)) {
        ring->autorelease();
        ring->setNumPoints(num);
        return ring;
    }
    CC_SAFE_DELETE(ring);
    return NULL;
}


void Ring::turnWheel(){

    for(int i=0; i<_numPoints; i++)
    {
        if(this->getRotation()> i*_angleOfRotation && this->getRotation() < (i+1) * _angleOfRotation)
        {
            if(this->getRotation() < i * _angleOfRotation + (_angleOfRotation/2))
            {
                _currentPoint = i;
                break;
            }
            else if(this->getRotation() > (i+1) * _angleOfRotation - (_angleOfRotation/2))
            {
                _currentPoint = i+1;
                break;
            }
        }
        
    }
    if (_currentPoint == _numPoints) {
        _currentPoint = 0;
    }
}

void Ring::setRads(int r, int R)
{
    _radius = r;
    _R = R;
}

int Ring::getR() {
    return _R;
}

int Ring::getRadius() {
    return _radius;
}

void Ring::randomPoint(){
    srand(time(NULL));
    this->setcurrentPoint(rand()%_numPoints);
}