#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

int main(int argc, char** argv)
{
	Display display(1024, 760, "Ryba Here!");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	
	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
		Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5,1.0)),
		Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0,0.0))
	};
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Transform transform;

	float counter = 0.0f;
	while (!display.IsClosed()){
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.GetPos().x = sinCounter;
		transform.GetRot().z = counter/3;
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform);
		mesh.Draw();

		display.Update();
		counter += 0.01f;
	}
	return 0;
}