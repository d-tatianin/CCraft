#pragma once
#include "glad/glad.h"

namespace CCraft
{
	class IndexBuffer
	{
	private:
		unsigned int m_RendererID;
	public:
		IndexBuffer(const void* data, unsigned int size);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;
	};
}
