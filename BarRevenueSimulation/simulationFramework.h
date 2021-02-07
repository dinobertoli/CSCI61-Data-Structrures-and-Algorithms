#ifndef SIMULATIONFRAMEWORK_H
#define SIMULATIONFRAMEWORK_H

#include "iostream"
#include "Event.h"
#include "eventPQ.h"
class SimulationFramework {
  public:
    SimulationFramework ( ) : eventQueue( ), currentTime(0) { }
    void scheduleEvent (Event * newEvent)
    {
      // insert newEvent into eventQueue (Priority Queue)
      // Priority Queue is based on MinHeap using newEvent’s time
      eventQueue.insert(newEvent);
    }

    //returns 1,2,3 based on weighted probability from the passed parameters
    unsigned int weightedProbability(vector<unsigned int> x);
    void run( );
    unsigned int currentTime;

  protected:
    eventPQ eventQueue;
};
unsigned int SimulationFramework::weightedProbability(vector<unsigned int> x){
  unsigned int total;
  for(unsigned int i = 0; i < x.size(); i++){
    total += x[i];
  }
  unsigned int randNum = rand() % total + 1;
  if(randNum < x[0]){
    return 0;
  }
  else if(randNum < (x[1]+x[0])){
    return 1;
  }
  else{
    return 2;
  }
}


void SimulationFramework::run( )
{
  // execute events until event queue becomes empty
  while (! eventQueue.empty( )) {
    // copy & remove min-priority element (min time) from eventQueue
    Event * nextEvent = eventQueue.min( );
    // update simulation’s current time
    currentTime = nextEvent->time;
    // process nextEvent
    nextEvent->processEvent( ); // what do you see here???
    eventQueue.deleteMin( );
    // cleanup nextEvent object
    delete nextEvent;
  }
}

#endif
