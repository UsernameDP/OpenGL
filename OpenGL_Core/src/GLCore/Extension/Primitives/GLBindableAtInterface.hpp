#pragma once 
#include "GLBindableInterface.hpp"

namespace GLCore::Extension::Primitives {

	class GLBindableAtInterface : public GLBindableAtInterface {

	public:
		GLBindableAtInterface() = default;
		virtual ~GLBindableAtInterface() override = default;

		virtual void bindAt(const GLuint& loc) = 0;
	};

}