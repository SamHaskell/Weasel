project(
    Wigner
    VERSION 0.1
    DESCRIPTION "Wigner Engine"
    LANGUAGES CXX
)

##############################################
################### VENDOR ###################
##############################################

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)



##############################################
################### LIBRARY ##################
##############################################

set(
    LOCAL_HEADERS

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Entrypoint.hpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Application.hpp
)

set(
    LOCAL_SOURCES

    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Entrypoint.cpp
    ${PROJECT_SOURCE_DIR}/source/${PROJECT_NAME}/Core/Application.cpp
)

add_library(
    ${PROJECT_NAME} STATIC
    ${LOCAL_SOURCES}
    ${LOCAL_HEADERS}
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/source
    ${PROJECT_SOURCE_DIR}/vendor/glfw/include
    ${PROJECT_SOURCE_DIR}/vendor/glm
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    # glfw ${GLFW_LIBRARIES}
    # glad
)

target_compile_features(
    ${PROJECT_NAME} PUBLIC
    cxx_std_17
)