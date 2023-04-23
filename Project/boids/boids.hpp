#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids {
private:
    glm::vec3 m_pos = {0., 0., 0.};
    glm::vec3 m_dir = {1., 1., 1.};
    glm::vec3 m_speed = {0., 0., 0.};
public:
    glm::vec3 getPos();
};