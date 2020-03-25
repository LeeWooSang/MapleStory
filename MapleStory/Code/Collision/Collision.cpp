#include "Collision.h"

AABB GetAABB(AABB *pAABBs, int nAABBs)
{
	if (!nAABBs) return(AABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(0.0f, 0.0f)));
    AABB rcAABB = pAABBs[0];
    for (int i = 1; i < nAABBs; i++) rcAABB = rcAABB.Extend(&pAABBs[i]);
    return(rcAABB);
}

AABB GetAABB(CIRCLE *pCircles, int nCircles)
{
	if (!nCircles) return(AABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(0.0f, 0.0f)));
	AABB rcAABB(pCircles[0].m_vCenter, VECTOR2D(0.0f, 0.0f));
	for (int i = 0; i < nCircles; i++)
	{
		VECTOR2D vExtents = VECTOR2D(pCircles[i].m_fRadius, pCircles[i].m_fRadius);
		VECTOR2D vMin = pCircles[i].m_vCenter - vExtents;
		VECTOR2D vMax = pCircles[i].m_vCenter + vExtents;
		rcAABB = rcAABB.Extend(&vMin);
		rcAABB = rcAABB.Extend(&vMax);
	}
	return(rcAABB);
}

CIRCLE GetBoundingCircle(CIRCLE *pCircles, int nCircles)
{
	CIRCLE c(VECTOR2D(0.0f, 0.0f), 0);
	AABB rcAABB = GetAABB(pCircles, nCircles);
	c.m_vCenter = rcAABB.Center();
	
	for (int i = 0; i < nCircles; i++)
	{
        VECTOR2D d = pCircles[i].m_vCenter - c.m_vCenter;
		c.m_fRadius = fmax((d.Length() + pCircles[i].m_fRadius), c.m_fRadius);
	}
	return(c);
}

//////////////////////////////////////////////////////////////////////////////////
//
VECTOR2D VECTOR2D::Clamp(AABB *pAABB) 
{ 
	VECTOR2D vClamped; 
	vClamped.x = fClamp(this->x, pAABB->m_vOrigin.x, pAABB->m_vOrigin.x + pAABB->m_vExtents.x); 
	vClamped.y = ::fClamp(this->y, pAABB->m_vOrigin.y, pAABB->m_vOrigin.y + pAABB->m_vExtents.y); 
	return(vClamped); 
}

bool VECTOR2D::Intersect(LINESEGMENT *pS) 
{ 
	VECTOR2D vDirS = pS->m_vEnd - pS->m_vStart; 
	VECTOR2D vFromS = *this - pS->m_vStart; 
	VECTOR2D vProject = vFromS.Project(vDirS); 
	return(vFromS.Intersect(&vProject) && ((vProject * vProject) <= (vDirS * vDirS)) && ((vProject * vDirS) <= 0.0f)); 
}

