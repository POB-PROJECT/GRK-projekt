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
	Texture bottomTexture("./res/bottomTexture.jpg");
	Texture rockTexture("./res/rockTexture.jpg");
	Texture bubbleTexture("./res/bubbleTexture.jpg");


	Mesh mesh2("./res/monkey3.obj");
	Mesh mesh3("./res/Rock.obj");
	Mesh bottomSandMesh("./res/untitled.obj");
	Mesh bubbleMesh("./res/bubble.obj");

	Transform transform;
	Transform transform1;
	Transform bottomTransform;
	Transform bubbleTransform;
	Camera camera(glm::vec3(0, 0, -10), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	float counter = 0.0f;
	float bubbleCounter = -2.0f;
	float rotatePosition = 3.0f;
	float rangePosition = 4.0f;
	transform.GetRot().y = 1.86f;
	transform1.GetPos().x = -5.7f;
	transform1.GetPos().y = -1.1f;
	bottomTransform.GetPos().y = -5.0f;
	bottomTransform.GetScale().x = 1.7f;
	bubbleTransform.GetPos().x = 5.0f;
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
		std::cout << "POS Y: " << bubbleTransform.GetPos().y << std::endl;
		transform.GetPos().z = cosCounter;

		if (bubbleTransform.GetPos().y > 10.0f)
		{
			bubbleCounter = -2.0f;
		}
		bubbleTransform.GetPos().y = bubbleCounter *4;

		//transform.GetRot().x = counter * 3;
		//transform.GetRot().y = counter * 3;
		
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();
		shader.Update(transform1, camera);
		rockTexture.Bind(0);
		mesh3.Draw();
		shader.Update(bottomTransform, camera);
		bottomTexture.Bind(0);
		bottomSandMesh.Draw();
		shader.Update(bubbleTransform, camera);
		bubbleTexture.Bind(0);
		bubbleMesh.Draw();

		display.Update();
		counter += 0.01f;
		bubbleCounter += 0.01f;
	}
	return 0;
}