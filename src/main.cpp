/*!
* \author Kurmapu Venkata Vijaya Sai Prasanth
* \author Korakoppula Suresh
* \version 1.0
* \date 27-04-2018 
* \warning Some features are yet to be implemented
* \mainpage Simulation of Boids in 3d space using Opengl
* \section Functionality Overview
*   -# Create a boids at random position.
*   -# Rotate and Scale whole boids space.
*   -# Boids follow these three rules :-
*       - Coheshion
*       - Alignment
*		- Separation
* \section Controls
* \subsection Keyboard_Controls
*	 -# Q , A - Rotate world space about x axis
*	 -# W , S - Rotate world space about y axis
*    -# E , D - Rotate world space about z axis
*    -# P , L - Scale world space
*    -# B     - Generate a boid at random position
*	 -# R	  - Reset the transformations of the world space
* \section How_To_Run
* \warning This is only tested in linux
* \subsection  This project is provided with the makefile 
*    -# $ make 
*    -# $ ./boids
*/




#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "flock.h"
#include <time.h>
#define PI 3.14159265
#define MAX_DISTANCE 1.5
#define MIN_DISTANCE 0.2
#define RULE1_FACTOR 6
#define RULE2_FACTOR 2
#define RULE3_FACTOR 15


/*! Main method creates a window using glut libraries and 
* renders a 3D - space for the boids to move .
* User can use the controls specified to generate the boids and 
* watch the simulation . The boids follow three rules cohesion ,separation 
* and alignment 
* 
*/
std::vector<int> closestNeighbours;
vector3 origin = {0,0,0};
Flock*  flock_a = new Flock();
Flock*  flock_b = new Flock();

int oldTimeSinceStart = 0;
int xrot = 0;
int yrot = 0;
int zrot = 0;
int scale = 1;
vector3 tem = {0.0,0.0,0.0};
// for rule two
vector3 tem2  = {0,0,0};
// for rule three
vector3 tem3 = {0.0,0.0,0.0};

/*! This function is used to simulate the cohesion rule
* \param an integer which represents the boid number
* \return doesnot return anything
*/
void method1(int i){

	closestNeighbours.clear();

	tem.x = 0.0;
	tem.y = 0.0;
	tem.z = 0.0;

	float temp;
	for(int j = 0;j< flock_a->sizeOfFlock();j++){
		if(i!=j){
			temp = Boids::distance(flock_a->boid_list[i]->position,flock_a->boid_list[j]->position);
			if((temp <MAX_DISTANCE)&&(temp>MIN_DISTANCE)){
				closestNeighbours.push_back(j);
			}
		}
		
	}

	for(int j = 0; j<closestNeighbours.size();j++){
		tem.x = tem.x + flock_a->boid_list[closestNeighbours[j]]->position.x;
		tem.y = tem.y + flock_a->boid_list[closestNeighbours[j]]->position.y;
		tem.z = tem.z + flock_a->boid_list[closestNeighbours[j]]->position.z;
	}

	if(closestNeighbours.size()!=0){
		tem.x = (tem.x/closestNeighbours.size())-flock_a->boid_list[i]->position.x;
		tem.y = (tem.y/closestNeighbours.size())-flock_a->boid_list[i]->position.y;	
		tem.z = (tem.z/closestNeighbours.size())-flock_a->boid_list[i]->position.z;
	}

	tem.x = tem.x/RULE1_FACTOR;
	tem.y = tem.y/RULE1_FACTOR;
	tem.z = tem.z/RULE1_FACTOR;

};

void method2(int i){

	closestNeighbours.clear();

	tem2.x = 0.0;
	tem2.y = 0.0;
	tem2.z = 0.0;

	float temp;

	for(int j = 0;j< flock_a->sizeOfFlock();j++){
		if(i!=j){
			temp = Boids::distance(flock_a->boid_list[i]->position,flock_a->boid_list[j]->position);
			if((temp<=MIN_DISTANCE)){
				closestNeighbours.push_back(j);
			}
		}
	}
	for(int j = 0; j<closestNeighbours.size();j++){
		tem2.x = tem2.x + flock_a->boid_list[closestNeighbours[j]]->position.x-flock_a->boid_list[i]->position.x;
		tem2.y = tem2.y + flock_a->boid_list[closestNeighbours[j]]->position.y-flock_a->boid_list[i]->position.y;
		tem2.z = tem2.z + flock_a->boid_list[closestNeighbours[j]]->position.z-flock_a->boid_list[i]->position.z;
	}

	tem2.x = -tem2.x/RULE2_FACTOR;
	tem2.y = -tem2.y/RULE2_FACTOR;
	tem2.z = -tem2.z/RULE2_FACTOR;
};

