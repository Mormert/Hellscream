#pragma once

#include <glm/glm.hpp>

class Renderer
{
public:
	void Init();

	// Render with camera's view matrix
	void Render(const glm::mat4 &viewMatrix);

	void SetPerspective(float FovDegree, float ratio, float nearClip, float farClip);
	void SetAspectRatio(int w, int h);

	~Renderer();

private:
	glm::mat4 projection;

	float projRatio;
	float projNearClip;
	float projFarClip;
	float projFovDegree;
};

