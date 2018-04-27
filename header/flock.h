
#ifndef FLOCK_H
#define FLOCK_H
#include "obstacle.h"
class Flock {
	public:
		std::vector<Boids *> boid_list;
		std::vector<Obstacle *> obs_list;

	public:
		void addBoid();
		int sizeOfFlock();
};
#endif