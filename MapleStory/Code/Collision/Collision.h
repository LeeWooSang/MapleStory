#pragma once
#include "../Defines.h"

struct VECTOR2D;
struct LINE;
struct LINESEGMENT;
struct RANGE;
struct CIRCLE;
struct AABB;
struct OOBB;

#define FRAMES_PER_SECOND		60.0f
#define COLLISION_UPDATE_RATIO	0.1f

#define EPSILON					1.0e-10f

inline bool IsZero(float fValue, float fEpsilon=EPSILON) { return((fabsf(fValue) < fEpsilon)); }
inline bool IsEqual(float fA, float fB, float fEpsilon=EPSILON) { return(::IsZero(fA - fB, fEpsilon)); }
inline bool IsOverlapping(float fMinA, float fMaxA, float fMinB, float fMaxB) { return((fMinB <= fMaxA) && (fMinA <= fMaxB)); }
inline float fClamp(float x, float fMin, float fMax) { return((x < fMin) ? fMin : ((fMax < x) ? fMax : x)); }
inline void Swap(float *pfS, float *pfT) { float fTemp = *pfS; *pfS = *pfT; *pfT = fTemp; }
inline float InverseSqrt(float fValue) { return(1.0f / sqrtf(fValue)); }

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern AABB GetAABB(AABB *pAABBs, int nAABBs);
extern AABB GetAABB(CIRCLE *pCircles, int nCircles);
extern CIRCLE GetBoundingCircle(CIRCLE *pCircles, int nCircles);

struct VECTOR2D : public D2D1_POINT_2F
{
public:
	VECTOR2D() { this->x = 0.0f, this->y = 0.0f; }
	VECTOR2D(float x, float y) { this->x = x, this->y = y; }
	VECTOR2D(D2D1_POINT_2F& d2dPoint) { this->x = d2dPoint.x; this->y = d2dPoint.y; }
	~VECTOR2D() { }

	VECTOR2D& operator += (VECTOR2D& v) { this->x += v.x; this->y += v.y; return(*this); }
	VECTOR2D& operator -= (VECTOR2D& v) { this->x -= v.x; this->y -= v.y; return(*this); }
	VECTOR2D& operator *= (float s) { this->x *= s; this->y *= s; return(*this); }
	VECTOR2D& operator /= (float s) { this->x /= s; this->y /= s; return(*this); }

	VECTOR2D operator + () { VECTOR2D v; v.x = this->x; v.y = this->y; return(v); }
	VECTOR2D operator - () { VECTOR2D v; v.x = -this->x; v.y = -this->y; return(v); }

	VECTOR2D operator + (VECTOR2D& v) { VECTOR2D o; o.x = this->x + v.x; o.y = this->y + v.y; return(o); }
	VECTOR2D operator - (VECTOR2D& v) { VECTOR2D o; o.x = this->x - v.x; o.y = this->y - v.y; return(o); }
	VECTOR2D operator * (float s) { VECTOR2D o; o.x = this->x * s; o.y = this->y * s; return(o); }
	VECTOR2D operator / (float s) { VECTOR2D o; o.x = this->x / s; o.y = this->y / s; return(o); }
	float operator * (VECTOR2D& v) { return(this->x * v.x + this->y * v.y); }

	friend VECTOR2D operator * (float s, D2D1_POINT_2F& v) { VECTOR2D o; o.x = v.x * s; o.y = v.y * s; return(o); }

	bool operator == (VECTOR2D& v) { return(IsEqual(this->x, v.x) && IsEqual(this->y, v.y)); }
	bool operator != (VECTOR2D& v) { return(!IsEqual(this->x, v.x) || !IsEqual(this->y, v.y)); }

	inline static void Swap(VECTOR2D *pvA, VECTOR2D *pvB) { VECTOR2D vTemp = *pvA; *pvA = *pvB; *pvB = vTemp; }

