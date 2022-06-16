
#include <stdio.h> // print functions
#include <math.h>  // math function
#include <stdlib.h>

// Input: user defines a bunch of bodies
// initial position


#define NUM_BODIES 5
double TIMESTEP = 2e6;
double G=6.6743e-11;
double INT_TIME = 3e7; // approx 1 YEAR

struct Vector
{
    double x;
    double y;
    double z;
};

float
random_float(const float min, const float max)
{
    if (max == min) return min;
    else if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;

    // return 0 if min > max
    return 0;
}


struct Body
{
    double mass;
    struct Vector velocity;
    struct Vector position;
    struct Vector acceleration;
};


void pos_update(struct Body *body, int i) {
   body[i].position.x += body[i].velocity.x*TIMESTEP;
   body[i].position.y += body[i].velocity.y*TIMESTEP;
   body[i].position.z += body[i].velocity.z*TIMESTEP;

}


void vel_partial_update(struct Body *body, int i) {

   body[i].velocity.x += body[i].acceleration.x*TIMESTEP/2;
   body[i].velocity.y += body[i].acceleration.y*TIMESTEP/2;
   body[i].velocity.z += body[i].acceleration.z*TIMESTEP/2;

}


void acc_update_1(struct Body *body, int i){
   double dx;
   double dy;
   double dz;
   double inv_r3;
   double newax[NUM_BODIES];
   double neway[NUM_BODIES];
   double newaz[NUM_BODIES];

   for (int j = 0; j < NUM_BODIES; j++){
      newax[j] = 0.0;
      neway[j] = 0.0;
      newaz[j] = 0.0;
   }


  //printf("X pos, Y pos, Z pos: %f\n", body.position.x);
   for (int j = 0; j < NUM_BODIES; j++) {

      if (j != i) {

          dx = body[j].position.x - body[i].position.x;
          dy = body[j].position.y - body[i].position.y;
          dz = body[j].position.z - body[i].position.z;
          
          //printf("Pair, %d, %d\n, X pos, Y pos, Z pos: %f,%f,%f\n", i, j, dx, dy, dz);

          inv_r3 = pow((pow(dx,2) + pow(dy,2)+ pow(dz,2) + 1000), -1.5);
          //printf("Inv r3: %f\n", inv_r3);

          newax[i] += G * (dx * inv_r3) * body[j].mass;
          neway[i] += G * (dy * inv_r3) * body[j].mass;
          newaz[i] += G * (dz * inv_r3) * body[j].mass;
          
      }

   }
   // printf("Ax: %f, i: %d\n", newax[i], i);
   // printf("Ay: %f, i: %d\n", neway[i], i);
   // printf("Az: %f, i: %d\n", newaz[i], i);

   body[i].acceleration.x = newax[i];
   body[i].acceleration.y = neway[i];
   body[i].acceleration.z = newaz[i];


}


int main() {

struct Body new_bodies[NUM_BODIES];

// SUN
new_bodies[0].mass = 2e30;

new_bodies[0].position.x = 0.0;
new_bodies[0].position.y = 0.0;
new_bodies[0].position.z = 0.0;

new_bodies[0].velocity.x = 0.0;
new_bodies[0].velocity.y = 0.0;
new_bodies[0].velocity.z = 0.0;

new_bodies[0].acceleration.x = 0.0;
new_bodies[0].acceleration.y = 0.0;
new_bodies[0].acceleration.z = 0.0;


//MERCURY
new_bodies[1].mass = 3.3e23;

new_bodies[1].position.x = 0.0;
new_bodies[1].position.y = 5.7e10;
new_bodies[1].position.z = 0.0;

new_bodies[1].velocity.x = -47e3;
new_bodies[1].velocity.y = 0.0;
new_bodies[1].velocity.z = 0.0;

new_bodies[1].acceleration.x = 0.0;
new_bodies[1].acceleration.y = 0.0;
new_bodies[1].acceleration.z = 0.0;

//VENUS
new_bodies[2].mass = 4.8e24;

new_bodies[2].position.x = 0.0;
new_bodies[2].position.y = 1.1e11;
new_bodies[2].position.z = 0.0;

new_bodies[2].velocity.x = -35e3;
new_bodies[2].velocity.y = 0.0;
new_bodies[2].velocity.z = 0.0;

new_bodies[2].acceleration.x = 0.0;
new_bodies[2].acceleration.y = 0.0;
new_bodies[2].acceleration.z = 0.0;

//EARTH
new_bodies[3].mass = 8e24;

new_bodies[3].position.x = 0.0;
new_bodies[3].position.y = 1.496e11;
new_bodies[3].position.z = 0.0;

new_bodies[3].velocity.x = -30e3;
new_bodies[3].velocity.y = 0.0;
new_bodies[3].velocity.z = 0.0;

new_bodies[3].acceleration.x = 0.0;
new_bodies[3].acceleration.y = 0.0;
new_bodies[3].acceleration.z = 0.0;

//MARS
 new_bodies[4].mass = 2.4e24;

 new_bodies[4].position.x = 0.0;
 new_bodies[4].position.y = 2.2e11;
 new_bodies[4].position.z = 0.0;

 new_bodies[4].velocity.x = -24e3;
 new_bodies[4].velocity.y = 0.0;
 new_bodies[4].velocity.z = 0.0;

 new_bodies[4].acceleration.x = 0.0;
 new_bodies[4].acceleration.y = 0.0;
 new_bodies[4].acceleration.z = 0.0;


    for (int timestep = 0; timestep < INT_TIME; timestep+=TIMESTEP) {

      //UPDATE VELOCITY 1/2 STEP
      for (int i = 0; i < NUM_BODIES; i++) {
         vel_partial_update(new_bodies, i);
      }
      //UPDATE POSITION 
      for (int i = 0; i < NUM_BODIES; i++) {
         pos_update(new_bodies, i);
      }
      //UPDATE ACCELERATION 
      for (int i = 0; i < NUM_BODIES; i++) {
         acc_update_1(new_bodies, i);
      }
      //UPDATE VELOCITY 1/2 STEP
      for (int i = 0; i < NUM_BODIES; i++) {

         vel_partial_update(new_bodies, i);

         printf("Body's X:, %d, %d, %.5e, %.5e, %.5e, \n", i, timestep, 6.68459e-12*new_bodies[i].position.x, 6.68459e-12*new_bodies[i].position.y, 6.68459e-12*new_bodies[i].position.z);
      }
   }
}


