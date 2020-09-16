#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "noobnoob.h"

class Controller {
 public:
  void HandleInput(bool &running, NoobNoob &noobnoob) const;
};

#endif