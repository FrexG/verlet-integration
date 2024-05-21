#include <raylib.h>
#include <stdio.h>
#include "verlet.h"

// Global defines
#define SCREEN_W 1000
#define SCREEN_H 1000

void RenderVarletObj(VerletObj *obj){
      DrawCircle(obj->pos.x,obj->pos.y, obj->rad, obj->color);
}

void RenderConstraint(Constraint constraint){
      DrawCircleLinesV(constraint.pos, constraint.rad, GREEN);
}

int main(){
 // VerletObj obj1 = InitVerletObj(SCREEN_W * 0.2,SCREEN_H,40.0f);
 // VerletObj obj2 = InitVerletObj(SCREEN_W * 0.8,SCREEN_H,40.0f);

  srand(time(0));

  size_t obj_count = 0;
  size_t max_objs = 200; 

  VerletObj **objs = calloc(max_objs, sizeof(VerletObj *));

  if (!objs) {
    perror("Failed to allocate memory for VerletObj pointers");
    exit(EXIT_FAILURE);
    }

  Constraint constraint = {.pos = {.x = SCREEN_W/2, .y = SCREEN_H/2},.rad = SCREEN_W/2 - 10};
  Vector2 g = {.x=50.0f,.y=1000.0f};

  float dt = 0.0f;
  
  InitWindow(SCREEN_W, SCREEN_H, "Verlet");

  // set fps
  SetTargetFPS(60);
  while(!WindowShouldClose()){

    if(IsKeyPressed(KEY_SPACE)){
      if(obj_count < max_objs){
        SpawnVerletObj(objs, SCREEN_W, SCREEN_H, max_objs,obj_count); 
        obj_count++;
      }
    }

    BeginDrawing();
      dt = GetFrameTime(); 
      ClearBackground(BLACK);
      // render
      RenderConstraint(constraint);
      for(size_t i = 0; i < obj_count; ++i){

        VerletObj *obj = objs[i];

        RenderVarletObj(obj);
        
        Accelerate(obj,g);
        AddConstraint(obj, constraint,dt);
        HandleCollision(obj, objs, obj_count,i);
        Update(obj, dt);
    }
      
    EndDrawing();
  }

  FreeVerletObj(objs,obj_count);

return 0;
}
