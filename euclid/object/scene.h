#pragma once

#include "euclid/object/base/object.h"
#include "euclid/object/portal.h"
#include "euclid/object/player.h"

class Scene {
public:
  virtual void Load(PObjectVec& objs, PPortalVec& portals, Player& player)=0;
  virtual void Unload() {};
};