	float Length() { return(sqrt((this->x * this->x) + (this->y * this->y))); }
	static float Length(VECTOR2D *pv) { return(sqrt(pv->x*pv->x + pv->y*pv->y)); }
	static float Length(VECTOR2D& v) { return(sqrt(v.x*v.x + v.y*v.y)); }
	static float Length(D2D1_POINT_2F *pv) { return(sqrt(pv->x*pv->x + pv->y*pv->y)); }
	static float Length(D2D1_POINT_2F& v) { return(sqrt(v.x*v.x + v.y*v.y)); }

	float Distance(VECTOR2D *pv) { return(sqrt((this->x - pv->x) * (this->x - pv->x) + (this->y - pv->y) * (this->y - pv->y))); }
	float Distance(VECTOR2D& v) { return(sqrt((this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y))); }
	static float Distance(VECTOR2D *pA, VECTOR2D *pB) { return(sqrt((pA->x - pB->x) * (pA->x - pB->x) + (pA->y - pB->y) * (pA->y - pB->y))); }
	static float Distance(D2D1_POINT_2F *pA, D2D1_POINT_2F *pB) { return(sqrt((pA->x - pB->x) * (pA->x - pB->x) + (pA->y - pB->y) * (pA->y - pB->y))); }
	static float Distance(VECTOR2D& vA, VECTOR2D& vB) { return(sqrt((vA.x - vB.x) * (vA.x - vB.x) + (vA.y - vB.y) * (vA.y - vB.y))); }
	static float Distance(D2D1_POINT_2F& vA, D2D1_POINT_2F& vB) { return(sqrt((vA.x - vB.x) * (vA.x - vB.x) + (vA.y - vB.y) * (vA.y - vB.y))); }

	VECTOR2D Normalize() { VECTOR2D v = VECTOR2D(0.0f, 0.0f); float l = this->Length(); if (l != 0) { v.x = this->x / l; v.y = this->y / l; } return(v); }
	static VECTOR2D Normalize(D2D1_POINT_2F *pP) { VECTOR2D v = *pP; float l = Length(v); if (l != 0) { v.x /= l; v.y /= l; } return(v); }
	static VECTOR2D Normalize(D2D1_POINT_2F& p) { VECTOR2D v = p; float l = Length(v); if (l != 0) { v.x /= l; v.y /= l; } return(v); }

	VECTOR2D Rotate(float d) { float r = DEGREE_TO_RADIAN(d); float fSin = sinf(r); float fCos = cosf(r); return(VECTOR2D(this->x * fCos - this->y * fSin, this->x * fSin + this->y * fCos)); }
	VECTOR2D Rotate90() { return(VECTOR2D(-(this->y), this->x)); }
	VECTOR2D Rotate180() { return(VECTOR2D(-(this->x), -(this->y))); }
	VECTOR2D Rotate270() { return(VECTOR2D(this->y, -(this->x))); }

	float Angle(VECTOR2D& v) { VECTOR2D a = Normalize(); VECTOR2D b = v.Normalize(); return(RADIAN_TO_DEGREE(a * b)); }
	VECTOR2D Project(VECTOR2D& v) { float d = v * v; if (d == 0.0f) return(v); return((v * (*this * v)) / d); }

	bool IsParallel(VECTOR2D *pV) { VECTOR2D n = Rotate90(); return(!(::IsZero(this->x) && ::IsZero(this->y)) && !(::IsZero(pV->x) && ::IsZero(pV->y)) && IsEqual((n * (*pV)), 0.0f)); }

	VECTOR2D Clamp(AABB *pAABB);

	bool Intersect(VECTOR2D *pV) { return(::IsEqual(this->x, pV->x) && ::IsEqual(this->y, pV->y)); }
	bool Intersect(LINESEGMENT *pS);
	bool Intersect(AABB *pAABB);

	VECTOR2D Transform(Matrix3x2F *pd2dmtxTransform) { D2D1_POINT_2F d2dP = { this->x, this->y }; return((pd2dmtxTransform) ? pd2dmtxTransform->TransformPoint(d2dP) : d2dP); }
};

struct RANGE
{
public:
	RANGE() { }
	RANGE(float fMin, float fMax) { if (fMin < fMax) { m_fMin = fMin; m_fMax = fMax; } else { m_fMin = fMax; m_fMax = fMin; } }

	float			m_fMin;
	float			m_fMax;

