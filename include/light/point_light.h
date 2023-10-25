#pragma once

#include <vector>
#include <algorithm>

// Include Glew
#include "GL/glew.h"
// Include GLFW
#include "GLFW/glfw3.h"

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/placeable.h"
#include "observable.h"

class PointLight : public Placeable, public Observable<PointLight> {
public:
    void set_translation(glm::vec3 value, bool apply) override;

    [[nodiscard]] const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

private:
    glm::vec3 color{0.7, 0.7, 0.7};
};
