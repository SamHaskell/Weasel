project(
    WeaselEditor
    VERSION 0.1
    DESCRIPTION "Weasel Engine Editor"
    LANGUAGES CXX
)

set(
    LOCAL_SOURCES
    ${PROJECT_SOURCE_DIR}/source/Editor.cpp
    ${PROJECT_SOURCE_DIR}/source/EditorLayer.cpp
)

set(
    LOCAL_HEADERS
    ${PROJECT_SOURCE_DIR}/source/EditorLayer.hpp
)

add_executable(
    ${PROJECT_NAME}
    ${LOCAL_SOURCES}
    ${LOCAL_HEADERS}
)

target_compile_features(
    ${PROJECT_NAME} PRIVATE
    cxx_std_17
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/source
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    Weasel
)