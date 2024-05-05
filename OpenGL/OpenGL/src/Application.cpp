#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"



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

    /*glfwSwapInterval:设置缓冲区交换的时间间隔,设置垂直同步时,传入参数1代表每次都要等待下一帧缓冲渲染好了才能允许进行glfwSwapBuffers。传入参数0代表无限制,如果帧数太快渲染更不*/
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error !\n";

    std::cout << glGetString(GL_VERSION) << std::endl;
    /* Loop until the user closes the window */

	{
		float positions[] = {
				-0.5f,  0.5f,
				 0.5f, -0.5f,
				 0.5f,  0.5f,
				-0.5f, -0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			3, 0, 1
		};

		/*unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));*/

        VertexArray va;

		/*unsigned int buffer;
		GLCall(glGenBuffers(1, &buffer));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, positions, GL_STATIC_DRAW));*/
		VertexBuffer vb(positions, 8 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

		/*GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0));*/

		IndexBuffer ib(indices, 6);
		//unsigned int ibo;
		//GLCall(glGenBuffers(1, &ibo));
		//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
		//GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW));

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		//ShaderProgramSource source = parseShader("res/shaders/Basic.shader");

		//unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		//GLCall(glUseProgram(shader));

		//GLCall(unsigned int location = glGetUniformLocation(shader, "u_Color"));
		//ASSERT(location != -1);
		//GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		//GLCall(glUseProgram(0));
		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();
		//GLCall(glBindVertexArray(0));
		//GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));



		float r = 0;
#define OFFSET 0.05f
		float increment = OFFSET;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			// write code here
			//GLCall(glUseProgram(shader));
			//GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            va.Unbind();

			//GLCall(glBindVertexArray(vao));
			/*GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0));*/


			//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
            va.Bind();
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
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