#pragma once
#include "Test.h"

namespace test {
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		virtual ~TestClearColor();
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}