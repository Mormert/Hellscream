#include "Engine.h"

#include "InputManager.h"
#include "CameraController.h"

#include <GLFW/glfw3.h>

#include <iostream>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Engine::Start()
{
	renderer = new Renderer();
	renderWindow = new Window(2000, 2000, "Hellscream", InputManager::ResizeWindowEvent);

	InputManager::AddResizeWindowCallback(renderer, &Renderer::SetAspectRatio);

	renderWindow->FpsModeCursor(true);

	InputManager::LinkWindow(renderWindow);

	camera = new Camera();
	renderer->Init(2000, 2000, 45.0f);
}

void Engine::Run()
{
	running = true;
	Loop();
}

void Engine::Loop()
{
	while (running)
	{
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		

		Update(deltaTime);
		Render();

		CollectInput();

		renderWindow->SwapBuffers();
		
		running = !renderWindow->ShouldClose();
	}
	Close();
}

void Engine::CollectInput()
{
	InputManager::FlushKeyPressArray();
	InputManager::UpdateLastMousePosition();
	renderWindow->PollEvents();
}

void Engine::Update(float dt)
{
	CameraController::MoveCameraBasedOnInput(*camera, dt);
	


	
}

void Engine::Render()
{
	renderer->Render(camera->GetViewMatrix());
}

void Engine::Stop()
{
	running = false;
}

void Engine::Close()
{
	delete renderWindow;
	delete renderer;
	delete camera;
}