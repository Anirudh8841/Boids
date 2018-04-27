#include <stdlib.h>
#include <vector>
#define WIN_WIDTH  2
#define WIN_HEIGHT  2
#define WIN_DEPTH  2

struct vector3{
    float x,y,z;
};

class Boids{
    public:
        vector3 position;
        vector3 velocity;
    public:
        Boids(vector3 vec,vector3 pos);
        Boids(vector3 vec);
        static vector3 normalize(vector3 vec);
        static vector3 crossProduct(vector3 one,vector3 two);
	    static float distance(vector3 pos1,vector3 pos2);
        
};
