#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"

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
Model *myModel;

glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
};

void Renderer::Init(int width, int height, float fovDegree)
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	myShader = new Shader("test.vert", "test.frag");
	myModel = new Model("lowe/lion.obj");

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

	//model = glm::rotate(model, glm::radians(35.0f), glm::vec3{ 0.0f,0.0f,1.0f });


	projFarClip = 100.0f;
	projNearClip = 0.1f;
	projFovDegree = fovDegree;
	projRatio = static_cast<float>(width) / static_cast<float>(height);
	SetPerspective(projFovDegree, projRatio, projNearClip, projFarClip);

	myShader->Use();
	myShader->SetMat4("model", glm::mat4{ 1.0f });
	myShader->SetMat4("projection", projection);

	myShader->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	myShader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	myShader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	myShader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	myShader->SetVec3("pointLights[0].position", pointLightPositions[0]);
	myShader->SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	myShader->SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	myShader->SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	myShader->SetFloat("pointLights[0].constant", 1.0f);
	myShader->SetFloat("pointLights[0].linear", 0.09);
	myShader->SetFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	myShader->SetVec3("pointLights[1].position", pointLightPositions[1]);
	myShader->SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	myShader->SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	myShader->SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	myShader->SetFloat("pointLights[1].constant", 1.0f);
	myShader->SetFloat("pointLights[1].linear", 0.09);
	myShader->SetFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	myShader->SetVec3("pointLights[2].position", pointLightPositions[2]);
	myShader->SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	myShader->SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	myShader->SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	myShader->SetFloat("pointLights[2].constant", 1.0f);
	myShader->SetFloat("pointLights[2].linear", 0.09);
	myShader->SetFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	myShader->SetVec3("pointLights[3].position", pointLightPositions[3]);
	myShader->SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	myShader->SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	myShader->SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	myShader->SetFloat("pointLights[3].constant", 1.0f);
	myShader->SetFloat("pointLights[3].linear", 0.09);
	myShader->SetFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	myShader->SetVec3("spotLight.position", 0.2f,0.2f,0.2f);
	myShader->SetVec3("spotLight.direction", 1.0f,0.0f,0.0f);
	myShader->SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	myShader->SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	myShader->SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	myShader->SetFloat("spotLight.constant", 1.0f);
	myShader->SetFloat("spotLight.linear", 0.09);
	myShader->SetFloat("spotLight.quadratic", 0.032);
	myShader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	myShader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	
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
	
	model = glm::mat4{ 1.0f };
	//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 3.0f), glm::vec3{ 0.0f,0.0f,1.0f });
	//myShader->SetMat4("model", model);

	myShader->Use();
	myShader->SetMat4("view", viewMatrix);

	myModel->Draw(*myShader);

	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	
}

Renderer::~Renderer()
{

}