	bool IsOverlapping(RANGE *pB) { return((pB->m_fMin <= m_fMax) && (m_fMin <= pB->m_fMax)); }
	RANGE Union(RANGE *pB) { RANGE hull; hull.m_fMin = (m_fMin < pB->m_fMin) ? m_fMin : pB->m_fMin; hull.m_fMax = (m_fMax > pB->m_fMax) ? m_fMax : pB->m_fMax; return(hull); }
};

struct LINE
{
public:
	LINE() { }
	LINE(VECTOR2D& o, VECTOR2D& d) { m_vOrigin = o; m_vDirection = d; }

	VECTOR2D		m_vOrigin;
	VECTOR2D		m_vDirection;

	bool Intersect(VECTOR2D *pL) { VECTOR2D d = *pL - m_vOrigin; return(((d.x == 0.0f) && (d.y == 0.0f)) || d.IsParallel(&m_vDirection)); }
	bool Intersect(LINE *pL) { return(!m_vDirection.IsParallel(&pL->m_vDirection) || Intersect(&pL->m_vOrigin)); }
	bool Intersect(LINESEGMENT *pS);
	bool Intersect(AABB *pAABB);
	bool Intersect(OOBB *pOOBB);
};

struct LINESEGMENT
{
public:
	LINESEGMENT() { }
	LINESEGMENT(VECTOR2D& s, VECTOR2D& e) { m_vStart = s; m_vEnd = e; }

	VECTOR2D		m_vStart;
	VECTOR2D		m_vEnd;

	RANGE Project(VECTOR2D *pV) { VECTOR2D vUnit = pV->Normalize(); return(RANGE(vUnit * m_vStart, vUnit * m_vEnd)); }
	bool IsSeparatingAxis(OOBB *pOOBB);
	bool IsSeparatingAxis(AABB *pAABB);

	bool Intersect(LINE *pA) { VECTOR2D d1 = pA->m_vOrigin - m_vStart; VECTOR2D d2 = pA->m_vOrigin - m_vEnd; VECTOR2D n = pA->m_vDirection.Rotate90(); return(((n * d1) * (n * d2)) <= 0); }
	bool Intersect(LINESEGMENT *pS);
};

struct CIRCLE
{
public:
	CIRCLE() { }
	CIRCLE(VECTOR2D& c, float r) { m_vCenter = c; m_fRadius = r; }

	VECTOR2D		m_vCenter;
    float			m_fRadius;

	AABB GetAABB();

	bool Intersect(CIRCLE *pC) { float fRadiusSum = m_fRadius + pC->m_fRadius; VECTOR2D vDistance = m_vCenter - pC->m_vCenter; return((vDistance * vDistance) <= (fRadiusSum * fRadiusSum)); }
	bool Intersect(VECTOR2D *pV) { VECTOR2D vDistance = m_vCenter - *pV; return((vDistance * vDistance) <= (m_fRadius * m_fRadius)); }
	bool Intersect(LINE *pL) { VECTOR2D vLC = m_vCenter - pL->m_vOrigin; VECTOR2D vP = vLC.Project(pL->m_vDirection); vP = pL->m_vOrigin + vP; return(Intersect(&vP)); }
	bool Intersect(LINESEGMENT *pS) { if (Intersect(&pS->m_vStart) || Intersect(&pS->m_vEnd)) return(true); VECTOR2D vDirection = pS->m_vEnd - pS->m_vStart; VECTOR2D vProject = (m_vCenter - pS->m_vStart).Project(vDirection); VECTOR2D vNearest = pS->m_vStart + vProject; return(Intersect(&vNearest) && ((vProject * vProject) <= (vDirection * vDirection)) && ((vProject * vDirection) >= 0.0f)); }

	bool Intersect(AABB *pAABB);
	bool Intersect(OOBB *pOOBB);

	bool Intersect(VECTOR2D *pvMoving, CIRCLE *pC);
	bool Intersect(VECTOR2D *pvMoving, AABB *pAABB);

	CIRCLE Transform(Matrix3x2F *pd2dmtxTransform) { VECTOR2D vCenter = m_vCenter.Transform(pd2dmtxTransform); return(CIRCLE(vCenter, m_fRadius)); }
};

