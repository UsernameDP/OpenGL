#pragma once 
#include "GLBindableInterface.hpp"

namespace GLCore::Extension::Primitives {

	class GLDetachableInterface {
	public:
		virtual void detach() = 0;
	};

}