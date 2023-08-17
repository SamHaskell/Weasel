project(
    Weasel
    VERSION 0.1
    DESCRIPTION "Weasel Engine"
    LANGUAGES C CXX
)

################### VENDOR ###################

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

set(
    VENDOR_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/assimp/include
    ${PROJECT_SOURCE_DIR}/vendor/glm
    ${PROJECT_SOURCE_DIR}/vendor/imgui
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends
    ${PROJECT_SOURCE_DIR}/vendor/stb
)

set(
    VENDOR_SOURCES
    ${PROJECT_SOURCE_DIR}/vendor/glad/src/glad.c
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    ${PROJECT_SOURCE_DIR}/vendor/stb/stb_image_impl.cpp
)

set(
    VENDOR_HEADERS
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.h
    ${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.h
)

################### LIBRARY ##################

set(
    LOCAL_HEADERS
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Defines.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Logging.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Asserts.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Maths.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Base.hpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Entrypoint.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Application.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Window.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/AppStack.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Layer.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Transform.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/GameObject.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Scene.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Model.hpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Input/Keys.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Input/Input.hpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Components/MeshInstance.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Components/VirtualCamera.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Components/EditorCameraController.hpp
    
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Events/Events.hpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/RenderTypes.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/RenderUtils.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Buffers.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Framebuffer.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Cameras.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Lights.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Renderer.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Mesh.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Material.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Shader.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Textures.hpp
)

set(
    LOCAL_SOURCES
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Logging.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Base/Maths.cpp
    
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Application.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Window.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/AppStack.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Transform.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/GameObject.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Scene.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Model.cpp
    
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Input/Input.cpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Components/MeshInstance.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Components/VirtualCamera.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Components/EditorCameraController.cpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Events/Events.cpp

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/RenderUtils.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Buffers.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Framebuffer.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Cameras.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Lights.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Mesh.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Material.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Shader.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Graphics/Textures.cpp
    )

add_library(
    ${PROJECT_NAME} STATIC
    ${LOCAL_SOURCES}
    ${LOCAL_HEADERS}
    ${VENDOR_SOURCES}
    ${VENDOR_HEADERS}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/source
    ${VENDOR_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    glfw ${GLFW_LIBRARIES}
    assimp
)

target_compile_features(
    ${PROJECT_NAME} PUBLIC
    cxx_std_17
)