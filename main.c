#include <raylib.h>
#include <stdio.h>
#include "verlet.h"

// Global defines
#define SCREEN_W 800
#define SCREEN_H 800

void RenderVarletObj(VerletObj obj){
      DrawCircleLines(obj.pos.x,obj.pos.y, obj.rad, WHITE);
}

void RenderConstraint(Constraint constraint){
      DrawCircleLinesV(constraint.pos, constraint.rad, GREEN);
}

int main(){
  VerletObj obj = InitVerletObj(SCREEN_W,SCREEN_H,40.0f);
  Constraint constraint = {.pos = {.x = SCREEN_W/2, .y = SCREEN_H/2},.rad = SCREEN_W/2};
  Vector2 g = {.x=50.0f,.y=50.0f};

  float dt = 0.0f;
  
  printf("Obj.x = %f\n",obj.pos.x);

  InitWindow(SCREEN_W, SCREEN_H, "Verlet");

  // set fps
  SetTargetFPS(60);
  while(!WindowShouldClose()){
    BeginDrawing();
      dt = GetFrameTime(); 
      ClearBackground(GRAY);
      // render
      RenderVarletObj(obj);
      RenderConstraint(constraint);
      
      Accelerate(&obj,g);
      Update(&obj, dt);
      AddConstraint(&obj, constraint,dt);
      
    EndDrawing();
  }

return 0;
}
