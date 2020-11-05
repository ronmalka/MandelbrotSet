#include "mandelbrotset.h"
#include <iostream>
#include "GL/glew.h"

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

mandelbrotset::mandelbrotset() : Scene()
{
	power = 2;
	colors = 128;
	zoom = 1.0;
	offset_x = 0;
	offset_y = 0;
	old_x = 0;
	old_y = 0;
}

//mandelbrotset::mandelbrotset(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{ 	
//}

void mandelbrotset::Init()
{		
	unsigned int texIDs[3] = { 0 , 1, 0};
	unsigned int slots[3] = { 0 , 1, 0 };
	
	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/myShader");
	AddTexture("../res/textures/pal.png",2);
	//TextureDesine(840, 840);

	AddMaterial(texIDs,slots, 1);
	
	AddShape(Plane, -1, TRIANGLES);
	SetShapeShader(0, 1);
}

void mandelbrotset::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{	
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	if (shapes[pickedShape]->GetMaterial() >= 0 && !materials.empty())
		BindMaterial(s, shapes[pickedShape]->GetMaterial());
	//textures[0]->Bind(0);
	s->Bind();
	if (shaderIndx != 1)
	{
		s->SetUniformMat4f("MVP", MVP);
		s->SetUniformMat4f("Normal", Model);
	}
	else
	{
		s->SetUniformMat4f("MVP", glm::mat4(1));
		s->SetUniformMat4f("Normal", glm::mat4(1));
	}
	//s->SetUniform1i("sampler1", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(0));
	if(shaderIndx!=1)
		s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));
	s->SetUniform1ui("power", power);
	s->SetUniform1ui("colors",colors);
	s->SetUniform1f("zoom", zoom);
	s->SetUniform1f("offset_x", offset_x);
	s->SetUniform1f("offset_y", offset_y);
	s->Unbind();
}

void mandelbrotset::setNewOffset(double xpos, double ypos) {
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	offset_x += (xpos - old_x)/viewport[2];
	offset_y += (old_y - ypos)/viewport[3];
}

void mandelbrotset::updatePressedPos(double xpos, double ypos){
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	old_x = xpos;
	old_y = ypos;
}

void mandelbrotset::UpdatePosition(float xpos,  float ypos)
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	x = xpos / viewport[2];
	y = 1 - ypos / viewport[3];
}

void mandelbrotset::WhenRotate()
{
}

void mandelbrotset::WhenTranslate()
{
}


void mandelbrotset::Motion()
{
	if(isActive)
	{
	}
}

unsigned int mandelbrotset::TextureDesine(int width, int height)
{
	unsigned char* data = new unsigned char[width * height * 4];
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			data[(i * height + j) * 4] = (i + j) % 256;
			data[(i * height + j) * 4 + 1] = (i + j * 2) % 256;
			data[(i * height + j) * 4 + 2] = (i * 2 + j) % 256;
			data[(i * height + j) * 4 + 3] = (i * 3 + j) % 256;
		}
	}
	textures.push_back(new Texture(width, height));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save 
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
	return(textures.size() - 1);
}

mandelbrotset::~mandelbrotset(void)
{

}
