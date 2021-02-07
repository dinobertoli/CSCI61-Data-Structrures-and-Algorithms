#include <iostream>
#include "arriveEvent.h"

/*
 *Discrete Event-Driven Simulation
 *Project 2
 *Dino Bertoli
 *6/1/19
 *
 *simulates profit of softwareGurusBar with given input for seats
 *
*/

int main( ) {
  srand(time(0));
  ofstream file;
  file.open ("output.txt");
  // load priority queue with initial arrive Events then run simulation
  unsigned int t = 0;
  // load 4 hours (240 minutes) of arrive Events

  while (t < 240) {
    // new group every 2-5 minutes
    t += randBetween(2,5);
    // group size ranges from 1 to 5
    unsigned int randomSize = randBetween(1,5);
    theSimulation.scheduleEvent(new arriveEvent(t, randomSize));
  }
  // then run simulation and print profits
  theSimulation.run( );
  cout << "Total profits " << theBar.profit << endl;
  file << "Total profits " << theBar.profit << endl;
  return 0;
  file.close();
}
