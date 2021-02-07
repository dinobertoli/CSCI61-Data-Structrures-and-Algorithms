#ifndef REORDEREVENT_H
#define REORDEREVENT_H

#include <iostream>
#include "orderEvent.h"
#include "softwareGurusBar.h"
#include "leaveEvent.h"

/*
 *Discrete Event-Driven Simulation
 *Project 2
 *Dino Bertoli
 *6/1/19
 *
 *chance of reordering the decreases after each reaorder
 *if reorder doesn't happed then leaveEvent is created
 *
*/

using namespace std;

class reorderEvent : public Event {
  public:
    unsigned int reorderCount = 5;
    reorderEvent (unsigned int time, unsigned int orderCount, unsigned int gs) : Event(time), groupSize(gs) { }
    virtual void processEvent ( );
  protected:
    unsigned int groupSize;
};

void reorderEvent::processEvent( )
{
    int toReorder = randBetween(1,3);
    if(toReorder - toReorder >= 1){
      theSimulation.scheduleEvent (new orderEvent(theSimulation.currentTime + randBetween(2,10), reorderCount, groupSize));
    }
    else{
      theSimulation.scheduleEvent (new leaveEvent(theSimulation.currentTime, groupSize));
    }

}

#endif