struct AABB
{
public:
	AABB() { }
	AABB(float fLeft, float fTop, float fRight, float fBottom) { m_vOrigin = VECTOR2D(fLeft, fTop); m_vExtents = VECTOR2D(fRight-fLeft, fBottom-fTop); }
	AABB(VECTOR2D& o, VECTOR2D& s) { m_vOrigin = o; m_vExtents = s; }
	AABB(D2D1_RECT_F& r) { m_vExtents = VECTOR2D(r.right - r.left, r.bottom - r.top); m_vOrigin = VECTOR2D(r.left, r.top); }

	VECTOR2D		m_vOrigin;
    VECTOR2D		m_vExtents;

	float Left() { return(m_vOrigin.x); }
	float Right() { return(m_vOrigin.x + m_vExtents.x); }
	float Top() { return(m_vOrigin.y); }
	float Bottom() { return(m_vOrigin.y + m_vExtents.y); }
	float Width() { return(m_vExtents.x); }
	float Height() { return(m_vExtents.y); }
	VECTOR2D Center() { return(VECTOR2D(m_vOrigin.x + (m_vExtents.x * 0.5f), m_vOrigin.y + (m_vExtents.y * 0.5f))); }
	VECTOR2D Corner(int n) { VECTOR2D vCorner = m_vOrigin; if (n == 0) vCorner.x += m_vExtents.x; if (n == 1) vCorner += m_vExtents; if (n == 2) vCorner.y += m_vExtents.y; return(vCorner); }
	VECTOR2D Clamp(VECTOR2D *pV) { VECTOR2D vClamped; vClamped.x = ::fClamp(pV->x, m_vOrigin.x, m_vOrigin.x + m_vExtents.x); vClamped.y = ::fClamp(pV->y, m_vOrigin.y, m_vOrigin.y + m_vExtents.y); return(vClamped); }
	bool IsSeparatingAxis(LINESEGMENT *pS) { VECTOR2D n = (pS->m_vStart - pS->m_vEnd).Normalize(); LINESEGMENT sEdgeA(Corner(0), Corner(1)); LINESEGMENT sEdgeB(Corner(2), Corner(3)); RANGE rEdgeA = sEdgeA.Project(&n); RANGE rEdgeB = sEdgeB.Project(&n); RANGE rProject = rEdgeA.Union(&rEdgeB); RANGE rAxis = pS->Project(&n); return(!rAxis.IsOverlapping(&rProject)); }
	AABB Extend(VECTOR2D *pV) { AABB r; r.m_vOrigin.x = min(m_vOrigin.x, pV->x); r.m_vOrigin.y = min(m_vOrigin.y, pV->y); r.m_vExtents.x = max(m_vOrigin.x + m_vExtents.x, pV->x); r.m_vExtents.y = max(m_vOrigin.y + m_vExtents.y, pV->y); r.m_vExtents = r.m_vExtents - r.m_vOrigin; return(r); }
	AABB Extend(AABB *pAABB) { VECTOR2D vCorner = pAABB->m_vOrigin + pAABB->m_vExtents; AABB rcExtended = Extend(&vCorner); return(rcExtended.Extend(&pAABB->m_vOrigin)); }

	bool Contain(AABB *pAABB);

	bool Intersect(AABB *pAABB);
	bool Intersect(OOBB *pOOBB);
	bool Intersect(CIRCLE *pCircle);
	bool Intersect(LINESEGMENT *pS);

	bool Intersect(VECTOR2D *pvMoving, AABB* pAABB);
	bool Intersect(VECTOR2D *pvMoving, CIRCLE *pC);

	AABB Transform(Matrix3x2F *pd2dmtxTransform);
};

struct OOBB
{
public:
	OOBB() { m_vCenter = VECTOR2D(0.0f, 0.0f); m_vExtents = VECTOR2D(0.0f, 0.0f); m_fRotation = 0.0f; }
	OOBB(VECTOR2D& c, VECTOR2D& e, float r) { m_vCenter = c; m_vExtents = e, m_fRotation = r; }
	OOBB(D2D1_RECT_F& r, float fRotation=0.0f) { m_vExtents = VECTOR2D((r.right - r.left) * 0.5f, (r.bottom - r.top) * 0.5f); m_vCenter = VECTOR2D(r.left + m_vExtents.x, r.top + m_vExtents.y);  m_fRotation = fRotation;}

