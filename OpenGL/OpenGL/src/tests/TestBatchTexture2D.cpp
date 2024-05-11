#include "TestBatchTexture2D.h"
#include "renderer.h"
#include "GL/glew.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test
{

	TestBatchTestTexture2D::TestBatchTestTexture2D()
		: m_TranslationA(200, 200, 0)
		, m_TranslationB(400, 200, 0)
		, m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
		, m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
		, m_R(0)
	{
		float positions[] = {
			-0.175f, -0.125f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.125f, -0.125f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f, 1.0f, 0.0f, 0.0f,
			 0.125f,  0.125f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f, 1.0f, 1.0f, 0.0f,
			-0.175f,  0.125f, 0.0f, 0.2f, 0.9f, 0.2f, 1.0f, 0.0f, 1.0f, 0.0f,

			 -0.25f,  -0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f, 0.0f, 0.0f, 1.0f,
			 -0.75f,  -0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f, 1.0f, 0.0f, 1.0f,
			 -0.75f,   0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f,
			 -0.25f,   0.25f, 0.0f, 0.9f, 0.9f, 0.2f, 1.0f, 0.0f, 1.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0, 
			4, 5, 6, 6, 7, 4
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 10 * 8 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shaders/BatchTexture.shader");
		m_Shader->Bind();
		/*m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		
		m_Texture = std::make_unique<Texture>("res/textures/qiya.jpg");
		m_Shader->SetUniform1i("u_Texture", 0);*/

		m_Texture1 = std::make_unique<Texture>("res/textures/qiya.jpg");
		m_Texture2 = std::make_unique<Texture>("res/textures/qiya2.jpg");


		m_VAO->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
	}

	TestBatchTestTexture2D::~TestBatchTestTexture2D()
	{

	}

	void TestBatchTestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestBatchTestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer render;

		m_Texture1->Bind(0);
		m_Texture2->Bind(1);

		m_Shader->Bind();
		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform2i("u_Textures", samplers);

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

#define OFFSET 0.05f
		static float increment = OFFSET;
		if (m_R > 1.0f) increment = -OFFSET;
		else if (m_R < 0) increment = OFFSET;

		m_R += increment;

	}

	void TestBatchTestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	}

}