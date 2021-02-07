#include <iostream>
#include <vector>
using namespace std;

/*
 *eventPQ
 *Project 2
 *Dino Bertoli
 *6/1/19
 *
 *minHeap priority queue for vector events
 *
*/

class eventPQ{
  public:

  eventPQ(){
    n = 0;
  }

  bool empty( ){
    return n == 0;
  }

  void insert(Event* x) {
      if(empty()){
        pq.push_back(x);
        pq.push_back(x);
        n++;
      }
      else{
        pq.push_back(x);
        n++;
        swim(n);
      }
  }


  void deleteMin() {
      exch(1, n);
      pq.pop_back();
      n--;
      sink(1, n);
  }

  void swim(int k) {
      while (k > 1 && pq[k/2]->time > pq[k]->time) {
        exch(k, k/2); // parent of
        k = k/2; // node k is at k/2
      }
    }

  int size();

  void printHeap(){
    for(int i = 0; i < n + 1; i++){
      std::cout << pq[i] << std::endl;
    }
  }

  Event* min(){
    return pq[1];
  }

  private:
    vector<Event*> pq;
    int n;

    void sink(int k, int n) {
        while (2*k <= n) {
          int j = 2*k;
          if (j < n && pq[j]->time > pq[j+1]->time) j++;
          if (pq[j]->time >= pq[k]->time) break;
          exch(k, j);
          k = j;
        }
      }

      bool greater(int i, int j){
         //return ((pq[i]->compareTo(pq[j])) > 0);
         return (pq[i] > pq[j]);
      }

      void exch(int i, int j){
         pq[0]=pq[i];
         pq[i] = pq[j];
         pq[j] = pq[0];
      }
};
