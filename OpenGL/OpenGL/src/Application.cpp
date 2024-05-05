#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*glfwSwapInterval:���û�����������ʱ����,���ô�ֱͬ��ʱ,�������1����ÿ�ζ�Ҫ�ȴ���һ֡������Ⱦ���˲����������glfwSwapBuffers���������0����������,���֡��̫����Ⱦ����*/
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error !\n";

    std::cout << glGetString(GL_VERSION) << std::endl;
    /* Loop until the user closes the window */

	{
		float positions[] = {
				-0.5f, -0.5f, 0.0f, 0.0f,
				 0.5f, -0.5f, 1.0f, 0.0f,
				 0.5f,  0.5f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
		VertexBuffer vb(positions, 4*4 * sizeof(float));
        VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
        va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		Texture texture("res/textures/qiya.jpg");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);


		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer render;

		float r = 0;
#define OFFSET 0.05f
		float increment = OFFSET;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			render.Clear();

			// write code here
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			render.Draw(va, ib, shader);

			//
			if (r > 1.0f) increment = -OFFSET;
			else if (r < 0) increment = OFFSET;

			r += increment;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		//glDeleteShader(shader);
	}

    glfwTerminate();
    return 0;
}