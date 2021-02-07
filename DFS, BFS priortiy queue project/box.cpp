#include <iostream>
#include "box.h"

box::box(){
label = 0;
foundAt = 0;
}

box::box(int lab){
  label = lab;
  foundAt = 0;
}

box::box(int lab, int found){
label = lab;
foundAt = found;
}
