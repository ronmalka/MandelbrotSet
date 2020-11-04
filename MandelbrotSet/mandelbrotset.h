#pragma once
#include "scene.h"

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
	inline void decPower() { power = power > 2 ? --power : 2; }
	inline void incPower() { ++power; }

	void UpdatePosition( float xpos, float ypos);
private:
	float x, y;
	unsigned int power;
};

