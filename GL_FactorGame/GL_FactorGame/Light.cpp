#include "Light.h"

Light::Light(void)
{
	//Light Direction
	Light_Direction = vec4(0.0, 0.0, 0.0, 0.0);
	Light_Brightness = 1;
	Light_Radius = 0.75f;
}


Light::~Light(void)
{
}

void Light::Initialize(int rendering_program)
{
	lightDir_location = glGetUniformLocation(rendering_program,"Light_Direction");
	lightBrightness_location = glGetUniformLocation(rendering_program,"Light_Brightness");
	lightRadius_location = glGetUniformLocation(rendering_program, "Light_Radius");
}

void Light::Update(float CurrentTime)
{
	//Light_Brightness = sin(CurrentTime * 30) * 0.5f + 0.5f;

	glUniform4f(lightDir_location,Light_Direction[0],Light_Direction[1],Light_Direction[2],Light_Direction[3]);
	glUniform1f(lightBrightness_location, Light_Brightness);
	glUniform1f(lightRadius_location, Light_Radius);
}
