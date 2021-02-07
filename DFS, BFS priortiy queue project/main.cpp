#include <iostream>
#include "box.h"
#include "arrayStack.h"
#include "position.h"
#include "queue.h"
using namespace std;


void setGrid(box*** &dfsArr,box*** &bfsArr, int dimension, float density);
void getParams(int& dimension, float& density);
void fillGrid(box*** &dfs, box*** &bfs, int dimens, float dens);
void printGrid(box*** dfsArr , box*** bfsArr , int dimension );
void scanGrids(box*** &dfsGrid, box*** &bfsGrid, int dimension);
void scanByDfs(box*** &maze, int mazeRow, int mazeCol, int label, int size);
void printGridsWFound(box*** grid, int dimension );
bool scanByBfs(box*** &grid, int row, int col, int label, int size);

int main(){
  int dimension = 13;
  float density = 0.5;

  getParams(dimension, density);

  box*** dfsGrid = new box**[dimension];
  box*** bfsGrid = new box**[dimension];

  setGrid(dfsGrid, bfsGrid, dimension, density);
  printGrid(dfsGrid, bfsGrid, dimension);
  scanGrids(dfsGrid, bfsGrid, dimension);

  cout << "Breadth first search results:" << endl;
  printGridsWFound(bfsGrid, dimension);
    cout << "Depth first search results:" << endl;
  printGridsWFound(dfsGrid, dimension);

}


void setGrid(box*** &dfsArr,box*** &bfsArr, int dimension, float density){
  for(int i = 0; i < dimension; i++){
    bfsArr[i] = new box*[dimension];
    dfsArr[i] = new box*[dimension];
  }

  for(int r = 0; r < dimension; r++){
    for(int c = 0; c < dimension; c++){
      bfsArr[r][c] = new box();
      dfsArr[r][c] = new box();
    }
  }

  fillGrid(dfsArr, bfsArr, dimension, density);
}

void printGrid(box*** dfsArr, box*** bfsArr, int dimension){
  cout << "BFS Grid:" << endl;
  for(int r = 0; r < dimension; r++){
    for(int c = 0; c < dimension; c++){
      if(bfsArr[r][c]->getLabel() == 0){
        cout << " (" <<"00" << ") ";
      }
      else if(bfsArr[r][c]->getLabel() < 10){
        cout << " (" << 0 << bfsArr[r][c]->getLabel() << ") ";
      }
      else{
        cout << " (" << bfsArr[r][c]->getLabel() << ") ";
      }
    }
    cout << endl;
  }

  cout << endl << endl;

  cout << "DFS Grid:" << endl;
  for(int r = 0; r < dimension; r++){
    for(int c = 0; c < dimension; c++){
      if(dfsArr[r][c]->getLabel() == 0){
        cout << " (" <<"00" << ") ";
      }
      else if(dfsArr[r][c]->getLabel() < 10){
        cout << " (" << 0 << dfsArr[r][c]->getLabel() << ") ";
      }
      else{
        cout << " (" << dfsArr[r][c]->getLabel() << ") ";
      }
    }
    cout << endl;
  }

  cout << endl << endl;
}

void fillGrid(box*** &dfs, box*** &bfs, int dimens, float dens){
  int compnts = (dimens - 2)*(dimens - 2)*dens;
  //srand(time(0));

  while(compnts > 0){
    int rand1 = rand() % (dimens - 2) + 1;
    int rand2 = rand() % (dimens - 2) + 1;
    if(bfs[rand1][rand2]->getLabel() == 0){
      compnts -=1;
      bfs[rand1][rand2]->setLabel(1);
      dfs[rand1][rand2]->setLabel(1);
    }
  }

  for(int i = 0; i < dimens; i++)
    for(int j = 0; j < dimens; j++){
        dfs[i][j]->setFoundAt(0);
        bfs[i][j]->setFoundAt(0);
    }
}

void getParams(int& dimension, float& density){
  cout << "Do you want to use default dimensions?(y/n)" << endl;
  string response;
  cin >> response;
  if(response == "n"){
    dimension = 0;
    density = 0.0;
    while(dimension < 5 || dimension > 20){
      cout << "Enter the dimension of the grid(between 5 and 20 inclusive)" << endl;
      cin >> dimension;
    }
    dimension += 2;

    while(density <= 0.0 || density >= 1.0){
      cout << "Enter a density for the grid(between 0.0 and 1.0)" << endl;
      cin >> density;
    }
  }
}

