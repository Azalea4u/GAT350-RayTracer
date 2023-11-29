#include "Camera.h"
#include "MathUtils.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio)
{

}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_eye = eye;
	// set the camera axis vectors (forward, right, up)
	// forward vector (eye <- target)
	m_forward = normalize(target - eye);
	// use cross product to create vectors
		// right = up x forward 
	m_right = normalize(cross(up, m_forward));
		//<make sure to normalize vector>
	// up = forward x right
	m_up = m_forward * m_right;
		// <both vectors are normalized, no need to normalize :)>
	
	CalculateViewPlane();
}

void Camera::CalculateViewPlane()
{
	// convert fov angle (degrees) to radians
	float theta = glm::radians(m_fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = halfHeight * 2.0f;
		//<twice the size of half height>;
	float width = height * m_aspectRatio;
		//<height * aspectRatio>;

	// calculate horizontal vector (right vector * width)
	m_horizontal = m_right * width;
		//<right * width>
		// calculate vertical vector (up vector * height)
		m_vertical = m_up * height;
			//<up * height>
		// calculate lower left location (origin)
		m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;
			//(<half horizontal>) - (<half vertical>) - m_forward;
}

ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	// the ray origin is the camera eye
	ray.origin = m_eye;
	//<set ray origin>
	// calculate direction from point
	ray.direction = normalize(m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye);
	//<lower left + (horizontal * point x) + (vertical * point.y) - eye>

	return ray;
}
