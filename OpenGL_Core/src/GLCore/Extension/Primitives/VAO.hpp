#pragma once
#include "GLBindableInterface.hpp"

namespace GLCore::Extension::Primitives {
	class VAO : public GLBindableInterface {
	public:
		VAO();
		virtual ~VAO() override;

		void bind() override;
		void unbind() override;
		void destroy() override;
	};
}