#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include <iostream>
#include "Ring.h"

USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
    
private:
    bool _running;
    Ring * _outerRing;
    Ring * _innerRing;
    Ring * _midRing;
    
    Ring * _selectedRing;
    
    Sprite * endMessage;
    Rect bbox;
    
    Size _screenSize;

    Point c;
    Point initial;
    Point last_point;
    Point tap;
    
    
    void resetGame();
    
    virtual void onEnter();
    virtual void onExit();

    
    bool hexCheck(Point p, Ring* r);
    void rotateRing(Ring * ring);
    
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
        
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    virtual bool onTouchBegan(Touch* touch, Event *unused_event);
    virtual void onTouchMoved(Touch* touch, Event *unused_event);
    virtual void onTouchEnded(Touch * touch, Event *unusued_event);
    
    
    virtual void update(float dt);
    

    
};

#endif // __GAMELAYER_H__
