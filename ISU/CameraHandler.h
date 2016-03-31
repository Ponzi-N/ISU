#include <d3dx10math.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	D3DXMATRIX pViewMatrix;
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
};