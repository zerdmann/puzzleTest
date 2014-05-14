//
//  Ring.h
//  puzzleTest
//
//  Created by Zach Erdmann on 4/17/14.
//
//

#ifndef __puzzleTest__Ring__
#define __puzzleTest__Ring__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class Ring : public Sprite {
public:
    CC_SYNTHESIZE(int, _currentPoint, currentPoint);
    
    
    Ring(void);
    ~Ring(void);
    Ring(int NumPoints);
    
    void setNumPoints(int num);
    int getNumPoints();
    float getAngle();
    
    void setRads(int r, int R);
    int getR();
    int getRadius();
    
    void turnWheel();
    void randomPoint();
    
    static Ring* ringSpriteWithFileAndNumber(std::string pszFileName, int num);

private:
    int _nextPoint;
    float _angleOfRotation;
    float _currentAngle;
    int _numPoints;
    
    int _radius;
    int _R;
    
    
};


#endif /* defined(__puzzleTest__Ring__) */