	VECTOR2D		m_vCenter;
    VECTOR2D		m_vExtents;
    float			m_fRotation;

	VECTOR2D Corner(int n) { VECTOR2D c = m_vExtents; if (n == 0) c.x = -c.x; else if (n == 2) c.y = -c.y; else if (n == 3) c = -c; c = c.Rotate(m_fRotation); return(c + m_vCenter); }
	LINESEGMENT Edge(int n) { VECTOR2D a = m_vExtents, b = m_vExtents; if (n == 0) a.x = -a.x; else if (n == 1) b.y = -b.y; else if (n == 2) { a.y = -a.y; b = -b; } else { a = -a; b.x = -b.x; } a = a.Rotate(m_fRotation); a += m_vCenter; b = b.Rotate(m_fRotation); b += m_vCenter; return(LINESEGMENT(a, b)); }
	bool IsSeparatingAxis(LINESEGMENT *pS) { LINESEGMENT sEdge0 = Edge(0); LINESEGMENT sEdge2 = Edge(2); VECTOR2D n = (pS->m_vStart - pS->m_vEnd).Normalize(); RANGE rAxis = pS->Project(&n); RANGE rRange0 = sEdge0.Project(&n); RANGE rRange2 = sEdge2.Project(&n); RANGE rProject = rRange0.Union(&rRange2); return(!rAxis.IsOverlapping(&rProject)); }
	AABB GetAABB() { AABB rcAABB(m_vCenter, VECTOR2D(0.0f, 0.0f)); for (int n = 0; n < 4; n++) { VECTOR2D vCorner = Corner(n); rcAABB = rcAABB.Extend(&vCorner); } return(rcAABB); }
	CIRCLE GetBoundingCircle() { return(CIRCLE(m_vCenter, m_vExtents.Length())); }

	bool Intersect(VECTOR2D *pV);
	bool Intersect(LINESEGMENT *pS);
	bool Intersect(OOBB *pOOBB);
	bool Intersect(AABB *pAABB);
	bool Intersect(CIRCLE *pCircle) { return(pCircle->Intersect(this)); }

	OOBB Transform(Matrix3x2F *pd2dmtxTransform) { VECTOR2D vCenter = m_vCenter.Transform(pd2dmtxTransform); return(OOBB(vCenter, m_vExtents, m_fRotation)); }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
#define LINE_LINE			0x01
#define LINE_RAY			0x02
#define LINE_SEGMENT		0x03

#define COLLIDER_AABB		0x01
#define COLLIDER_OOBB		0x02
#define COLLIDER_LINE		0x03
#define COLLIDER_RAY		0x03
#define COLLIDER_SEGMENT	0x04
#define COLLIDER_CIRCLE		0x05
#define COLLIDER_POLYGON	0x06
#define COLLIDER_MESH		0x07

class Collider
{
private:
	int								m_nReferences;
	int								m_nType;

public:
	Collider() { m_nReferences = 0; m_nType = 0; }
	Collider(int nType) { m_nReferences = 0; m_nType = nType; }
	~Collider() { }

	void AddRef() { m_nReferences++; }
	void Release() { m_nReferences--; if (m_nReferences == 0) delete this; }

	int GetType() { return(m_nType); }

	virtual void Merge(Collider* pOtherCollider) { }
	virtual void Update(Matrix3x2F* pd2dmtxTransform) { }
	virtual bool Intersect(Collider* pOtherCollider, float* pfDistance=NULL) { return(false); }

