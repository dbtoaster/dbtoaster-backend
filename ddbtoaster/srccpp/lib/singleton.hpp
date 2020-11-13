#ifndef DBTOASTER_SINGLETON_HPP
#define DBTOASTER_SINGLETON_HPP

namespace dbtoaster {

template <typename T>
class Singleton {
 public:
  T* acquire() {
    ++counter_;
    if (instance_ == nullptr) { 
      instance_ = new T(); 
    }
    return instance_;
  }

  void release(T* obj) {
    if (instance_ == obj && --counter_ == 0) {
      delete instance_;
      instance_ = nullptr;
    }
  }

 private:
  static T* instance_;
  static size_t counter_;
};

template <typename T>
T* Singleton<T>::instance_ = nullptr;

template <typename T>
size_t Singleton<T>::counter_ = 0;

}

#endif /* DBTOASTER_SINGLETON_HPP */
