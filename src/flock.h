

#include "obstacle.h"
class Flock {
	public:
		std::vector<Boids *> boid_list;
		std::vector<Obstacle *> obs_list;

	public:
		void addBoid();
		int sizeOfFlock();
};