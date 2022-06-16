#include <stdio.h> // print functions
#include <math.h>  // math function
#include <stdlib.h>
#include <omp.h>
#include "timer.h"

// Input: user defines bodies in struct, timestep and inttime


#define NUM_BODIES 4003
double TIMESTEP = 3e6;
double G=6.6743e-11;
double INT_TIME = 6e12; //in seconds

//create vector
struct Vector
{
    double x;
    double y;
    double z;
};


//function for random distibution between range
float
random_float(const float min, const float max)
{
    if (max == min) return min;
    else if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;

    // return 0 if min > max
    return 0;
}

//create body struct
struct Body
{
    double mass;
    struct Vector velocity;
    struct Vector position;
    struct Vector acceleration;
};


//position updates in x, y, z
void pos_update(struct Body *body, int i) {
   body[i].position.x += body[i].velocity.x*TIMESTEP;
   body[i].position.y += body[i].velocity.y*TIMESTEP;
   body[i].position.z += body[i].velocity.z*TIMESTEP;

}

// velocity updates in x, y, z
void vel_partial_update(struct Body *body, int i) {

   body[i].velocity.x += body[i].acceleration.x*TIMESTEP/2;
   body[i].velocity.y += body[i].acceleration.y*TIMESTEP/2;
   body[i].velocity.z += body[i].acceleration.z*TIMESTEP/2;

}


//acceleration updates using Newton's 2nd Law
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


   for (int j = 0; j < NUM_BODIES; j++) {

      if (j != i) {

          dx = body[j].position.x - body[i].position.x;
          dy = body[j].position.y - body[i].position.y;
          dz = body[j].position.z - body[i].position.z;
          

          inv_r3 = pow((pow(dx,2) + pow(dy,2)+ pow(dz,2) + 1000), -1.5);


          newax[i] += G * (dx * inv_r3) * body[j].mass;
          neway[i] += G * (dy * inv_r3) * body[j].mass;
          newaz[i] += G * (dz * inv_r3) * body[j].mass;
          
      }

   }

   body[i].acceleration.x = newax[i];
   body[i].acceleration.y = neway[i];
   body[i].acceleration.z = newaz[i];


}


int main() {

int nthreads, tid;


//parallel openmp implementation
#pragma omp parallel private (nthreads, tid)
    {
        /* Obtain thread number */
        tid = omp_get_thread_num();
    
        /* Only master thread does this */
        if (tid == 0) 
        {
            nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);
        }
    }


//HERE WE DEFINE THE BODIES
struct Body new_bodies[NUM_BODIES];

//SUN

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

//JUPITER
new_bodies[1].mass = 1.8e27;

new_bodies[1].position.x = 0.0;
new_bodies[1].position.y = 7.7e11;
new_bodies[1].position.z = 0.0;

new_bodies[1].velocity.x = -13e3;
new_bodies[1].velocity.y = 0.0;
new_bodies[1].velocity.z = 0.0;

new_bodies[1].acceleration.x = 0.0;
new_bodies[1].acceleration.y = 0.0;
new_bodies[1].acceleration.z = 0.0;


//ASTEROIDS
for(int i=2; i<NUM_BODIES; i++){

   double theta;
   double r;
   new_bodies[i].mass = random_float(0.1, 1);

   theta = random_float(0, 2*M_PI);
   r = random_float(1.5e11*2.5, 1.5e11*3.5);
   
       new_bodies[i].position.x = r*cos(theta);
       new_bodies[i].position.y = r*sin(theta);
       new_bodies[i].position.z = 0.0;

       //GIVE ASTEROIDS POSITION AND VELOCITIES THAT ARE PERPENDICULAR
       new_bodies[i].velocity.x = - sqrt(G*2e30/sqrt(pow(new_bodies[i].position.x, 2) + pow(new_bodies[i].position.y, 2)))*sin(theta);
       new_bodies[i].velocity.y = sqrt(G*2e30/sqrt(pow(new_bodies[i].position.x, 2) + pow(new_bodies[i].position.y, 2)))*cos(theta);
       new_bodies[i].velocity.z = 0.0;

       new_bodies[i].acceleration.x = 0.0;
       new_bodies[i].acceleration.y = 0.0;
       new_bodies[i].acceleration.z = 0.0;


}
// TIME CODE
  double wtime;
    wtime = omp_get_wtime ( );
   

  #pragma omp parallel shared(new_bodies)
      {
        //UPDATE 1/2 VELOCITY
      for (unsigned long int  timestep = 0; timestep < INT_TIME; timestep+=TIMESTEP) {
         #pragma omp for
          for (int i = 0; i < NUM_BODIES; i++) {
             vel_partial_update(new_bodies, i);
          }
          //UPDATE POSITION
          #pragma omp for
          for (int i = 0; i < NUM_BODIES; i++) {
             pos_update(new_bodies, i);
             // THIS IF STATEMENT ALLOWS TO ONLY PRINT LAST TWO TIMESTEPS. REMOVE IF IF ALL STEPS ARE TO BE PRINTED ON CSV
                if ((int) (timestep/TIMESTEP) == 0 || (int) (timestep/TIMESTEP) == 999999){
           printf("Body's X:, %d, %.5e, %.5e, %.5e, \n", i, timestep/3.e7, 6.68459e-12*new_bodies[i].position.x, 6.68459e-12*new_bodies[i].position.y);
        }  
	}
        //UPDATE ACCELERATION
          #pragma omp for
          for (int i = 0; i < NUM_BODIES; i++) {
             acc_update_1(new_bodies, i);
          }
          //UPDATE 1/2 VELOCITY
          #pragma omp for
        for (int i = 0; i < NUM_BODIES; i++) {

           vel_partial_update(new_bodies, i);
        }

     }
   }
  wtime = omp_get_wtime ( ) - wtime;
  //GET FINAL RUN TIME
   printf ( "  Wallclock time = %f\n", wtime );

}



