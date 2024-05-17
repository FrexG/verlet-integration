#include <math.h>
#include "verlet.h"

VerletObj InitVerletObj(float W,float H, float rad){
  VerletObj obj;
  obj.pos.x = obj.prev_pos.x = (float) W/2;
  obj.pos.y = obj.prev_pos.y = (float) H/2;

  obj.acceleration.x = 0.00f;
  obj.acceleration.y = 0.00f;

  obj.rad = rad;

  return obj;
}

void AddConstraint(VerletObj *obj, Constraint constraint,float dt){
  // calculate the euclid distance from the center to the obj
  float d = Vector2Length(obj->pos,constraint.pos);

  if(d > constraint.rad - obj->rad){

    // find mov'nt axis
    Vector2 axis = Vector2Subtract(constraint.pos,obj->pos); 
    // normalize
    axis = Vector2Normalize(axis);
  
    float force =  (constraint.rad - obj->rad) - d * (dt*dt);

    printf("force = %f\n",force);
    printf("axis.x = %f\n",axis.x);
    printf("axis.y = %f\n",axis.y);

    //obj->pos.x = constraint.pos.x + axis.x * (constraint.rad - obj->rad);
    //obj->pos.y = constraint.pos.y + axis.y * (constraint.rad - obj->rad);

    obj->acceleration.x -= axis.x * force;
    obj->acceleration.y -= axis.y * force;

    }

}

void Update(VerletObj *obj, float dt){
  /*verlet integration*/
  //  find the diplacement of the object
  //  how much it moved since dt.
  Vector2 disp = Vector2Subtract(obj->prev_pos,obj->pos);


  obj->prev_pos = obj->pos;

  // update the current position based on the acceleration
  obj->pos.x = obj->prev_pos.x + disp.x + obj->acceleration.x * (dt*dt);
  obj->pos.y = obj->prev_pos.y + disp.y + obj->acceleration.y * (dt*dt);

  obj->acceleration.x = 0;
  obj->acceleration.y = 0;


}

void Accelerate(VerletObj *obj, Vector2 g){

  obj->acceleration.x += g.x;
  obj->acceleration.y += g.y;
}

Vector2 Vector2Subtract(Vector2 v1, Vector2 v2){
  Vector2 diff;

  diff.x = v2.x - v1.x;
  diff.y = v2.y - v1.y;

  return diff;
}

Vector2 Vector2Add(Vector2 v1, Vector2 v2){
  Vector2 sum;

  sum.x = v2.x + v1.x;
  sum.y = v2.y + v1.y;

  return sum;
}

Vector2 Vector2Normalize(Vector2 v1){
  Vector2 norm;
  float magnitude = sqrt((v1.x*v1.x) + (v1.y*v1.y));
  
  norm.x = v1.x / magnitude;
  norm.y = v1.y / magnitude;
  
  return norm;
}

float Vector2Length(Vector2 v1, Vector2 v2){
  return sqrt(pow((v2.x - v1.x),2) + pow((v2.y - v1.y),2));
}


