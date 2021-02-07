#ifndef ORDEREVENT_H
#define ORDEREVENT_H

#include <iostream>
#include "reorderEvent.h"
#include "softwareGurusBar.h"
using namespace std;

/*
*Discrete Event-Driven Simulation
*Project 2
*Dino Bertoli
*6/1/19
*
*event-abstract class to be inherited from
*
*
*/
class orderEvent : public Event {
  public: orderEvent (unsigned int time, unsigned int orderCount, unsigned int gs): Event(time), groupSize(gs) {orderNum = orderCount;}
    virtual void processEvent ( );
  protected:
    unsigned int groupSize;
    unsigned int orderNum;
};

void orderEvent::processEvent( )
{
  // each member of the group orders a beer (type 1,2,3)
  vector<unsigned int> type;
  type.push_back(50);
  type.push_back(30);
  type.push_back(20);
  for (int i = 0; i < groupSize; i++){
    unsigned int beerType = theSimulation.weightedProbability(type);
    theBar.order(beerType);
  }

  int t = theSimulation.currentTime + randBetween(15,35);
  // schedule a LeaveEvent for this group of drinkers
  // all the group leaves together
  // add your code here ...
    theSimulation.scheduleEvent (new reorderEvent(theSimulation.currentTime, orderNum, groupSize));
};

#endif
