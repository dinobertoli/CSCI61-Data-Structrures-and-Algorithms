#include <iostream>
#include <vector>

using namespace std;

template<class T>
class dynamicQueue{
  public:
    dynamicQueue<T>();
    void pop();
    void push(T &param);
    bool empty();
    size_t size();
    T front();

  private:
    vector<T> _v;
    std::size_t _size;
    std::size_t _front;
};

  template<class T>
  dynamicQueue<T>::dynamicQueue(){
    _v.resize(10);
    _size = 0;
    _front = 0;
  }

  template<class T>
  void dynamicQueue<T>::pop(){
    _front++;
    _size--;
  }

  template<class T>
  void dynamicQueue<T>::push(T &param){
    if(_size == 0){
      _v.at(0) = param;
      _size++;
      _front = 0;
    }

    else if(_front == 0 && _size >= _v.size()){
      _v.resize(_size*2);
      _v.at((_front+_size)%_v.size()) = param;
      _size++;
    }

    else if(_size < _v.size()){
      _v.at((_front+_size)%_v.size()) = param;
      _size++;
    }

    else if(_front != 0){
      _v.at(_size%_v.size()) = param;
      _size++;
    }

  }

  template<class T>
  bool dynamicQueue<T>::empty(){
    return(_size == 0);
  }

  template<class T>
  size_t dynamicQueue<T>::size(){
    return(_size);
  }

  template<class T>
  T dynamicQueue<T>::front(){
    if(_size == 0){
      cout << "Empty Queue" << endl;
      return T();
    }
    else{
      return _v.at(_front);
    }
  }
