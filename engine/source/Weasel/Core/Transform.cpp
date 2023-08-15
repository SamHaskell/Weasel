#include "Weasel/Core/Transform.hpp"

namespace Weasel {
    void Transform::Invalidate() {
        m_Valid = false;
        for (auto& tf : m_Children) {
            tf->Invalidate();
        }
    }

    glm::mat4 Transform::WorldTransform() {
        if (!m_Parent) {
            return LocalTransform();
        }
        if (!m_Valid) {
            m_WorldTransform = LocalTransform() * m_Parent->WorldTransform();
        }
        return m_WorldTransform;
    }

    glm::quat Transform::WorldRotation() {
        if (!m_Parent) {
            return LocalRotation();
        }
        return LocalRotation() * m_Parent->WorldRotation();
    }

    glm::vec3 Transform::WorldPosition() {
        return WorldTransform()[3];
    }

    glm::mat4 Transform::LocalTransform() {
        if (!m_Valid) {
            m_LocalTransform = glm::translate(glm::mat4(1.0f), m_LocalPosition) * glm::mat4_cast(m_LocalRotation) * glm::scale(glm::mat4(1.0f), m_LocalScale);
        }
        return m_LocalTransform;
    }

    glm::quat Transform::LocalRotation() {
        return m_LocalRotation;
    }
    
    glm::vec3 Transform::LocalPosition() {
        return m_LocalPosition;
    }

    glm::vec3 Transform::LocalScale() {
        return m_LocalScale;
    }

    glm::vec3 Transform::Forward() {
        return glm::rotate(WorldRotation(), glm::vec3(0.0, 0.0, -1.0));
    }

    glm::vec3 Transform::Up() {
        return glm::rotate(WorldRotation(), glm::vec3(0.0, 1.0, 0.0));
    }

    glm::vec3 Transform::Right() {
        return glm::rotate(WorldRotation(), glm::vec3(1.0, 0.0, 0.0));
    }

    void Transform::SetLocalRotation(const glm::quat& rotation) {
        m_Valid = false;
        m_LocalRotation = rotation;
    }

    void Transform::SetLocalPosition(const glm::vec3& position) {
        m_Valid = false;
        m_LocalPosition = position;
    }

    void Transform::SetLocalScale(const glm::vec3& scale) {
        m_Valid = false;
        m_LocalScale = scale;
    }  

    void Transform::Translate(const glm::vec3& displacement) {
        m_Valid = false;
        m_LocalPosition += displacement;
    }  

    void Transform::Rotate(const glm::vec3& axis, f32 angle) {
        m_Valid = false;
        m_LocalRotation = glm::angleAxis(glm::radians(angle), axis) * m_LocalRotation;
    }
}