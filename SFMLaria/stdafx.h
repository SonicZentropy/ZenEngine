#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.
#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Matrix4 = glm::mat4;
using glm::translate;
using glm::scale;
using glm::rotate;
using glm::lookAt;
using glm::mat4;
using glm::perspective;
using glm::radians;
using glm::vec2;
using glm::vec3;
using glm::vec4;
