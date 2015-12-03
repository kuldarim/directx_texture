////////////////////////////////////////////////////////////////////////////////
// Filename: TransformationClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TRANSFORMATION_CLASS_H_
#define _TRANSFORMATION_CLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: TransformationClass
////////////////////////////////////////////////////////////////////////////////
class TransformationClass
{
public:
	TransformationClass();
	TransformationClass(const TransformationClass&);
	~TransformationClass();

	void SetCameraPosition(D3DXVECTOR3);
	void SetCameraTarget(D3DXVECTOR3);
	void SetCameraUPV(D3DXVECTOR3);

	D3DXVECTOR3 GetCameraPosition();
	D3DXVECTOR3 GetCameraTarget();
	D3DXVECTOR3 GetCameraUPV();

	void Initialize(HWND);
	void Render();

	D3DXMATRIX GetViewMatrix();
	D3DXMATRIX GetProjectionMatrix();
	D3DXMATRIX GetOrthoMatrix();

private:
	D3DXVECTOR3 m_position, m_target, m_upv;

	int m_screenWidth, m_screenHeight;
 	float m_screenNear, m_screenDepth;

	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_orthoMatrix;
};

#endif