	virtual AABB GetAABB(D2D1_RECT_F* pd2drcBounds=NULL) { return(AABB(0.0f, 0.0f, 0.0f, 0.0f)); }
	virtual VECTOR2D GetSize(Matrix3x2F* pd2dmtxTransform=NULL) { return(VECTOR2D(0.0f, 0.0f)); }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CAABBCollider : public Collider
{
public:
	CAABBCollider() : Collider(COLLIDER_AABB) { m_rcBounds = AABB(VECTOR2D(0.0f, 0.0f), VECTOR2D(0.0f, 0.0f)); }
	CAABBCollider(AABB& rcBounds) : Collider(COLLIDER_AABB) { m_rcBounds = rcBounds; }
	CAABBCollider(ID2D1Geometry *pd2dGeometry);
	virtual ~CAABBCollider();

	AABB							m_rcBounds;					
	AABB							m_rcTransformedBounds;					

	virtual void Update(Matrix3x2F *pd2dmtxTransform);
	virtual bool Intersect(Collider *pOtherCollider, float *pfDistance=NULL);
	virtual VECTOR2D GetSize(Matrix3x2F *pd2dmtxTransform=NULL) { m_rcTransformedBounds = m_rcBounds.Transform(pd2dmtxTransform); return(m_rcTransformedBounds.m_vExtents); }

	virtual AABB GetAABB(D2D1_RECT_F *pd2drcBounds=NULL);
	AABB GetBounds(D2D1_RECT_F *pd2drcBounds=NULL);
	AABB GetTransformedBounds(Matrix3x2F *pd2dmtxTransform=NULL, D2D1_RECT_F *pd2drcBounds=NULL);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class COOBBCollider : public Collider
{
public:
	COOBBCollider() : Collider(COLLIDER_OOBB) { m_rcBounds = OOBB(VECTOR2D(0.0f, 0.0f), VECTOR2D(0.0f, 0.0f), 0.0f); }
	COOBBCollider(OOBB& rcBounds) : Collider(COLLIDER_OOBB) { m_rcBounds = rcBounds; }
	COOBBCollider(ID2D1Geometry *pd2dGeometry);
	virtual ~COOBBCollider();

	OOBB							m_rcBounds;					
	OOBB							m_rcTransformedBounds;					

	virtual void Update(Matrix3x2F *pd2dmtxTransform);
	virtual bool Intersect(Collider *pOtherCollider, float *pfDistance=NULL);
	virtual VECTOR2D GetSize(Matrix3x2F *pd2dmtxTransform=NULL) { m_rcTransformedBounds = m_rcBounds.Transform(pd2dmtxTransform); return(m_rcTransformedBounds.m_vExtents * 2.0f); }

	virtual AABB GetAABB(D2D1_RECT_F *pd2drcBounds=NULL);
	OOBB GetBounds(D2D1_RECT_F *pd2drcBounds=NULL);
	OOBB GetTransformedBounds(Matrix3x2F *pd2dmtxTransform=NULL) { m_rcTransformedBounds = m_rcBounds.Transform(pd2dmtxTransform); return(m_rcTransformedBounds); }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CCircleCollider : public Collider
{
public:
	CCircleCollider() : Collider(COLLIDER_CIRCLE) { m_ccBounds = CIRCLE(VECTOR2D(0.0f, 0.0f), 0.0f); }
	CCircleCollider(CIRCLE& ccBounds) : Collider(COLLIDER_CIRCLE) { m_ccBounds = ccBounds; }
	CCircleCollider(ID2D1Geometry *pd2dGeometry);
	virtual ~CCircleCollider();

	CIRCLE							m_ccBounds;					
	CIRCLE							m_ccTransformedBounds;					

	virtual void Update(Matrix3x2F *pd2dmtxTransform);
	virtual bool Intersect(Collider *pOtherCollider, float *pfDistance=NULL);
	virtual VECTOR2D GetSize(Matrix3x2F *pd2dmtxTransform=NULL) { return(VECTOR2D(m_ccBounds.m_fRadius, m_ccBounds.m_fRadius)); }

	virtual AABB GetAABB(D2D1_RECT_F *pd2drcBounds=NULL);
	CIRCLE GetBounds(D2D1_ELLIPSE *pd2dEllipse=NULL);
	CIRCLE GetTransformedBounds(Matrix3x2F *pd2dmtxTransform=NULL) { m_ccTransformedBounds = m_ccBounds.Transform(pd2dmtxTransform); return(m_ccTransformedBounds); }
};
