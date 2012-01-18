#pragma once 

#include "Defines.h"
#include "CHeightMap.h"

struct tVector3
{			
	tVector3() {}
	tVector3 (float new_x, float new_y, float new_z)
	{ x = new_x; y = new_y; z = new_z; }
	// overload + operator
	tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
	// overload - operator
	tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
	// overload * operator
	tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
	// overload / operator
	tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}
	
	float x, y, z;	
};

class CCamera 
{
public:
	CCamera(void);
	~CCamera(void);

	tVector3 mPos;	
	tVector3 mView;		
	tVector3 mUp;			

	void Strafe_Camera(float speed, CHeightMap* theMap);

	void Mouse_Move(int wndWidth, int wndHeight, bool fullscreenflag);
	void Move_Camera(float speed, CHeightMap* theMap);
	void Rotate_View(float speed);
	void Position_Camera(float pos_x, float pos_y,float pos_z,
		 				 float view_x, float view_y, float view_z,
						 float up_x,   float up_y,   float up_z);
};