void scanGrids(box*** &dfsGrid, box*** &bfsGrid, int dimension){
  int componentLabel = 1;
  for(int row = 1; row < dimension; row++)
    for(int col = 1; col < dimension; col++)
      if(dfsGrid[row][col]->getLabel() == 1){
        componentLabel++;
        scanByDfs(dfsGrid, row, col, componentLabel, dimension);
        scanByBfs(bfsGrid, row, col, componentLabel, dimension);

      }
}

void scanByDfs(box*** &maze, int mazeRow, int mazeCol, int label, int size){
    int foundOrder = 1;
    int row, col;
    row = mazeRow;
    col = mazeCol;
    arrayStack<position>* path;

   path = new arrayStack<position>;

   // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up

   position here;
   here.row = row;
   here.col = col;
   maze[row][col]->setLabel(label); // prevent return to entrance
   maze[row][col]->setFoundAt(foundOrder);
   foundOrder++;
   int option = 0; // next move
   int lastOption = 3;
   path->push(here);

   // search for a path
   int emptyStackOverload = 0;
   while (!path->empty())
   {
     option = 0;
      int r, c;
      while (option <= lastOption)
      {
         r = here.row + offset[option].row;
         c = here.col + offset[option].col;
         if (maze[r][c]->getLabel() == 1) break;
         option++; // next option
      }

      // was a neighbor found?
      if (option <= lastOption)
      {// move to maze[r][c]
         path->push(here);
         here.row = r;
         here.col = c;
         maze[r][c]->setLabel(label);
         maze[r][c]->setFoundAt(foundOrder);
         foundOrder++;
      }//no neighbor
      else
      {
        path->pop();
        here = path->top();
      }
   }
}

bool scanByBfs(box*** &grid, int row, int col, int label, int size){
   int foundCount = 1;
   position start;
   start.row = row;
   start.col = col;

   position finish;
   finish.row = size - 1;
   finish.col = size - 1;


   // initialize offsets
   position offset[4];
   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up


   position here = start;
   grid[start.row][start.col]->setLabel(label); // block
   grid[start.row][start.col]->setFoundAt(foundCount);
   ++foundCount;
   int numOfNbrs = 4; // neighbors of a grid position

   // label reachable grid positions
   dynamicQueue<position> q;
   position nbr;
   do
   {// label neighbors of here
       for (int i = 0; i < numOfNbrs; i++)
       {// check out neighbors of here
          nbr.row = here.row + offset[i].row;
          nbr.col = here.col + offset[i].col;
          if (grid[nbr.row][nbr.col]->getLabel() == 1)
          {// unlabeled nbr, label it
             grid[nbr.row][nbr.col]->setLabel(label);
             grid[nbr.row][nbr.col]->setFoundAt(foundCount);
             ++foundCount;
             // put on queue for later expansion
   	        q.push(nbr);
          }
       }

      // finish not reached, can we move to a nbr?
      if (q.empty())
         return false;          // no path
      here = q.front();         // get next position
      q.pop();
   } while(true);

   return true;
}

void printGridsWFound(box*** grid, int dimension ){
  for(int r = 0; r < dimension; r++){
    for(int c = 0; c < dimension; c++){

      if(grid[r][c]->getLabel() == 0){
        cout << " (" <<"00" << "," << "00" << ") ";
      }

      else if(grid[r][c]->getLabel() < 10){
        cout << " (" << 0 << grid[r][c]->getLabel()  << ",";
        if(grid[r][c]->getFoundAt() > 9){
          cout << grid[r][c]->getFoundAt() << ") ";
        }
        else{
          cout << "0" << grid[r][c]->getFoundAt() << ") ";
        }
      }

      else{
        cout << " (" << grid[r][c]->getLabel()  << ",";
        if(grid[r][c]->getFoundAt() > 9){
          cout << grid[r][c]->getFoundAt() << ") ";
        }
        else{
          cout << "0" << grid[r][c]->getFoundAt() << ") ";
        }
      }
    }
    cout << endl;
  }

  cout << endl << endl;
}
