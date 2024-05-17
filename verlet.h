#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

// verlet object type
typedef struct{
  Vector2 pos;
  Vector2 prev_pos;
  Vector2 acceleration;
  float rad;
}VerletObj;

typedef struct{
  Vector2 pos;
  float rad;
}Constraint;

// Verlet ops func definitions
VerletObj InitVerletObj(float W,float H, float rad);
void Update(VerletObj *obj, float dt);
void AddConstraint(VerletObj *obj,Constraint constraint, float dt);

void Accelerate(VerletObj *obj, Vector2 g);


// Vector2 ops

Vector2 Vector2Subtract(Vector2 v1, Vector2 v2);
Vector2 Vector2Add(Vector2 v1, Vector2 v2);
Vector2 Vector2Normalize(Vector2 v1);

float Vector2Length(Vector2 v1, Vector2 v2);
