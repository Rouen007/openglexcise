#pragma once

class VertexBuffer
{
protected:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer() = default;
	virtual void SetSubBuffer(const void* data, unsigned int size) { __debugbreak(); }
	virtual ~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

class DynamicVertexBuffer : public VertexBuffer
{
public:
	DynamicVertexBuffer(unsigned int size);
	~DynamicVertexBuffer();
	void SetSubBuffer(const void* data, unsigned int size) override;
};
