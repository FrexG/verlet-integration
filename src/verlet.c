#include "verlet.h"

void SpawnVerletObj(VerletObj **objs, float W, float H, size_t size, size_t idx){

  if(idx < size){
    VerletObj *obj = calloc(1, sizeof(VerletObj));

    Color color;

    color.r = 50 + rand() % 10;
    color.g = 50 + rand() % 16;
    color.b = 100 + rand() % 156;

    color.a = 255;

    if (!objs) {
      perror("Failed to allocate memory for VerletObj pointers");
      exit(EXIT_FAILURE);
    }

    int x = (int) W/4;
    int y = (int) H/4;
  

    obj->pos.x = obj->prev_pos.x = x;
    obj->pos.y = obj->prev_pos.y = y;

    obj->acceleration.x = 0.00f;
    obj->acceleration.y = 0.00f;

    obj->rad = 10 + rand() % (60); 

    obj->color = color;

    objs[idx] = obj;
  }

}

void AddConstraint(VerletObj *obj, Constraint constraint,float dt){
  // calculate the euclid distance from the center to the obj
  float d = Vector2Length(obj->pos,constraint.pos);

  if(d > constraint.rad - obj->rad){

    // find mov'nt axis
    Vector2 axis = Vector2Subtract(constraint.pos,obj->pos); 
    // normalize
    axis = Vector2Normalize(axis);
  
    //float force =  ((constraint.rad - obj->rad) - d) / (dt*dt);

    obj->pos.x = constraint.pos.x + axis.x * (constraint.rad - obj->rad);
    obj->pos.y = constraint.pos.y + axis.y * (constraint.rad - obj->rad);

    //obj->acceleration.x += axis.x * force;
    //obj->acceleration.y -= axis.y * force;

    // find the tangential velocity (perpendicular to the axis)
    Vector2 tangent = {-axis.y, axis.x};  // rotate axis by 90 degrees to get tangent
    // apply tangential movement
    float angularVelocity = Vector2Dot(tangent, Vector2Subtract(obj->pos, obj->prev_pos)) / dt;
    obj->acceleration.x += tangent.x * angularVelocity;
    obj->acceleration.y += tangent.y * angularVelocity;

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

void HandleCollision(VerletObj *obj1, VerletObj **objs, size_t size,size_t idx){
  
  float damp_coeff = 0.5f;
  for(size_t i = 0; i < size; ++i){

    if(i == idx)
      continue;
    float min_dist = obj1->rad + objs[i]->rad;

    Vector2 collision_axis = Vector2Subtract(obj1->pos,objs[i]->pos);

    float dist = sqrt(pow(collision_axis.x,2) + pow(collision_axis.y,2)); 

    float axis_x = collision_axis.x / dist;
    float axis_y = collision_axis.y / dist;


    if(dist < min_dist){

      float obj1_weight_ratio = obj1->rad / (obj1->rad + objs[i]->rad);
      float obj2_weight_ratio = objs[i]->rad / (obj1->rad + objs[i]->rad);

      float delta = 0.5 * (dist - min_dist);
      
      obj1->pos.x += axis_x * (obj2_weight_ratio * delta);
      objs[i]->pos.x -= axis_x * (obj1_weight_ratio * delta);

      obj1->pos.y += axis_y * (obj2_weight_ratio * delta);
      objs[i]->pos.y -= axis_y * (obj1_weight_ratio * delta);;

      }
    }
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

float Vector2Dot(Vector2 v1, Vector2 v2){
  return v1.x * v2.x + v1.y * v2.y;
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

void FreeVerletObj(VerletObj **objs,size_t size){
  for(size_t i = 0; i < size; ++i){
    free(objs[i]);
  }
  free(objs);
}
