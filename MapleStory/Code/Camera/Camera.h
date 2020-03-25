#pragma once
#include "../Macro.h"
#include "../Defines.h"
#include "../Collision/Collision.h"

struct ViewPort
{
	UINT							m_xStart;
	UINT							m_yStart;
	UINT							m_nWidth;
	UINT							m_nHeight;
	UINT							m_nMinLayer;
	UINT							m_nMaxLayer;
};

class Camera
{
	SINGLE_TONE(Camera)
public:
	 void Move(VECTOR2D& vShift) { m_positionVector += vShift; }
	 void Rotate(float);
	 void Update(float);

	void RegenerateViewMatrix();
	bool IsVisible(class GameObject*);

	const Matrix3x2F& GetViewMatrix() const { return m_viewMatrix; }

	VECTOR2D GetRightVector() { return(m_rightVector); }
	VECTOR2D GetPosition()	const { return m_positionVector; }
	VECTOR2D GetUpVector() { return m_upVector; }

	VECTOR2D GetExtents()	const { return m_extents; }
	void SetExtents(VECTOR2D& extents) { m_extents = extents; m_positionVector -= 0.5f * m_extents; }

	float GetTimeLag()	const { return(m_timeLag); }
	void SetTimeLag(float timeLag) { m_timeLag = timeLag; }

	const ViewPort& GetViewport()	const { return m_viewport; }
	void SetViewport(UINT xStart, UINT yStart, UINT nWidth, UINT nHeight, UINT nMinLayer, UINT nMaxLayer);

private:
	Matrix3x2F m_viewMatrix;

	VECTOR2D m_positionVector;
	VECTOR2D m_rightVector;
	VECTOR2D m_upVector;

	float m_angle;
	float m_timeLag;

	//Matrix3x2F m_d2dmtxProjection;

	ViewPort m_viewport;
	VECTOR2D m_extents;
};



