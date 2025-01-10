#pragma once
#include <vector>
#include <memory>
#include "VertexBufferLayout.h"

namespace rendell
{
	class VertexBuffer
	{
	protected:
		VertexBuffer(std::vector<float>&& data);

	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		const std::vector<float>& getData() const;
		int getStride() const;
		const std::vector<VertexBufferLayout>& getLayouts() const;
		void setLayouts(const std::vector<VertexBufferLayout>& layouts);

	protected:
		void calculateOffsetsAndStride();

		std::vector<float> _data;
		int _stride = 0;
		std::vector<VertexBufferLayout> _layouts{};

	};

	typedef std::shared_ptr<VertexBuffer> VertexBufferSharedPtr;
}