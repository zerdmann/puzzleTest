#include "GameLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/**
 
 TO DO:
 Move Victory Check to seperate Method
 Move Circle Rotate to new method
 Move
 Abstract out Puzzle Class Logic
 
 Track previous direction travelled, use that to infer next direction
 
 
 **/

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    
    _screenSize = Director::getInstance()->getWinSize();
    
    
    //INITIALIZE SPRITES
    Sprite * bg = Sprite::create("bg.png");
    bg->setPosition(Point(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    this->addChild(bg);
    
    _outerRing = Ring::ringSpriteWithFileAndNumber("outer_wheel.png", 5);
    _outerRing->setPosition(Point(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _outerRing->setRotation(_outerRing->getAngle());
    _outerRing->setRads(308, 356);

    
    _midRing = Ring::ringSpriteWithFileAndNumber("mid_wheel.png", 6);
    _midRing->setPosition(Point(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _midRing->setRotation(_midRing->getAngle());
    _midRing->setRads(213, 266);


    _innerRing = Ring::ringSpriteWithFileAndNumber("inner_wheel.png",4);
    _innerRing->setPosition(Point(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _innerRing->setRotation(_innerRing->getAngle());
    _innerRing->setRads(113, 150);
    this->addChild(_innerRing);
    this->addChild(_midRing);
    this->addChild(_outerRing);
    
    //C is Center Point of Puzzle Ring
    c = Point(_screenSize.width * 0.5f,_screenSize.height * 0.5f);

    //BBOX is bounding box determined by Radius of Circle, not texture size
    bbox = Rect(c.x-_outerRing->getRadius(),c.y-_outerRing->getR(), _outerRing->getRadius() * 2 ,_outerRing->getR() * 2);
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("rotate.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("gong.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("pickup2.wav");

    
    
    //Load GAME OVER SCREEN and HIDE
    endMessage = Sprite::create("end_screen.png");
    endMessage->setPosition(Point(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    endMessage->setVisible(false);
    this->addChild(endMessage);

    //Testing Hexagon Math
    
    /** int r = 308;
    int R = 356;
    
     auto draw = DrawNode::create();

     
    Point Block1[] = {
        Point(c.x, c.y+R),  //1
        Point(c.x+r, c.y+R/2), //2
        Point(c.x+r, c.y-R/2), //3
        Point(c.x, c.y-R), //4
        Point(c.x-r,c.y-R/2), //5
        Point(c.x-r,c.y+R/2) //6
    };
    
    r = 213;
    R = 246;
    
    Point Block2[] = {
        Point(c.x, c.y+R),
        Point(c.x+r, c.y+R/2),
        Point(c.x+r, c.y-R/2),
        Point(c.x, c.y-R),
        Point(c.x-r,c.y-R/2),
        Point(c.x-r,c.y+R/2)
    };
    
    r = 113;
    R = 130;
    
    Point Block3[] = {
        Point(c.x, c.y+R),
        Point(c.x+r, c.y+R/2),
        Point(c.x+r, c.y-R/2),
        Point(c.x, c.y-R),
        Point(c.x-r,c.y-R/2),
        Point(c.x-r,c.y+R/2)
    };
    
    
    draw->drawPolygon(Block1, 6, Color4F(1,222,120,.4), 0, Color4F(0,0,0,0));
    draw->drawPolygon(Block2, 6, Color4F(222,1,120,.4), 0, Color4F(0,0,0,0));
    draw->drawPolygon(Block3, 6, Color4F(1,120,222,.4), 0, Color4F(0,0,0,0));
     this->addChild(draw);

     
     **/
    
    
    this->schedule(schedule_selector(GameLayer::update));
    _running = true;
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
    
    return true;
}


void GameLayer::onEnter()
{
    Layer::onEnter();
    
    // Register Touch Event
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
}

void GameLayer::onExit()
{
    // You don't need to unregister listeners here as new API
    // removes all linked listeners automatically in CCNode's destructor
    // which is the base class for all cocos2d DRAWING classes
    
    Layer::onExit();
}

void GameLayer::update(float dt){
    
    if(_outerRing->getNumberOfRunningActions() == 0 && _innerRing->getNumberOfRunningActions()== 0 && _midRing->getNumberOfRunningActions()==0){
    if(_outerRing->getcurrentPoint() == 0 && _innerRing->getcurrentPoint()==0 && _midRing->getcurrentPoint() == 0)
    {
        resetGame();
    }}
}

bool GameLayer::onTouchBegan(Touch* touch, Event *unused_event){
    if(!_running) {
        

        endMessage->setVisible(false);
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
        _running = true;

    }
    else {
        
    tap = Point(touch->getLocation());
        initial = tap;
    std::cout<<"Touch at :"<<tap.x<<","<<tap.y<<"\n";
        
    if(bbox.containsPoint(tap)){
        SimpleAudioEngine::getInstance()->playEffect("pickup2.wav");
        if(hexCheck(tap,_innerRing))
        {
            _selectedRing = _innerRing;
           // rotateRing(_innerRing);
        }
        else if(hexCheck(tap, _midRing))
        {
            _selectedRing = _midRing;
          //  rotateRing(_midRing);

        }
        else if(hexCheck(tap, _outerRing)){
            _selectedRing = _outerRing;
           // rotateRing(_outerRing);

        }
        
    }}
    
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event *unused_event){
    
    float threshold = 2;
    last_point = tap;
    tap = Point(touch->getLocation());
    std::cout<<"Touch moves to : "<<tap.x<<","<<tap.y<<"\n";
    
    
    float dp = (tap.x-c.x)*(initial.x-c.x)+(tap.y-c.y)*(initial.y - c.y);
    float vec_angle = acosf(dp/(tap.getDistance(c)*initial.getDistance(c)));
    
    float initial_slope = (initial.y - c.y)/(initial.x - c.x);
    float tap_slope = (tap.y - c.y)/(tap.x - c.x);
    
    vec_angle *= 6;
    
  /**  if((tap.x > c.x && (last_point.y < tap.y || (last_point.y <= tap.y && last_point.x > tap.x))) || (tap.x < c.x && (last_point.y > tap.y || (last_point.y >= tap.y && last_point.x < tap.x))))
    {
        vec_angle = -vec_angle;
    } **/
    
    
    std::cout<<"Vector Angle : "<<vec_angle<<"\n";

    if(_selectedRing && vec_angle >= threshold){
        
        vec_angle = (tap_slope > initial_slope) ? vec_angle : -vec_angle;
        _selectedRing->setRotation(_selectedRing->getRotation() + vec_angle > 360 ? _selectedRing->getRotation()+vec_angle  - 360: _selectedRing->getRotation() + vec_angle);
    }
}

void GameLayer::onTouchEnded(Touch* touch, Event *unused_event){
    if(_selectedRing){
        rotateRing(_selectedRing);
        _selectedRing = NULL;
        }
}

bool GameLayer::hexCheck(Point p, Ring* ring){

    Rect ibox = Rect(c.x-ring->getRadius(),c.y-(ring->getR()/2), ring->getRadius() * 2, ring->getR());
    
    if (ibox.containsPoint(p)) {
        return true;
    }
    else if(p.getDistance(c) <= ring->getRadius()){
        return true;
    }
    
    return false;
}

void GameLayer::rotateRing(Ring * ring){
    ring->turnWheel(); //adjusts ring point and angles
    if(ring->getRotation() != ring->getAngle()){
        ring->runAction(RotateTo::create(1.2, ring->getAngle()));
        SimpleAudioEngine::getInstance()->playEffect("rotate.wav");
    }

}

void GameLayer::resetGame(){
    endMessage->setVisible(true);
    _running = false;
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
    SimpleAudioEngine::getInstance()->playEffect("gong.wav");
    
    _outerRing->randomPoint();
    _midRing->randomPoint();
    _innerRing->randomPoint();
    
    _outerRing->runAction(RotateTo::create(1, _outerRing->getAngle()));
    _midRing->runAction(RotateTo::create(1, _midRing->getAngle()));
    _innerRing->runAction(RotateTo::create(1, _innerRing->getAngle()));
    
    
}