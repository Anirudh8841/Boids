
#include "flock.h"


void Flock::addBoid(){
	float r1 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*WIN_WIDTH*2 - WIN_WIDTH;
	float r2 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*WIN_HEIGHT*2 - WIN_HEIGHT;
	float r3 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*WIN_DEPTH*2 - WIN_DEPTH;
	vector3 v1 = {r1,r2,r3};
	r1 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*2 - 1;
	r2 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*2 - 1;
	r3 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*2 - 1;
	vector3 v2 = {r1,r2,r3};
	Boids * boid_b = new Boids(v1,v2);
	boid_list.push_back(boid_b);
}

int Flock::sizeOfFlock(){
	return boid_list.size();
}