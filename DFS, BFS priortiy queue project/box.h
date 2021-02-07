#include <iostream>

class box{
public:
  box();
  box(int lab);
  box(int lab, int found);
  int getLabel(){return label;}
  int getFoundAt(){return foundAt;}

  void setLabel(int lab){label = lab;}
  void setFoundAt(int at){foundAt = at;}
private:
  int label;
  int foundAt;
};
