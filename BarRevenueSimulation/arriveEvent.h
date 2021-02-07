#ifndef ARRIVEEVENT_H
#define ARRIVEEVENT_H

#include <iostream>
#include "orderEvent.h"
#include "softwareGurusBar.h"

using namespace std;

/*
*Discrete Event-Driven Simulation
*Project 2
*Dino Bertoli
*6/1/19
*
*polymorphic child of event
*responsible for processing of arriving customers and setting up order event for customers
*
*/

class arriveEvent : public Event {
  public: arriveEvent (unsigned int time, unsigned int gs) : Event(time), groupSize(gs) {}
    virtual void processEvent ( );
  protected:
    unsigned int groupSize;
};
void arriveEvent::processEvent( )
{
  if (theBar.canSeat(groupSize))// place an order within 2 & 10 minutes
    theSimulation.scheduleEvent (new orderEvent(theSimulation.currentTime + randBetween(2,10), 0, groupSize));
}

#endif
