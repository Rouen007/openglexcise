#pragma once
#include "Test.h"
#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

namespace test {
	class TestBatchColor : public Test
	{
	public:
		TestBatchColor();
		virtual ~TestBatchColor();
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr < VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		glm::mat4 m_Proj, m_View;
		float m_R;
	};
}