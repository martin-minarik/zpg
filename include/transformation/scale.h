#pragma once

// Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "transformation/transformation_component.h"

class Scale : public TransformationComponent {
public:
    explicit Scale(glm::vec3 vec);

    void apply() override;

    const glm::vec3 &get_vec() const;

    void set_vec(const glm::vec3 &vec);

private:
    glm::vec3 vec;
};
