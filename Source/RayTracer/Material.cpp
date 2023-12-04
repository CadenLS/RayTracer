#include "Material.h"
#include "MathUtils.h"

namespace ray 
{
    bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
    {
        // scatters the lambertain reflection in a random direction
        glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();
        glm::vec3 direction = glm::normalize(target - raycastHit.point);
        scattered = { raycastHit.point, direction };
        color = m_albedo;

        return true;
    }

    bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
    {
        glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);
        scattered = { raycastHit.point, reflected + (randomInUnitSphere() * m_fuzz) };
        color = m_albedo;
        
        return (glm::dot(scattered.direction, raycastHit.normal) > 0);
    }
}
