#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

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
	Camera camera(glm::vec3(0, 0, -5), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	float counter = 0.0f;
	while (!display.IsClosed()){
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinCounter;
		transform.GetPos().z = cosCounter;
		transform.GetRot().x = counter * 3;
		transform.GetRot().y = counter * 3;
		transform.GetRot().z = counter * 3;
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