#include <d3dx10math.h>

class pCamera{
public:
	pCamera();
	pCamera(const pCamera&);
	~pCamera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	D3DXMATRIX pViewMatrix;
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
};
