#pragma once

#include "euclid/object/base/object.h"
#include "euclid/geometry/resources.h"

class Ground : public Object {
public:
  Ground(bool slope=false) {
    if (slope) {
      mesh = AquireMesh("../assets/ground_slope.obj");
    } else {
      mesh = AquireMesh("../assets/ground.obj");
    }
    shader = AquireShader("texture");
    texture = AquireTexture("checker_green.bmp");
    scale = Vector3(10, 1, 10);
  }
  virtual ~Ground() {}
};
