#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

<<<<<<< HEAD
#include "tests/TestClearColor.h"

=======
>>>>>>> 0487232a7ef003e23b77ada6c1e4c150b5fb945c
int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(960, 540, "Hello", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
<<<<<<< HEAD
		////           |----0----| |----1----| |----2----| |----3----|         
		//// Layout => x, y, u, v, x, y, u, v, x, y, u, v, x, y, u, v
		//float positions[] = {
		//	-50.0f, -50.0f, 0.0f, 0.0f, // 0
		//	 50.0f, -50.0f, 1.0f, 0.0f, // 1
		//	 50.0f,  50.0f, 1.0f, 1.0f, // 2
		//	-50.0f,  50.0f, 0.0f, 1.0f  // 3
		//};

		//unsigned int indices[] = {
		//	0, 1, 2,
		//	2, 3, 0
		//};

=======
		//           |----0----| |----1----| |----2----| |----3----|         
		// Layout => x, y, u, v, x, y, u, v, x, y, u, v, x, y, u, v
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, // 0
			 50.0f, -50.0f, 1.0f, 0.0f, // 1
			 50.0f,  50.0f, 1.0f, 1.0f, // 2
			-50.0f,  50.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

>>>>>>> 0487232a7ef003e23b77ada6c1e4c150b5fb945c
		// For images with transparency
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//VertexArray va;
		//VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push<float>(2);
		//layout.Push<float>(2);
		//va.AddBuffer(vb, layout);

		//IndexBuffer ib(indices, 6);

<<<<<<< HEAD
		//glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		////glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
=======
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

		//glm::mat4 mvp = proj * view * model;

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		//shader.SetUniformMat4f("u_MVP", mvp);
>>>>>>> 0487232a7ef003e23b77ada6c1e4c150b5fb945c

		////glm::mat4 mvp = proj * view * model;

		//Shader shader("res/shaders/Basic.shader");
		//shader.Bind();
		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		////shader.SetUniformMat4f("u_MVP", mvp);

		//Texture texture("res/textures/image.png");
		//texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

		//va.Unbind();
		//vb.Unbind();
		//ib.Unbind();
		//shader.Unbind();

		Renderer renderer;

		// ImGui initialization
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
		ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
		ImGui_ImplOpenGL3_Init("#version 100");

<<<<<<< HEAD
		//bool show_demo_window = true;
		//bool show_another_window = false;
		//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//glm::vec3 translationA(200, 200, 0);
		//glm::vec3 translationB(400, 200, 0);

		//float r = 0.0f;
		//float increment = 0.05f;

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");

=======
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		glm::vec3 translationA(200, 200, 0);
		glm::vec3 translationB(400, 200, 0);

		float r = 0.0f;
		float increment = 0.05f;
>>>>>>> 0487232a7ef003e23b77ada6c1e4c150b5fb945c
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

<<<<<<< HEAD
			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
=======
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * view * model;

				shader.Bind();
				shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}
			
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * view * model;
				
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}
>>>>>>> 0487232a7ef003e23b77ada6c1e4c150b5fb945c

				ImGui::Begin("Test");

				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();

				ImGui::End();
			}

			////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			//{
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			//	glm::mat4 mvp = proj * view * model;

			//	shader.Bind();
			//	shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			//	shader.SetUniformMat4f("u_MVP", mvp);
			//	renderer.Draw(va, ib, shader);
			//}
			//
			//{
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			//	glm::mat4 mvp = proj * view * model;
			//	
			//	shader.Bind();
			//	shader.SetUniformMat4f("u_MVP", mvp);
			//	renderer.Draw(va, ib, shader);
			//}

			//if (r > 1.0f) increment = -0.05f;
			//else if (r < 0.0f) increment = 0.05f;

			//r += increment;

			//{
			//	ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
			//	ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
			//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			//}

			////glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			{
				ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			}

			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}