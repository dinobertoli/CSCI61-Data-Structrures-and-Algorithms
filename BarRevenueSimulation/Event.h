#ifndef EVENT_H
#define EVENT_H

#include <iostream>
using namespace std;

/*
*Discrete Event-Driven Simulation
*Project 2
*Dino Bertoli
*6/1/19
*
*event-abstract class to be inherited from for polymorphic children
*contains public time, eventComparison, and processEvent(to be defined by children)
*
*/

class Event {
  public:
    // constructor requires time of event
    Event (unsigned int t) : time(t) { }
    // time is a public data field
    unsigned int time;
    // execute event by invoking this method
    virtual void processEvent( ) { }
};

class eventComparison {
  public:
    bool operator ( ) (Event * left, Event * right)
    {
    return left->time > right->time;
    }
};

#endif
