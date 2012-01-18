#include "CCamera.h"

CCamera::CCamera(void)
{
}

CCamera::~CCamera(void)
{
}


void CCamera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							  float view_x, float view_y, float view_z,
							  float up_x,   float up_y,   float up_z)
{
	mPos	= tVector3(pos_x,  pos_y,  pos_z ); // set position
	mView	= tVector3(view_x, view_y, view_z); // set view
	mUp		= tVector3(up_x,   up_y,   up_z  ); // set the up vector	
}


void CCamera::Move_Camera(float speed, CHeightMap* theMap)
{
	tVector3 vVector = mView - mPos;	// Get the view vector
	
	// forward positive cameraspeed and backward negative -cameraspeed.
	mPos.x  = mPos.x  + vVector.x * speed;
	mPos.z  = mPos.z  + vVector.z * speed;
	if ( mPos.x + MAP_SIZE/2 < 0 )
		mPos.x = -MAP_SIZE/2;
	if (  mPos.z + MAP_SIZE/2 < 0 )
		 mPos.z = -MAP_SIZE/2;

	mPos.y  = (float)theMap->Height(int(mPos.x + MAP_SIZE/2.0f), int(mPos.z + MAP_SIZE/2.0f)) - HM_DISPLACEMENT; 
	
	mView.x = mView.x + vVector.x * speed;
	mView.z = mView.z + vVector.z * speed;

}

void CCamera::Strafe_Camera(float speed, CHeightMap* theMap)
{
	tVector3 vVector = mView - mPos;	
	tVector3 vOrthoVector;

	vOrthoVector.x = -vVector.z;
	vOrthoVector.z =  vVector.x;

	// left positive cameraspeed and right negative -cameraspeed.
	mPos.x  = mPos.x  + vOrthoVector.x * speed;
	if ( mPos.x > MAP_SIZE / 2)
		mPos.x = MAP_SIZE/2;
	if ( mPos.x < -MAP_SIZE / 2)
		mPos.x = MAP_SIZE/2;

	mPos.z  = mPos.z  + vOrthoVector.z * speed;
	if ( mPos.x + MAP_SIZE/2 < 0 )
		mPos.x = -MAP_SIZE/2;
	if (  mPos.z + MAP_SIZE/2 < 0 )
		 mPos.z = -MAP_SIZE/2;

	mPos.y  = (float)theMap->Height(int(mPos.x + MAP_SIZE/2.0f), int(mPos.z + MAP_SIZE/2.0f)) - HM_DISPLACEMENT; 

	mView.x = mView.x + vOrthoVector.x * speed;
	mView.z = mView.z + vOrthoVector.z * speed;
	//mView.y = mPos.y  + vOrthoVector.y * speed;
}


void CCamera::Mouse_Move(int wndWidth, int wndHeight, bool fullscreenflag)
{
	if (fullscreenflag)
		wndWidth = (long)GetSystemMetrics(SM_CXSCREEN);
	if (fullscreenflag)
		wndHeight = (long)GetSystemMetrics(SM_CYSCREEN);
	

	POINT mousePos;	
	int mid_x = wndWidth  >> 1;	
	int mid_y = wndHeight >> 1;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;							
	
	GetCursorPos(&mousePos);
	
	if( (mousePos.x == mid_x) && (mousePos.y == mid_y) ) return;

	SetCursorPos(mid_x, mid_y);		

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angle_y = (float)( (mid_x - mousePos.x) ) / 1000;		
	angle_z = (float)( (mid_y - mousePos.y) ) / 1000;

	// The higher the value is the faster the camera looks around.
	mView.y += angle_z * 100;

	// limit the rotation around the x-axis
	if((mView.y - mPos.y) > 100)  mView.y = mPos.y + 100;
	if((mView.y - mPos.y) <-100)  mView.y = mPos.y - 100;
	
	Rotate_View(-angle_y); // Rotate
}

void CCamera::Rotate_View(float speed)
{
	tVector3 vVector = mView - mPos;	// Get the view vector
	mView.z = (float)(mPos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	mView.x = (float)(mPos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}
