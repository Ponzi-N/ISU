#include "CameraHandler.h"


pCamera::pCamera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


pCamera::pCamera(const pCamera& other)
{
}


pCamera::~pCamera()
{
}


void pCamera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void pCamera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


void pCamera::Render()
{
	D3DXVECTOR3 up;
	D3DXVECTOR3 position;
	D3DXVECTOR3 lookAt;
	float radians;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Calculate the rotation in radians.
	radians = m_rotationY * 0.0174532925f;

	// Setup where the camera is looking.
	lookAt.x = sinf(radians) + m_positionX;
	lookAt.y = m_positionY;
	lookAt.z = cosf(radians) + m_positionZ;

	// Create the view matrix from the three vectors.
	D3DXMatrixLookAtLH(&pViewMatrix, &position, &lookAt, &up);

	return;
}


void pCamera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = pViewMatrix;
	return;
}