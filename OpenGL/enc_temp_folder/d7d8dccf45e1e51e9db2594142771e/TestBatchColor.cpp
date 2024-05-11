#include "TestBatchColor.h"
#include "renderer.h"
#include "GL/glew.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test
{

	TestBatchColor::TestBatchColor()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
		, m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
		, m_R(0)
	{
		float positions[] = {
			-0.175f, -0.125f, 0.0f, 0.2f, 0.9f, 0.2f,1.0f,
			 0.125f, -0.125f, 0.0f, 0.2f, 0.9f, 0.2f,1.0f,
			 0.125f,  0.125f, 0.0f, 0.2f, 0.9f, 0.2f,1.0f,
			-0.175f,  0.125f, 0.0f, 0.2f, 0.9f, 0.2f,1.0f,

			 -0.25f, -0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f,
			 -0.75f, -0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f,
			 -0.75f,  0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f,
			 -0.25f,  0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 7 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/BatchColor.shader");
		m_Shader->Bind();
		// m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		m_VAO->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
	}

	TestBatchColor::~TestBatchColor()
	{

	}

	void TestBatchColor::OnUpdate(float deltaTime)
	{

	}

	void TestBatchColor::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer render;

		m_Shader->Bind();
		// m_Shader->SetUniform4f("u_Color", 0.3f, m_R, 0.8f, 1.0f);

		{
			render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

	}

	void TestBatchColor::OnImGuiRender()
	{
	}

}