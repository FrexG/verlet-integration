#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
#include <raylib.h>

// verlet object type
typedef struct{
  Vector2 pos;
  Vector2 prev_pos;
  Vector2 acceleration;
  float rad;
  Color color;
}VerletObj;

typedef struct{
  Vector2 pos;
  float rad;
}Constraint;

// Verlet ops func definitions
void SpawnVerletObj(VerletObj **objs, float W, float H, size_t size, size_t idx);
void Update(VerletObj *obj, float dt);
void AddConstraint(VerletObj *obj,Constraint constraint, float dt);
void Accelerate(VerletObj *obj, Vector2 g);
void HandleCollision(VerletObj *obj1, VerletObj **objs,size_t size,size_t idx);

void FreeVerletObj(VerletObj **objs,size_t size);


// Vector2 ops
Vector2 Vector2Subtract(Vector2 v1, Vector2 v2);
Vector2 Vector2Add(Vector2 v1, Vector2 v2);
Vector2 Vector2Normalize(Vector2 v1);
float Vector2Dot(Vector2 v1, Vector2 v2);

float Vector2Length(Vector2 v1, Vector2 v2);
