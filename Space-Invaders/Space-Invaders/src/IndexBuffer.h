#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	// Use "inline" keyword to place function into code, rather than calling it (no function call)
	// Also has the benefit of declaring and defining a function in a header file
	inline unsigned int GetCount() const { return m_Count; }
};