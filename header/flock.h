
#ifndef FLOCK_H
#define FLOCK_H
#include "obstacle.h"


//! Class for Flock. 
/*! The class Flock consists of boids list and obstacles list.  
 *  It represents the attributes of the flock of boids.
 *  It has two methods addboid and sizeofFlock.
 *  These methods are used to add a boid to flock and get the size of flock respectively.  
 */

class Flock {
	public:
		std::vector<Boids *> boid_list; /**< boid_list stored in a vector*/
		std::vector<Obstacle *> obs_list;/**< obstacle_list stored in a vector*/

	public:
	    /*! This function is used to add a boid to flock
        * \param no parameters required
        * \return creates and adds a new boid to the boids list
        */
		void addBoid();
		/*! This method is used to query for the number of boids in flock
        * \param no parameters required
        * \return returns an int which tells us the number of boids
        */
		int sizeOfFlock();
};
#endif
