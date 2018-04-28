#include <math.h>
#include <iostream>
#include "boids.h"

#define PI 3.14159265

float Boids::distance(vector3 pos1,vector3 pos2){
	float c;
	c=(float)sqrt((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y)+(pos1.z-pos2.z)*(pos1.z-pos2.z));
	
	return c;
};

Boids::Boids(vector3 vec,vector3 pos){
	position = vec;
	velocity = pos;
	
};

Boids::Boids(vector3 vec){
	position = vec;
};
vector3 Boids::normalize(vector3 vec){
	float c = sqrt(vec.x * vec.x + vec.y*vec.y + vec.z * vec.z);
	vec.x = vec.x /c ;
	vec.y = vec.y /c;
	vec.z = vec.z /c ;
	return vec;
};

vector3 Boids::crossProduct(vector3 one,vector3 two){
	vector3 a;
	a.x = one.y * two.z - one.z * two.y ;
	a.y = -(one.x*two.z - one.z*two.x);
	a.z = one.x*two.y - one.y*two.x ;
	return a;
}
