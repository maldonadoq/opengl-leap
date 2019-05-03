/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "Leap.h"
extern int gesture_idx;
extern int gesture_state;

using namespace Leap;

class TListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

private:
    bool checkFist(const Hand&);
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

bool TListener::checkFist(const Hand& hand){

    float sum = 0;
    int n = 0;
    bool r = false;
    
    const FingerList fingers = hand.fingers();
    Vector meta, proxi, inter;

    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl){
        const Finger finger = *fl;
        
        meta  = finger.bone(static_cast<Bone::Type>(0)).direction();
        proxi = finger.bone(static_cast<Bone::Type>(1)).direction();
        inter = finger.bone(static_cast<Bone::Type>(2)).direction();
        // std::cout << std::string(6, ' ') << bone.direction() << std::endl;
        sum += meta.dot(proxi);
        sum += proxi.dot(inter);

        if(finger.isExtended())
            n++;
    }    

    sum = sum / 10;
    if (sum <= 0.5 && n == 0)
        r = true;

    return r;
}

void TListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void TListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void TListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void TListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void TListener::onFrame(const Controller& controller) {
    const Frame frame = controller.frame();    

    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count(); ++g) {
        Gesture gesture = gestures[g];

        std::cout << gesture.duration() << " ms\n";


        switch (gesture.type()) {
            case Gesture::TYPE_CIRCLE:{
                CircleGesture circle = gesture;
                gesture_idx = 0;

                std::string clockwiseness;                
                if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2){
                    clockwiseness = "clockwise";
                    gesture_state = 1;
                }
                else{
                	clockwiseness = "counterclockwise";
                	gesture_state = -1;
                }

                std::cout << "circle - " << clockwiseness << "\n";
                break;
            }
            
            case Gesture::TYPE_SWIPE:{
                SwipeGesture swipe = gesture;
                gesture_idx = 1;
                std::cout << "swipe\n";

                // std::cout << "direction: " << swipe.direction().x << " ";
                if(swipe.direction().y < -0.7f)	gesture_state = -1;
                else if(swipe.direction().y > 0.6f)	gesture_state = 1;
                break;
            }
            case Gesture::TYPE_KEY_TAP:{
                KeyTapGesture tap = gesture;
                gesture_idx = 2;
                std::cout << "keytap\n";
                break;
            }
            case Gesture::TYPE_SCREEN_TAP:{
                ScreenTapGesture screentap = gesture;
                gesture_idx = 3;
                std::cout << "screentap\n";
                break;
            }
            default:{            	
                std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
                break;
            }
        }
    }

    HandList hands = frame.hands();
    Hand hand;
    if (hands.count() == 1) {
        hand = hands.frontmost();
        if (checkFist(hand)) {
            gesture_idx = 4;
            std::cout << "fist\n";
        }        
    }
}

void TListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void TListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void TListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void TListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void TListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

#endif