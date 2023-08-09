#pragma once
//This file is neccesary because .hpp within ./Core aren't just being used in OpenGL-Core but also OpenGL-Examples where a precompile header doesn't exist

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>