bool VECTOR2D::Intersect(AABB *pAABB) 
{ 
	float left = pAABB->m_vOrigin.x; 
	float right = left + pAABB->m_vExtents.x; 
	float bottom = pAABB->m_vOrigin.y; 
	float top = bottom + pAABB->m_vExtents.y; 
	return((left <= x) && (bottom <= y) && (x <= right) && (y <= top)); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool LINE::Intersect(LINESEGMENT *pS) 
{ 
	VECTOR2D d1 = m_vOrigin - pS->m_vStart; 
	VECTOR2D d2 = m_vOrigin - pS->m_vEnd; 
	VECTOR2D n = m_vDirection.Rotate90(); 
	return(((n * d1) * (n * d2)) <= 0); 
}

bool LINE::Intersect(AABB *pAABB)
{
    VECTOR2D c1 = pAABB->m_vOrigin;
    VECTOR2D c2 = c1 + pAABB->m_vExtents;
	VECTOR2D c3 = VECTOR2D(c2.x, c1.y);
	VECTOR2D c4 = VECTOR2D(c1.x, c2.y);
    c1 = c1 - m_vOrigin;
    c2 = c2 - m_vOrigin;
    c3 = c3 - m_vOrigin;
    c4 = c4 - m_vOrigin;
	VECTOR2D n = m_vDirection.Rotate90();
    float dp1 = n * c1;
    float dp2 = n * c2;
    float dp3 = n * c3;
    float dp4 = n * c4;

	return((dp1 * dp2 <= 0.0f) || (dp2 * dp3 <= 0.0f) || (dp3 * dp4 <= 0.0f));
}

bool LINE::Intersect(OOBB *pOOBB)
{
	AABB rcAABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(pOOBB->m_vExtents.x * 2.0f, pOOBB->m_vExtents.y * 2.0f));

	LINE line;
	line.m_vOrigin = m_vOrigin - pOOBB->m_vCenter;
	line.m_vOrigin = line.m_vOrigin.Rotate(-pOOBB->m_fRotation);
	line.m_vOrigin = line.m_vOrigin + pOOBB->m_vExtents;
	line.m_vDirection = m_vDirection.Rotate(-pOOBB->m_fRotation);

    return(line.Intersect(&rcAABB));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool LINESEGMENT::IsSeparatingAxis(OOBB *pOOBB) 
{ 
	LINESEGMENT sEdge0 = pOOBB->Edge(0); 
	LINESEGMENT sEdge2 = pOOBB->Edge(2); 
	VECTOR2D n = (m_vStart - m_vEnd).Normalize(); 
	RANGE rAxis = Project(&n); 
	RANGE rRange0 = sEdge0.Project(&n); 
	RANGE rRange2 = sEdge2.Project(&n); 
	RANGE rProject = rRange0.Union(&rRange2); 
	return(!rAxis.IsOverlapping(&rProject)); 
}

bool LINESEGMENT::IsSeparatingAxis(AABB *pAABB) 
{ 
	VECTOR2D n = (m_vStart - m_vEnd).Normalize(); 
	LINESEGMENT sEdgeA(pAABB->Corner(0), pAABB->Corner(1)); 
	LINESEGMENT sEdgeB(pAABB->Corner(2), pAABB->Corner(3)); 
	RANGE rEdgeA = sEdgeA.Project(&n); 
	RANGE rEdgeB = sEdgeB.Project(&n); 
	RANGE rProject = rEdgeA.Union(&rEdgeB); 
	RANGE rAxis = Project(&n); 
	return(!rAxis.IsOverlapping(&rProject)); 
}

bool LINESEGMENT::Intersect(LINESEGMENT *pS)
{
	LINE aAxis(m_vStart, m_vEnd - m_vStart);
	if ((aAxis.m_vDirection.x == 0.0f) && (aAxis.m_vDirection.y == 0.0f)) return(m_vStart.Intersect(pS));
	else if(aAxis.Intersect(pS)) return(false);
	LINE bAxis(pS->m_vStart, pS->m_vEnd - pS->m_vStart);
	if ((bAxis.m_vDirection.x == 0.0f) && (bAxis.m_vDirection.y == 0.0f)) return(pS->m_vStart.Intersect(this));
	else if (bAxis.Intersect(this)) return(false);
	if (aAxis.m_vDirection.IsParallel(&bAxis.m_vDirection))
	{
		VECTOR2D vDirection = aAxis.m_vDirection.Normalize();
		RANGE rA = Project(&vDirection);
		RANGE rB = pS->Project(&vDirection);
		return(rA.IsOverlapping(&rB));
	}
	return(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
AABB CIRCLE::GetAABB() 
{
	return(AABB(m_vCenter.x - m_fRadius, m_vCenter.y - m_fRadius, m_vCenter.x + m_fRadius, m_vCenter.y + m_fRadius)); 
}

bool CIRCLE::Intersect(AABB *pAABB) 
{ 
	VECTOR2D vClamped = m_vCenter.Clamp(pAABB); 
	return(Intersect(&vClamped)); 
}

bool CIRCLE::Intersect(OOBB *pOOBB) 
{ 
	AABB rcAABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(pOOBB->m_vExtents.x * 2.0f, pOOBB->m_vExtents.y * 2.0f)); 

	CIRCLE cCircle(VECTOR2D(0.0f, 0.0f), m_fRadius); 
	cCircle.m_vCenter = m_vCenter - pOOBB->m_vCenter; 
	cCircle.m_vCenter = cCircle.m_vCenter.Rotate(-(pOOBB->m_fRotation)); 
	cCircle.m_vCenter = cCircle.m_vCenter + pOOBB->m_vExtents; 

	return(cCircle.Intersect(&rcAABB)); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool AABB::Intersect(AABB *pAABB) 
{ 
	return(::IsOverlapping(m_vOrigin.x, m_vOrigin.x + m_vExtents.x, pAABB->m_vOrigin.x, pAABB->m_vOrigin.x + pAABB->m_vExtents.x) && ::IsOverlapping(m_vOrigin.y, m_vOrigin.y + m_vExtents.y, pAABB->m_vOrigin.y, pAABB->m_vOrigin.y + pAABB->m_vExtents.y)); 
}

bool AABB::Intersect(LINESEGMENT *pS)
{
	RANGE rRange(m_vOrigin.x, m_vOrigin.x + m_vExtents.x);
	RANGE sRange(pS->m_vStart.x, pS->m_vEnd.x);
	if (!rRange.IsOverlapping(&sRange)) return(false);

	rRange = RANGE(m_vOrigin.y, m_vOrigin.y + m_vExtents.y);
	sRange = RANGE(pS->m_vStart.y, pS->m_vEnd.y);
	if (!rRange.IsOverlapping(&sRange)) return(false);

	LINE sLine(pS->m_vStart, pS->m_vEnd - pS->m_vStart);
    return sLine.Intersect(this);
}

AABB AABB::Transform(Matrix3x2F *pd2dmtxTransform)
{
	VECTOR2D vCorners[4];
	for (int i = 0; i < 4; i++) 
	{
		vCorners[i] = Corner(i);
		vCorners[i] = vCorners[i].Transform(pd2dmtxTransform);
	}
	VECTOR2D vMin(FLT_MAX, FLT_MAX), vMax(-FLT_MAX, -FLT_MAX);
	for (int i = 0; i < 4; i++)
	{
		if (vCorners[i].x < vMin.x) vMin.x = vCorners[i].x;
		if (vCorners[i].y < vMin.y) vMin.y = vCorners[i].y;
		if (vCorners[i].x > vMax.x) vMax.x = vCorners[i].x;
		if (vCorners[i].y > vMax.y) vMax.y = vCorners[i].y;
	}
	return(AABB(vMin, vMax - vMin));
}

bool AABB::Intersect(VECTOR2D *pvMoving, AABB *pAABB)
{
	AABB rcEnvelope(m_vOrigin + (*pvMoving), m_vExtents);
	rcEnvelope = rcEnvelope.Extend(this);
	if (rcEnvelope.Intersect(pAABB))
	{
		float fEpsilon = 1.0f / 32.0f;
		float fMinMoveDistance = max(min(m_vExtents.x, m_vExtents.y) * 0.25f, fEpsilon);
		if (pvMoving->Length() < fMinMoveDistance) return(true);
		VECTOR2D vHalfMoving = 0.5f * (*pvMoving);
		rcEnvelope.m_vOrigin = m_vOrigin + vHalfMoving;
		rcEnvelope.m_vExtents = m_vExtents;
		return(Intersect(&vHalfMoving, pAABB) || rcEnvelope.Intersect(&vHalfMoving, pAABB));
	}
	return(false);
}

bool AABB::Intersect(VECTOR2D *pvMoving, CIRCLE *pC)
{
	VECTOR2D vOppositeMoving = -(*pvMoving);
	return(pC->Intersect(&vOppositeMoving, this));
}

bool AABB::Intersect(OOBB *pOOBB) 
{ 
	return(pOOBB->Intersect(this)); 
}

bool AABB::Intersect(CIRCLE *pCircle) 
{ 
	return(pCircle->Intersect(this)); 
}

bool AABB::Contain(AABB *pAABB)
{
	return((m_vOrigin.x <= pAABB->m_vOrigin.x) && ((m_vOrigin.x + m_vExtents.x) >= (pAABB->m_vOrigin.x + pAABB->m_vExtents.x)) && (m_vOrigin.y <= pAABB->m_vOrigin.y) && ((m_vOrigin.y + m_vExtents.y) >= (pAABB->m_vOrigin.y + pAABB->m_vExtents.y))); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool OOBB::Intersect(OOBB *pOOBB)
{
	LINESEGMENT lS = Edge(0);
	if (lS.IsSeparatingAxis(pOOBB)) return(false);
	lS = Edge(1);
	if (lS.IsSeparatingAxis(pOOBB)) return(false);
	lS = pOOBB->Edge(0);
	if (lS.IsSeparatingAxis(this)) return(false);
	lS = pOOBB->Edge(1);
	return(!lS.IsSeparatingAxis(this));
}

bool OOBB::Intersect(VECTOR2D *pV) 
{ 
	AABB rcAABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(m_vExtents.x * 2.0f, m_vExtents.y * 2.0f)); 
	VECTOR2D vCenterToPoint = *pV - m_vCenter; 
	vCenterToPoint = vCenterToPoint.Rotate(-m_fRotation); 
	vCenterToPoint = vCenterToPoint + m_vExtents; 
	return(vCenterToPoint.Intersect(&rcAABB)); 
}

bool OOBB::Intersect(AABB * pAABB)
{
	AABB rcAABB = GetAABB();
	if (!rcAABB.Intersect(pAABB)) return(false);

	LINESEGMENT lSegment = Edge(0);
	if (lSegment.IsSeparatingAxis(pAABB)) return(false);
	lSegment = Edge(1);
	return(!lSegment.IsSeparatingAxis(pAABB));
}

bool OOBB::Intersect(LINESEGMENT* pS)
{
	AABB rcAABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(m_vExtents.x * 2.0f, m_vExtents.y * 2.0f));

	LINESEGMENT lSegment;
    lSegment.m_vStart = pS->m_vStart - m_vCenter;
    lSegment.m_vStart = lSegment.m_vStart.Rotate(-m_fRotation);
    lSegment.m_vStart = lSegment.m_vStart + m_vExtents;
    lSegment.m_vEnd = pS->m_vEnd - m_vCenter;
    lSegment.m_vEnd = lSegment.m_vEnd.Rotate(-m_fRotation);
    lSegment.m_vEnd = lSegment.m_vEnd + m_vExtents;

    return(rcAABB.Intersect(&lSegment));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CIRCLE::Intersect(VECTOR2D *pvMoving, CIRCLE *pC)
{
	LINESEGMENT lMoving(m_vCenter, m_vCenter + *pvMoving);
	CIRCLE cMerged(VECTOR2D(pC->m_vCenter.x, pC->m_vCenter.y), pC->m_fRadius + m_fRadius);
	return(cMerged.Intersect(&lMoving));
}

bool CIRCLE::Intersect(VECTOR2D *pvMoving, AABB *pAABB)
{
	VECTOR2D vHalfMoving = 0.5f * (*pvMoving);
	float fMovingDistance = pvMoving->Length();
	CIRCLE cEnvelope(m_vCenter + vHalfMoving, m_fRadius + (fMovingDistance * 0.5f));
	if (cEnvelope.Intersect(pAABB))
	{
		float fEpsilon = 1.0f / 32.0f;
		float fMinMoveDistance = max(m_fRadius / 4, fEpsilon);
		if (fMovingDistance < fMinMoveDistance) return(true);
		cEnvelope.m_fRadius = m_fRadius;
		return(Intersect(&vHalfMoving, pAABB) || cEnvelope.Intersect(&vHalfMoving, pAABB));
	}
	return(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
CAABBCollider::CAABBCollider(ID2D1Geometry *pd2dGeometry) : Collider(COLLIDER_AABB)
{
	D2D1_RECT_F d2drcBounds = { 0.0f, 0.0f, 0.0f, 0.0f }; 
	if (pd2dGeometry) pd2dGeometry->GetBounds(NULL, &d2drcBounds); 
	m_rcBounds = AABB(d2drcBounds);
}

CAABBCollider::~CAABBCollider()
{
}

void CAABBCollider::Update(Matrix3x2F *pd2dmtxTransform)
{
	m_rcTransformedBounds = m_rcBounds.Transform(pd2dmtxTransform);
}

AABB CAABBCollider::GetAABB(D2D1_RECT_F *pd2drcBounds)
{
	if (pd2drcBounds)
	{
		pd2drcBounds->left = m_rcBounds.m_vOrigin.x;
		pd2drcBounds->top = m_rcBounds.m_vOrigin.y;
		pd2drcBounds->right = m_rcBounds.m_vOrigin.x + m_rcBounds.m_vExtents.x;
		pd2drcBounds->bottom = m_rcBounds.m_vOrigin.y + m_rcBounds.m_vExtents.y;
	}
	return(m_rcBounds);
}

AABB CAABBCollider::GetBounds(D2D1_RECT_F *pd2drcBounds) 
{ 
	if (pd2drcBounds)
	{
		pd2drcBounds->left = m_rcBounds.m_vOrigin.x;
		pd2drcBounds->top = m_rcBounds.m_vOrigin.y;
		pd2drcBounds->right = m_rcBounds.m_vOrigin.x + m_rcBounds.m_vExtents.x;
		pd2drcBounds->bottom = m_rcBounds.m_vOrigin.y + m_rcBounds.m_vExtents.y;
	}
	return(m_rcBounds); 
}

AABB CAABBCollider::GetTransformedBounds(Matrix3x2F *pd2dmtxTransform, D2D1_RECT_F *pd2drcBounds) 
{ 
	m_rcTransformedBounds = m_rcBounds.Transform(pd2dmtxTransform); 
	if (pd2drcBounds)
	{
		pd2drcBounds->left = m_rcTransformedBounds.m_vOrigin.x;
		pd2drcBounds->top = m_rcTransformedBounds.m_vOrigin.y;
		pd2drcBounds->right = m_rcTransformedBounds.m_vOrigin.x + m_rcTransformedBounds.m_vExtents.x;
		pd2drcBounds->bottom = m_rcTransformedBounds.m_vOrigin.y + m_rcTransformedBounds.m_vExtents.y;
	}
	return(m_rcTransformedBounds); 
}

bool CAABBCollider::Intersect(Collider *pOtherCollider, float *pfDistance)
{
	bool bCollided = false;
	switch (pOtherCollider->GetType())
	{
		case COLLIDER_AABB:
		{
			CAABBCollider *pOtherAABBCollider = (CAABBCollider *)pOtherCollider;
			bCollided = m_rcTransformedBounds.Intersect(&pOtherAABBCollider->m_rcTransformedBounds);
			break;
		}
		case COLLIDER_OOBB:
		{
			CAABBCollider *pOtherAABBCollider = (CAABBCollider *)pOtherCollider;
			bCollided = m_rcTransformedBounds.Intersect(&pOtherAABBCollider->m_rcTransformedBounds);
			break;
		}
		case COLLIDER_CIRCLE:
		{
			CCircleCollider *pOtherCircleCollider = (CCircleCollider *)pOtherCollider;
			bCollided = m_rcTransformedBounds.Intersect(&pOtherCircleCollider->m_ccTransformedBounds);
			break;
		}
	}
	return(bCollided);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
COOBBCollider::COOBBCollider(ID2D1Geometry *pd2dGeometry) : Collider(COLLIDER_OOBB)
{
	D2D1_RECT_F d2drcBounds = { 0.0f, 0.0f, 0.0f, 0.0f }; 
	if (pd2dGeometry) pd2dGeometry->GetBounds(NULL, &d2drcBounds); 
	m_rcBounds = OOBB(d2drcBounds);
}

COOBBCollider::~COOBBCollider()
{
}

void COOBBCollider::Update(Matrix3x2F *pd2dmtxTransform)
{
	m_rcTransformedBounds = m_rcBounds.Transform(pd2dmtxTransform);
}

AABB COOBBCollider::GetAABB(D2D1_RECT_F *pd2drcBounds)
{
	if (pd2drcBounds)
	{
		pd2drcBounds->left = m_rcBounds.m_vCenter.x - m_rcBounds.m_vExtents.x;
		pd2drcBounds->top = m_rcBounds.m_vCenter.y - m_rcBounds.m_vExtents.y;
		pd2drcBounds->right = m_rcBounds.m_vCenter.x + m_rcBounds.m_vExtents.x;
		pd2drcBounds->bottom = m_rcBounds.m_vCenter.y + m_rcBounds.m_vExtents.y;
	}
	return(m_rcBounds.GetAABB());
}

OOBB COOBBCollider::GetBounds(D2D1_RECT_F *pd2drcBounds) 
{ 
	if (pd2drcBounds)
	{
		pd2drcBounds->left = m_rcBounds.m_vCenter.x - m_rcBounds.m_vExtents.x;
		pd2drcBounds->top = m_rcBounds.m_vCenter.y - m_rcBounds.m_vExtents.y;
		pd2drcBounds->right = m_rcBounds.m_vCenter.x + m_rcBounds.m_vExtents.x;
		pd2drcBounds->bottom = m_rcBounds.m_vCenter.y + m_rcBounds.m_vExtents.y;
	}
	return(m_rcBounds); 
}

bool COOBBCollider::Intersect(Collider *pOtherCollider, float *pfDistance)
{
	bool bCollided = false;
	switch (pOtherCollider->GetType())
	{
		case COLLIDER_AABB:
		{
			CAABBCollider *pOtherAABBCollider = (CAABBCollider *)pOtherCollider;
			bCollided = m_rcTransformedBounds.Intersect(&pOtherAABBCollider->m_rcTransformedBounds);
			break;
		}
		case COLLIDER_OOBB:
		{
			COOBBCollider *pOtherOOBBCollider = (COOBBCollider *)pOtherCollider;
			bCollided = m_rcTransformedBounds.Intersect(&pOtherOOBBCollider->m_rcTransformedBounds);
			break;
		}
		case COLLIDER_CIRCLE:
		{
			CCircleCollider *pOtherCircleCollider = (CCircleCollider *)pOtherCollider;
			bCollided = m_rcTransformedBounds.Intersect(&pOtherCircleCollider->m_ccTransformedBounds);
			break;
		}
	}
	return(bCollided);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
CCircleCollider::CCircleCollider(ID2D1Geometry *pd2dGeometry) : Collider(COLLIDER_CIRCLE)
{
	D2D1_RECT_F d2drcBounds = { 0.0f, 0.0f, 0.0f, 0.0f }; 
	if (pd2dGeometry) pd2dGeometry->GetBounds(NULL, &d2drcBounds); 
	OOBB rcOOBB(d2drcBounds);
	m_ccBounds = CIRCLE(rcOOBB.m_vCenter, rcOOBB.m_vExtents.Length());
}

CCircleCollider::~CCircleCollider()
{
}

void CCircleCollider::Update(Matrix3x2F *pd2dmtxTransform)
{
	m_ccTransformedBounds = m_ccBounds.Transform(pd2dmtxTransform);
}

AABB CCircleCollider::GetAABB(D2D1_RECT_F *pd2drcBounds)
{
	if (pd2drcBounds)
	{
		pd2drcBounds->left = m_ccBounds.m_vCenter.x - m_ccBounds.m_fRadius;
		pd2drcBounds->top = m_ccBounds.m_vCenter.y - m_ccBounds.m_fRadius;
		pd2drcBounds->right = m_ccBounds.m_vCenter.x + m_ccBounds.m_fRadius;
		pd2drcBounds->bottom = m_ccBounds.m_vCenter.y - m_ccBounds.m_fRadius;
	}
	return(m_ccBounds.GetAABB());
}

CIRCLE CCircleCollider::GetBounds(D2D1_ELLIPSE *pd2dEllipse)
{
	if (pd2dEllipse)
	{
		*pd2dEllipse = Ellipse(m_ccBounds.m_vCenter, m_ccBounds.m_fRadius, m_ccBounds.m_fRadius);
	}
	return(m_ccBounds);
}

bool CCircleCollider::Intersect(Collider *pOtherCollider, float *pfDistance)
{
	bool bCollided = false;
	switch (pOtherCollider->GetType())
	{
		case COLLIDER_AABB:
		{
			CAABBCollider *pOtherAABBCollider = (CAABBCollider *)pOtherCollider;
			bCollided = m_ccTransformedBounds.Intersect(&pOtherAABBCollider->m_rcTransformedBounds);
			break;
		}
		case COLLIDER_OOBB:
		{
			COOBBCollider *pOtherOOBBCollider = (COOBBCollider *)pOtherCollider;
			bCollided = m_ccTransformedBounds.Intersect(&pOtherOOBBCollider->m_rcTransformedBounds);
			break;
		}
		case COLLIDER_CIRCLE:
		{
			CCircleCollider *pOtherCircleCollider = (CCircleCollider *)pOtherCollider;
			bCollided = m_ccTransformedBounds.Intersect(&pOtherCircleCollider->m_ccTransformedBounds);
			break;
		}
	}
	return(bCollided);
}

