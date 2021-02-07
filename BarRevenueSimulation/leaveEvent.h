#ifndef LEAVEEVENT_H
#define LEAVEEVENT_H

#include <iostream>
#include "Event.h"
#include "softwareGurusBar.h"
using namespace std;

/*
*Discrete Event-Driven Simulation
*Project 2
*Dino Bertoli
*6/1/19
*
*group leaves priority queue and space for more customers is made
*
*
*/

class leaveEvent : public Event {
  public:
    leaveEvent (unsigned int time, unsigned int gs): Event(time), groupSize(gs) {}
    virtual void processEvent ( );
  protected:
    unsigned int groupSize;
};

void leaveEvent::processEvent ( )
{
  theBar.leave(groupSize);
}

#endif
