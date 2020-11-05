#pragma once
#include "scene.h"
#include <math.h>

class mandelbrotset : public Scene
{
public:
	
	mandelbrotset();
	void Init();
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	
	unsigned int TextureDesine(int width, int height);
	~mandelbrotset(void);
	inline float getZoom() { return zoom; }
	inline void decPower() { power = power > 2 ? --power : 2; }
	inline void incPower() { ++power; }
	inline void decColors() { colors = colors > 2 ? colors>>1 : 2; }
	inline void incColors() { colors <<= 1; }
	inline void doZoom(double yoffset) { zoom = yoffset > 0 ? zoom * pow(0.5, yoffset) : zoom * pow(2, -yoffset); }

	void updatePressedPos(double xpos, double ypos);
	void setNewOffset(double x, double y);
	void UpdatePosition( float xpos, float ypos);
private:
	float x, y;
	unsigned int power;
	unsigned int colors;
	float zoom;
	float old_x;
	float old_y;
	float offset_x;
	float offset_y;
};

