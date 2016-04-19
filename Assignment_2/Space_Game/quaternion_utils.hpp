#ifndef QUATERNION_UTILS_H
#define QUATERNION_UTILS_H
#include <vector>
#include <glm/glm.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);

glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp);

glm::quat RotateTowards(glm::quat q1, glm::quat q2, float maxAngle);


#endif // QUATERNION_UTILS_H