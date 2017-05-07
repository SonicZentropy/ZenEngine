#pragma once

using PrecisionType = float;

// Including SDKDDKVer.h defines the highest available Windows platform.
#include <SDKDDKVer.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <spdlog/spdlog.h>
//#include <SFML/System/Vector3.hpp>
//#include <SFML/System/Vector2.hpp>
#include "Source/Core/common/math/Vector2.h"
#include "Source/Core/common/math/Vector3.h"

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using std::vector;
//using Vector2 = sf::Vector2<float>;
//using Vector3 = sf::Vector3<float>;
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

#include "Source/Core/common/logging/ZLog.h"