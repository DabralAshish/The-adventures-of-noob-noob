#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "noobnoob.h"

class Controller {
 public:
  void HandleInput(bool &running, NoobNoob &noobnoob) const;

 private:
  void ChangeDirection(NoobNoob &noobnoob, NoobNoob::Direction input,
                       NoobNoob::Direction opposite) const;
};

#endif