void method3(int i){
	closestNeighbours.clear();
	tem3.x = 0.0;
	tem3.y = 0.0;
	tem3.z = 0.0;
	float temp;
	for(int j = 0;j< flock_a->sizeOfFlock();j++){
		if(i!=j){
			temp = Boids::distance(flock_a->boid_list[i]->position,flock_a->boid_list[j]->position);
			if((temp <MAX_DISTANCE)&&(temp>MIN_DISTANCE)){
				closestNeighbours.push_back(j);
			}
		}
		
	}
	for(int j = 0; j<closestNeighbours.size();j++){
		tem3.x = tem3.x + flock_a->boid_list[closestNeighbours[j]]->velocity.x;
		tem3.y = tem3.y + flock_a->boid_list[closestNeighbours[j]]->velocity.y;
		tem3.z = tem3.z + flock_a->boid_list[closestNeighbours[j]]->velocity.z;
	}
	if(closestNeighbours.size()!=0){
		tem3.x = (tem3.x/closestNeighbours.size())-flock_a->boid_list[i]->velocity.x;
		tem3.y = (tem3.y/closestNeighbours.size())-flock_a->boid_list[i]->velocity.y;	
		tem3.z = (tem3.z/closestNeighbours.size())-flock_a->boid_list[i]->velocity.z;
	}	
	tem3.x = tem3.x/RULE3_FACTOR;
	tem3.y = tem3.y/RULE3_FACTOR;
	tem3.z = tem3.z/RULE3_FACTOR;

};

