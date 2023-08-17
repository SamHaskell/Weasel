#pragma once

#include "Weasel/Base/Defines.hpp"
#include "Weasel/Base/Logging.hpp"
#include "Weasel/Base/Asserts.hpp"
#include "Weasel/Base/Maths.hpp"

#define GLM_FORCE_RADIANS
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <array>