#include "TestCube.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	TestCube::TestCube() :
		m_Proj(glm::perspective(glm::radians(60.0f), 960.0f / 540.0f, 0.1f, 1000.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3))),
		m_RotationA(0, 0, 0), m_RotationB(0, 0, 0),
		m_DeltaTime(0)
	{
		float positions[] = {
			 0.5,  0.5,  0.5,  1.0f,  0.0f,  0.0f,
			 0.5,  0.5, -0.5,  0.0f,  1.0f,  0.0f,
			 0.5, -0.5,  0.5,  0.0f,  0.0f,  1.0f,
			 0.5, -0.5, -0.5,  1.0f,  1.0f,  0.0f,
			-0.5,  0.5,  0.5,  1.0f,  0.0f,  1.0f,
			-0.5,  0.5, -0.5,  0.0f,  1.0f,  1.0f,
			-0.5, -0.5,  0.5,  1.0f,  0.5f,  0.0f,
			-0.5, -0.5, -0.5,  1.0f,  0.0f,  0.5f,
		};

		unsigned int indices[] = {
			0, 3, 1,
			0, 2, 3,
			2, 7, 3,
			2, 6, 7,
			0, 6, 2,
			0, 4, 6,
			4, 5, 7,
			7, 6, 4,
			7, 1, 3,
			7, 5, 1,
			4, 0, 1,
			1, 5, 4
		};

		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

		//glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
		//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 6 * sizeof(float));
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12 * 3);

		m_Shader = std::make_unique<Shader>("res/shaders/Cube.shader");
		m_Shader->Bind();
	}

	TestCube::~TestCube()
	{
		GLCall(glDisable(GL_DEPTH_TEST));
	}

	void TestCube::OnUpdate(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}

	void TestCube::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer;

		m_View = m_Camera->GetViewMatrix();

		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(m_RotationA.x), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(m_RotationA.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(m_RotationA.z), glm::vec3(0, 0, 1));
			glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-5.0f, 1.0f, -5.0f));
			model = glm::rotate(model, glm::radians(m_RotationB.x), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(m_RotationB.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(m_RotationB.z), glm::vec3(0, 0, 1));
			glm::mat4 mvp = m_Proj * m_View * model;

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestCube::OnImGuiRender()
	{
		ImGui::SliderFloat3("Cube Rotation A", &m_RotationA.x, 0.0f, 360.0f);
		ImGui::SliderFloat3("Cube Rotation B", &m_RotationB.x, 0.0f, 360.0f);
		ImGui::Text("DeltaTime: %f", m_DeltaTime);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	Camera& TestCube::GetCamera()
	{
		return *m_Camera;
	}
}