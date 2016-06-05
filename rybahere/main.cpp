#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 1440
#define HEIGHT 900

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "Ryba Here!");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	
	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0.0))
	};

	unsigned int indices[] = { 0, 1, 2 };
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Mesh mesh2("./res/monkey3.obj");
	Transform transform;
	Camera camera(glm::vec3(0, 0, -10), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	float counter = 0.0f;
	float rotatePosition = 3.0f;
	float rangePosition = 4.0f;
	transform.GetRot().y = 1.86f;
	while (!display.IsClosed()){
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		if (transform.GetPos().x > -rotatePosition && transform.GetPos().x < rotatePosition)
		{
			transform.GetPos().x = sinCounter * rangePosition;
		}
		if (transform.GetPos().x >= rotatePosition)
		{
			transform.GetRot().y = counter * 2;
			transform.GetPos().x = sinCounter * rangePosition;
		}
		if (transform.GetPos().x <= -rotatePosition)
		{
			transform.GetRot().y = counter * -2;
			transform.GetPos().x = sinCounter * rangePosition;
		}
		transform.GetRot().z = sinCounter/4;
		std::cout << "POS X: " << transform.GetPos().x << std::endl;
		transform.GetPos().z = cosCounter;


		//transform.GetRot().x = counter * 3;
		//transform.GetRot().y = counter * 3;
		
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh.Draw();
		mesh2.Draw();

		display.Update();
		counter += 0.01f;
	}
	return 0;
}