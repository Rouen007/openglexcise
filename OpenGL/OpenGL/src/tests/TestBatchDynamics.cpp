#include "TestBatchDynamics.h"
#include "renderer.h"
#include "GL/glew.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>


namespace test
{
	struct Vec3
	{
		float x, y, z;
	};
	struct Vec2
	{
		float x, y;
	};
	struct Vec4
	{
		float x, y, z, w;
	};
	struct Vertex
	{
		Vec3 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TexID;
	};

	TestBatchDynamics::TestBatchDynamics()
	{
		
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0, 
			4, 5, 6, 6, 7, 4
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		
		m_VertexBuffer = std::make_unique<DynamicVertexBuffer>(1000 * sizeof(Vertex));

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
		
		m_Texture1 = std::make_unique<Texture>("res/textures/qiya.jpg");
		m_Texture2 = std::make_unique<Texture>("res/textures/qiya2.jpg");

		m_VAO->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
	}

	TestBatchDynamics::~TestBatchDynamics()
	{

	}

	void TestBatchDynamics::OnUpdate(float deltaTime)
	{

	}

	static std::array<Vertex, 4> CreateQuad(float x, float y, float texID)
	{
		float size = 0.3f;
		Vertex v0;
		v0.Position = { x, y, 0.0f };
		v0.Color = { 0.2f, 0.9f, 0.2f, 1.0f };
		v0.TexCoord = { 0.0f, 0.0f };
		v0.TexID = texID;

		Vertex v1;
		v1.Position = { x+size, y, 0.0f };
		v1.Color = { 0.2f, 0.9f, 0.2f, 1.0f };
		v1.TexCoord = { 1.0f, 0.0f };
		v1.TexID = texID;


		Vertex v2;
		v2.Position = { x+size, y+size, 0.0f };
		v2.Color = { 0.2f, 0.9f, 0.2f, 1.0f };
		v2.TexCoord = { 1.0f, 1.0f };
		v2.TexID = texID;


		Vertex v3;
		v3.Position = { x, y+size, 0.0f };
		v3.Color = { 0.2f, 0.9f, 0.2f, 1.0f };
		v3.TexCoord = { 0.0f, 1.0f };
		v3.TexID = texID;

		return { v0, v1, v2, v3 };
	}

	void TestBatchDynamics::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer render;

		m_Texture1->Bind(0);
		m_Texture2->Bind(1);

		auto q0 = CreateQuad(m_TranslationA[0], m_TranslationA[1], 0.0f);
		auto q1 = CreateQuad(-0.25f, -0.25f, 1.0f);

		Vertex vertices[8];
		memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
		memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

		m_VertexBuffer->Bind();
		m_VertexBuffer->SetSubBuffer(vertices, sizeof(vertices));

		m_Shader->Bind();
		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform2Textures("u_Textures", samplers);

		{
			render.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

	}

	void TestBatchDynamics::OnImGuiRender()
	{
		ImGui::DragFloat2("Translation of image 1", m_TranslationA, 0.1f);            
	}

}