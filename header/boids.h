
#ifndef BOIDS_H
#define BOIDS_H
#include <stdlib.h>
#include <vector>
#include <iostream>
#define WIN_WIDTH  2
#define WIN_HEIGHT  2
#define WIN_DEPTH  2


//! Class for vector3
/*! This class , vector3 consists of three floating numbers x,y and z.
* It represents a three dimentional vector in coordinate geometry.
*/

struct vector3{
    float x; /**< used for representing the x coordinate of space*/
    float y; /**< used for representing the x coordinate of space*/
    float z; /**< used for representing the x coordinate of space*/
};


//! Class for Boids. 
/*! The class Boids consists of position and velocity as objects of type vector3 in it.  
 *  It represents the attributes of the boid object.
 *  It has three static methods normalize , crossProduct , and distance.
 *  These static methods are used to perform operations on vector3 objects  
 */

class Boids{
    public:
        vector3 position;/**< vector3 position*/
        vector3 velocity;/**< vector3 velocity*/
    public:
        /*! This method is constructor for the Boids
        * \param position and direction vector3 objects
        * \return A new boid with a position and velocity
        */
        Boids(vector3 vec,vector3 pos);
        /*!This method is constructor for the Boids
        * \param position vector3 objects
        * \return A new boid with a position
        */
        Boids(vector3 vec);
        /*! This function convertes the given vector3 object to a normalized form
        * \param any vector3 object
        * \return a new normalized vector3 object
        */
        static vector3 normalize(vector3 vec);
        /*! This is a static method which performs crossproduct of two given vectors
        * \param two vector3 objects
        * \return a new  vector3 object after performing operation
        */
        static vector3 crossProduct(vector3 one,vector3 two);
        /*! This is a static method which calculates the distance of two given position vectors
        * \param two vector3 objects
        * \return a float carrying distance
        */
	    static float distance(vector3 pos1,vector3 pos2);
        
};
#endif
