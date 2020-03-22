#pragma once
#include "../Macro.h"
#include "../Defines.h"
#include "../Network/Network.h"

constexpr float ASPECT_RATIO = float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT);

class Camera
{
	SINGLE_TONE(Camera)

	bool Initialize();
	void Update(char, float);
	bool Move(const XMFLOAT2&);

	void GenerateProjectionMatrix(float, float, float, float);

	const D3D12_VIEWPORT& GetViewPort()	const { return m_ViewPort; }
	const XMFLOAT4X4& GetProjectionMatrix()	const { return m_ProjectionMatrix; }

	const XMFLOAT2& GetWorldPosition()	const { return m_WorldPosition; }
	void SetWorldPosition(const XMFLOAT2& pos) { m_WorldPosition = pos; }

	void SetTarget(class GameObject* target);

private:
	D3D12_VIEWPORT m_ViewPort;
	XMFLOAT4X4 m_ProjectionMatrix;

	XMFLOAT2 m_WorldPosition;

	class GameObject* m_Target;
};