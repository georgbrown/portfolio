#include "Window.hpp"


// Viewing window is constructed from the scene data //
Window::Window(Scene scene){

	// Getting relevant scene data 
	origin = scene.getEyePos();
	view = scene.getViewDir();
	up = scene.getUpDir();
	fovv = scene.getFovv();
	Vec2i dims = scene.getEnvDims();
	
	d = 5; // arbitrary distance to window
	h = 2.f * d * tan(0.5f*0.01745329251*fovv);   // height of the viewing window
	aspect = dims.x / float(dims.y);   // aspect ratio
	w = h * aspect;   // width of viewing window

	// Computing the "u" vector as the cross product of "view" and "up", and then normalizing it
	u = Vec3f::cross(view,up);
	u = Vec3f::normalize(u);
	
	// Computing the "v" vector as the cross product of "u" and "view", and then normalizing it
	v = Vec3f::cross(u,view);
	v = Vec3f::normalize(v);
	
	// Computing the vector coordinates of the four corners of the viewing window
	ul = origin + d*view + (0.5f*h)*v - (0.5f*w)*u;
	ur = origin + d*view + (0.5f*h)*v + (0.5f*w)*u;
	ll = origin + d*view - (0.5f*h)*v - (0.5f*w)*u;
	lr = origin + d*view - (0.5f*h)*v + (0.5f*w)*u;

	// Computing step sizes along the horizontal and vertical directions
	dh = (1.f / float(dims.x -1.f) ) * ( ur - ul );
	dv = (1.f / float(dims.y -1.f) ) * ( ll - ul );
	
}


// Method which takes as input a pair of ints representing the pixel coordinates in an image
// and returns the corresponding mapping to 3d spatial coordinates in the viewing window plane
Vec3f Window::pixelToWindow(Vec2i pixelCoords){
	return ul + pixelCoords.x*dh + pixelCoords.y*dv;
}