void myInit()
{
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(60.0, 64/48.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(0,0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3d(0,0,0);
};

void boundaries(){
	glBegin(GL_LINE_LOOP); // Draw Platform
	glVertex3d(WIN_WIDTH,-WIN_HEIGHT,WIN_DEPTH); 
	glVertex3d(WIN_WIDTH,WIN_HEIGHT,WIN_DEPTH);
	glVertex3d(-WIN_WIDTH,WIN_HEIGHT,WIN_DEPTH);
	glVertex3d(-WIN_WIDTH,-WIN_HEIGHT,WIN_DEPTH);
	glEnd();
	glBegin(GL_LINE_LOOP); // Draw Platform
	glVertex3d(WIN_WIDTH,-WIN_HEIGHT,-WIN_DEPTH); 
	glVertex3d(WIN_WIDTH,WIN_HEIGHT,-WIN_DEPTH);
	glVertex3d(-WIN_WIDTH,WIN_HEIGHT,-WIN_DEPTH);
	glVertex3d(-WIN_WIDTH,-WIN_HEIGHT,-WIN_DEPTH);
	glEnd();
	glBegin(GL_LINE_LOOP); // Draw Platform
	glVertex3d(WIN_WIDTH,WIN_HEIGHT,WIN_DEPTH); 
	glVertex3d(WIN_WIDTH,WIN_HEIGHT,-WIN_DEPTH);
	glEnd();
	glBegin(GL_LINE_LOOP); // Draw Platform
	glVertex3d(-WIN_WIDTH,WIN_HEIGHT,WIN_DEPTH); 
	glVertex3d(-WIN_WIDTH,WIN_HEIGHT,-WIN_DEPTH);
	glEnd();
	glBegin(GL_LINE_LOOP); // Draw Platform
	glVertex3d(-WIN_WIDTH,-WIN_HEIGHT,WIN_DEPTH); 
	glVertex3d(-WIN_WIDTH,-WIN_HEIGHT,-WIN_DEPTH);
	glEnd();
	glBegin(GL_LINE_LOOP); // Draw Platform
	glVertex3d(WIN_WIDTH,-WIN_HEIGHT,WIN_DEPTH); 
	glVertex3d(WIN_WIDTH,-WIN_HEIGHT,-WIN_DEPTH);
	glEnd();
}

void axes(){
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3d(1,0,0);
	glVertex3d(WIN_WIDTH/2,0,0);
	glVertex3d(-WIN_WIDTH/2,0,0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3d(0,1,0);
	glVertex3d(0,WIN_HEIGHT/2,0);
	glVertex3d(0,-WIN_HEIGHT/2,0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3d(0,0,1);
	glVertex3d(0,0,WIN_DEPTH/2);
	glVertex3d(0,0,-WIN_DEPTH/2);
	glEnd();
	glPopMatrix();
}

void myDisplay()
{
	/*
	*This method takes void as paramater and this is the main method for the display
	* of the objects in the 
	*/
	

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glRotatef(xrot,1,0,0);
	glRotatef(yrot,0,1,0);
	glRotatef(zrot,0,0,1);
	boundaries();
	axes();
	float g;
	vector3 kuko,axis;
	vector3 zaxis = {0,0,1};
	// BOIDS
	 // draw and place Sphere
   for(int i =0 ;i< flock_a->sizeOfFlock();i++){
   		kuko = Boids::normalize(flock_a->boid_list[i]->velocity);
   		g = (acosf(kuko.z)) * 180.0 / PI;
   		axis = Boids::normalize(Boids::crossProduct(zaxis,flock_a->boid_list[i]->velocity));
		glPushMatrix();
	    glTranslated(-flock_a->boid_list[i]->position.x,-flock_a->boid_list[i]->position.y,-flock_a->boid_list[i]->position.z);
		glRotatef(g-180,axis.x,axis.y,axis.z);
		glColor3d(0.2,0.8,0.1);
		glutSolidCone(0.05, 0.2, 50, 50);
	    glTranslated(flock_a->boid_list[i]->position.x,flock_a->boid_list[i]->position.y,flock_a->boid_list[i]->position.z);
		glPopMatrix();
    }
	glPopMatrix();
	glutSwapBuffers();

}
void obstacle(){

	for (int i = 0;i<flock_a->sizeOfFlock();i++){
		if(flock_a->boid_list[i]->position.y >= WIN_HEIGHT)
		{
			//boid_list[i]->velocity.y= -0.8;
			if(flock_a->boid_list[i]->velocity.y>0)
				flock_a->boid_list[i]->velocity.y = -flock_a->boid_list[i]->velocity.y;
		}
	/*Lower bound of the window*/
		else if(flock_a->boid_list[i]->position.y < -WIN_HEIGHT)
		{
			//boid_list[i]->velocity.y= +0.8;
		 	if(flock_a->boid_list[i]->velocity.y<0)
				flock_a->boid_list[i]->velocity.y = -flock_a->boid_list[i]->velocity.y;
		}
		else{

		}
	/*Left bound of the window*/
		if(flock_a->boid_list[i]->position.x > WIN_WIDTH)
		{
			if(flock_a->boid_list[i]->velocity.x>0)
				flock_a->boid_list[i]->velocity.x = -flock_a->boid_list[i]->velocity.x;
		}
	/*Right bound of the window*/
		else if(flock_a->boid_list[i]->position.x < -WIN_WIDTH)
		{
			if(flock_a->boid_list[i]->velocity.x<0)
				flock_a->boid_list[i]->velocity.x = -flock_a->boid_list[i]->velocity.x;
		}
		else{

		}

		if(flock_a->boid_list[i]->position.z > WIN_DEPTH)
		{
			if(flock_a->boid_list[i]->velocity.z>0)
				flock_a->boid_list[i]->velocity.z = -flock_a->boid_list[i]->velocity.z;
		}
	/*Right bound of the window*/
		else if(flock_a->boid_list[i]->position.z< -WIN_DEPTH)
		{
			if(flock_a->boid_list[i]->velocity.z<0)
				flock_a->boid_list[i]->velocity.z = -flock_a->boid_list[i]->velocity.z;
		}
		else{

		}
	}
};
void calculatePositions(float frameTime){
	vector3 change_velo = {0,0,0};
	for(int i =0;i<flock_a->sizeOfFlock();i++){
		method1(i);
		method2(i);
		method3(i);
		flock_a->boid_list[i]->velocity.x = flock_a->boid_list[i]->velocity.x + tem.x + tem2.x + tem3.x;
		flock_a->boid_list[i]->velocity.y = flock_a->boid_list[i]->velocity.y + tem.y+ tem2.y + tem3.y;
		flock_a->boid_list[i]->velocity.z = flock_a->boid_list[i]->velocity.z + tem.z+ tem2.z + tem3.z;
		change_velo.x = change_velo.x + tem.x + tem2.x + tem3.x;
		change_velo.y = change_velo.y + tem.y + tem2.y + tem3.y;
		change_velo.z = change_velo.z + tem.z + tem2.z + tem3.z;
		if((flock_a->boid_list[i]->velocity.x>1)||(flock_a->boid_list[i]->velocity.x<-1)){
			flock_a->boid_list[i]->velocity.x = flock_a->boid_list[i]->velocity.x/2;
		}

		if((flock_a->boid_list[i]->velocity.y>1)||(flock_a->boid_list[i]->velocity.y<-1)){
			flock_a->boid_list[i]->velocity.y = flock_a->boid_list[i]->velocity.y/2;
		}
		if((flock_a->boid_list[i]->velocity.z>1)||(flock_a->boid_list[i]->velocity.z<-1)){
			flock_a->boid_list[i]->velocity.z = flock_a->boid_list[i]->velocity.z/2;
		}
		if((flock_a->boid_list[i]->velocity.x<0.3)&&(flock_a->boid_list[i]->velocity.x>-0.3)){
			flock_a->boid_list[i]->velocity.x = flock_a->boid_list[i]->velocity.x*2;
		}

		if((flock_a->boid_list[i]->velocity.y<0.3)&&(flock_a->boid_list[i]->velocity.y>-0.3)){
			flock_a->boid_list[i]->velocity.y = flock_a->boid_list[i]->velocity.y*2;
		}
		if((flock_a->boid_list[i]->velocity.z<0.3)&&(flock_a->boid_list[i]->velocity.z>-0.3)){
			flock_a->boid_list[i]->velocity.z = flock_a->boid_list[i]->velocity.z*2;
		}

	}
	float ene = 0;
	float angmom = 0;
	float force = 0;
	vector3 moment = {0,0,0};
	vector3 tempe = {0,0,0};
	
	obstacle();
	// for average energy
	for(int i = 0;i<flock_a->sizeOfFlock();i++){
		ene = ene + ((flock_a->boid_list[i]->velocity.x)*(flock_a->boid_list[i]->velocity.x)+(flock_a->boid_list[i]->velocity.y)*(flock_a->boid_list[i]->velocity.y)+(flock_a->boid_list[i]->velocity.z)*(flock_a->boid_list[i]->velocity.z))/2;
	}
	
	// for angular momentum
	// m r * v
	for(int i = 0;i<flock_a->sizeOfFlock();i++){
		tempe = Boids::crossProduct(flock_a->boid_list[i]->position,flock_a->boid_list[i]->velocity);
		moment.x+=tempe.x;
		moment.y+=tempe.y;
		moment.z+=tempe.z;
	}
	angmom = Boids::distance(moment,origin);
	force = Boids::distance(change_velo,origin);
	if(flock_a->sizeOfFlock()!= 0){
		angmom = angmom / flock_a->sizeOfFlock();
		ene = ene / flock_a->sizeOfFlock();
		force = force / (flock_a->sizeOfFlock()* frameTime);
		std::cout<< "average energy : "<<ene<<std::endl;	
		std::cout<< "average momentum : "<<angmom<<std::endl;
		std::cout<< "average force : "<<force<<std::endl;
		
	}
	for(int i = 0; i<flock_a->sizeOfFlock();i++){
			flock_a->boid_list[i]->position.x += flock_a->boid_list[i]->velocity.x*frameTime;
			flock_a->boid_list[i]->position.y += flock_a->boid_list[i]->velocity.y*frameTime;
			flock_a->boid_list[i]->position.z += flock_a->boid_list[i]->velocity.z*frameTime;
	}
}
void myIdle()
{
	/*
	* for the physics
	*/
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = timeSinceStart - oldTimeSinceStart;
	calculatePositions(0.01);
	myDisplay();
   	oldTimeSinceStart = timeSinceStart;
 
};
void myKeyboard(unsigned char key, int x, int y){
	switch(key)
	{
		case 'q': xrot+= 5; break;
		case 'a': xrot-=5; break;
		case 'w': yrot+=5; break;
		case 's': yrot-=5; break;
		case 'e': zrot+=5; break;
		case 'd':zrot-=5; break;
		case 'r':xrot = yrot = zrot = 0;scale=1;break;
		case 'p':scale+=1.2;break;
		case 'l':scale-=1.2;break;
		case 'b':flock_a->addBoid();break;
		default: break;
	};
}


int main(int argc, char **argv){


	srand (static_cast <unsigned> (time(0)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(1000,860);
	glutInitWindowPosition(0, 50);
	glutCreateWindow("Boids");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glClearColor(1.0f, 1.0f, 1.0f,0.0f);
	glViewport(0, 0, 860, 640);
	glutKeyboardFunc(myKeyboard);
	myInit();
	glutMainLoop();
}
