#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.5f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.5f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.5f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.5f
};

unsigned int VBO, VAO;
glm::mat4 model{ 1.0f };
Shader *myShader;

void Renderer::Init()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	myShader = new Shader("test.vert", "test.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	model = glm::rotate(model, glm::radians(35.0f), glm::vec3{ 0.0f,0.0f,1.0f });


	projFarClip = 100.0f;
	projNearClip = 0.1f;
	projFovDegree = 45.0f;
	projRatio = 1200.0f / 1000.0f;
	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);

	myShader->Use();
	myShader->SetMat4("model", model);
	myShader->SetMat4("projection", projection);
	
}

void Renderer::SetPerspective(float FovDegree, float ratio, float nearClip, float farClip)
{
	projection = glm::mat4{ 1.0f };
	projection = glm::perspective(glm::radians(FovDegree), ratio, nearClip, farClip);
	myShader->SetMat4("projection", projection);
}

void Renderer::SetAspectRatio(int w, int h)
{
	projRatio = static_cast<float>(w) / static_cast<float>(h);
	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);
}

void Renderer::Render(const glm::mat4 &viewMatrix)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	myShader->Use();
	myShader->SetMat4("view", viewMatrix);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
}

Renderer::~Renderer()
{

}