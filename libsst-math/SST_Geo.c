#include <math.h>
#include <SST/SST_Vec2.h>
#include <SST/SST_Vec3.h>
#include <SST/SST_Math.h>
#include <SST/SST_Geo.h>

/*
    Helper function to find intersection(s) of two line segments.
    This is adapted from "Geometric Tools For Computer Graphpics", p. 244.

    Note that the segments are being represented here by a start point and a distance offset vector,
    P and D, assuming that the full segment can be represented by the equation:
    
        L(t) = P + tD, where t is on the range [0,1]
*/

#define sqrEpsilon (0.0001f)

static SST_2DLineSegmentIntersectType doFindIntersection( float u0, float u1, float v0, float v1, float w[2])
{
    if ( u1 < v0 || u0 > v1 )
    {
        return SST2DLINESEGINTERSECT_NONE;
    }

    if ( u1 > v0 )
    {
        if (u0 < v1)
        {
            w[0] = (u0 < v0) ? (v0) : (u0);
            w[1] = (u1 > v1) ? (v1) : (u1);
            return SST2DLINESEGINTERSECT_OVERLAP;
        }
        else
        {
            w[0] = u0;
            return SST2DLINESEGINTERSECT_POINT;
        }        
    }
    else
    {
        w[0] = u1;
        return SST2DLINESEGINTERSECT_POINT;
    }
}

SST_2DLineSegmentIntersectType doSegmentSegmentIntersectionF(   const SST_Vec2f* RESTRICT P0,
                                                                const SST_Vec2f* RESTRICT D0,
                                                                const SST_Vec2f* RESTRICT P1,
                                                                const SST_Vec2f* RESTRICT D1,
                                                                SST_Vec2f* RESTRICT overlaps)
{
    SST_Vec2f e;
    float kross;
    float kross2;
    float sqrKross;
    float sqrKross2;
    float sqrLen0;
    float sqrLen1;
    float sqrLenE;
    float s;
    float t;
    float s0;
    float s1;
    float w[2];
    float smin;
    float smax;
    SST_2DLineSegmentIntersectType itype;

    SST_Math_Vec2fSubtract(P1, P0, &e);

    /*
    Note on the kross operator:

    Kross(a,b) = (ax*by) - (bx*ay)
    */
    kross = ((D0->x)*(D1->y)) - ((D0->y)*(D1->x));
    sqrKross = kross * kross;
    sqrLen0 = ((D0->x) * (D0->x)) + ((D0->y) * (D0->y));
    sqrLen1 = ((D1->x) * (D1->x)) + ((D1->y) * (D1->y));

    if (sqrKross > sqrEpsilon * sqrLen0 * sqrLen1)
    {
        s = ((e.x * D1->y) - (e.y * D1->x)) / kross;
        if (s < 0.0f || s > 1.0f)
        {
            return SST2DLINESEGINTERSECT_NONE;
        }

        t = ((e.x * D0->y) - (e.y * D0->x)) / kross;
        if (t < 0.0f || t > 1.0f)
        {
            return SST2DLINESEGINTERSECT_NONE;
        }

        SST_Math_Vec2fWeightedSum(P0, 1.0f, D0, s, overlaps);

        return SST2DLINESEGINTERSECT_POINT;
    }

    sqrLenE = (e.x * e.x) + (e.y * e.y);

    kross2 = ((e.x)*(D0->y)) - ((e.y)*(D0->x));
    sqrKross2 = kross2 * kross2;

    if (sqrKross2 > sqrEpsilon * sqrLen0 * sqrLenE )
    {
        return SST2DLINESEGINTERSECT_NONE;
    }

    s0 = SST_Math_Vec2fDot( D0, &e) / sqrLen0;
    s1 = s0 + SST_Math_Vec2fDot( D0, D1) / sqrLen0;
    smin = s0 < s1 ? s0 : s1;
    smax = s0 > s1 ? s0 : s1;

    itype = doFindIntersection(0.0f, 1.0f, smin, smax, w);

    switch (itype) {
        case SST2DLINESEGINTERSECT_NONE: break;
        case SST2DLINESEGINTERSECT_POINT:
                                            SST_Math_Vec2fWeightedSum(P0, 1.0f, D0, w[0], &(overlaps[0]) );

                                            break;
        case SST2DLINESEGINTERSECT_OVERLAP:
                                            SST_Math_Vec2fWeightedSum(P0, 1.0f, D0, w[0], &(overlaps[0]) );
                                            SST_Math_Vec2fWeightedSum(P0, 1.0f, D0, w[1], &(overlaps[1]) );

                                            break;
        default: break;
    }

    return itype;
}

/*
    Main driver function, mostly just handles moving from the way we think about line segments,
    using start and end points, to the way the routine thinks about things, using origin and offset.

*/
SST_2DLineSegmentIntersectType SST_Geo_2DSegmentSegmentIntersectionF(  const SST_Vec2f* RESTRICT Astart,
                                                                       const SST_Vec2f* RESTRICT Aend,
                                                                       const SST_Vec2f* RESTRICT Bstart,
                                                                       const SST_Vec2f* RESTRICT Bend,
                                                                       SST_Vec2f* RESTRICT overlaps)
{
    SST_Vec2f p0;   // starting point of first line segment
    SST_Vec2f d0;   // the offset of the first line segment
    SST_Vec2f p1;   // starting point of the second line segment
    SST_Vec2f d1;   // the offset of the second line segment

    // store starting points of rays
    memmove( &p0, Astart, sizeof(SST_Vec2f) );
    memmove( &p1, Bstart, sizeof(SST_Vec2f) );

    // grab the offset of the segment from the origin
    SST_Math_Vec2fSubtract(Aend, Astart, &d0);
    SST_Math_Vec2fSubtract(Bend, Bstart, &d1);

    return doSegmentSegmentIntersectionF(&p0, &d0, &p1, &d1, overlaps);
}

float PointToPoint2f(const SST_Vec2f* a,const SST_Vec2f* b)
{
	SST_Vec2f temp;
	SST_Math_Vec2fSubtract(a,b,&temp);
	return SST_Math_Vec2fMagnitude(&temp);
}
float PointToPointSquared2f(const SST_Vec2f* a,const SST_Vec2f* b)
{
	SST_Vec2f temp;
	SST_Math_Vec2fSubtract(a,b,&temp);
	return SST_Math_Vec2fMagnitudeSquared(&temp);
}
double PointToPoint2d(const SST_Vec2d* a,const SST_Vec2d* b)
{
	SST_Vec2d temp;
	SST_Math_Vec2dSubtract(a,b,&temp);
	return SST_Math_Vec2dMagnitude(&temp);
}
double PointToPointSquared2d(const SST_Vec2d* a,const SST_Vec2d* b)
{
	SST_Vec2d temp;
	SST_Math_Vec2dSubtract(a,b,&temp);
	return SST_Math_Vec2dMagnitudeSquared(&temp);
}
float PointToLineSegment2f(SST_Vec2f* close, const SST_Vec2f* a, const SST_Vec2f* b)
{
	/* Line segment b is defined with two points b[0:1] and b[2:3] */
	SST_Vec2f temp;
	float t;
	float distsqr;

	temp.v[0] = b[1].v[0]-b[0].v[0];
	temp.v[1] = b[1].v[1]-b[0].v[1];
	distsqr = SST_Math_Vec2fMagnitudeSquared(&temp);
	t = ((a->v[0]-b[0].v[0]) * temp.v[0] + (a->v[1]-b[0].v[1]) * temp.v[1] ) / distsqr;
	if(t>1.f)
		t = 1.f;
	if(t<0.f)
		t = 0.f;

	/* close[i] = b[i]+ t * temp[i]; */
	SST_Math_Vec2fScale(&temp,t,close);
	SST_Math_Vec2fAddLocal(close,b);

	/* temp[i] = close[i]-a[i]; */
	SST_Math_Vec2fSubtract(close,a,&temp);
	
	return SST_Math_Vec2fMagnitude(&temp);
}
double PointToLineSegment2d(SST_Vec2d* close, const SST_Vec2d* a, const SST_Vec2d* b)
{
	/* Line segment b is defined with two points b[0:1] and b[2:3] */
	SST_Vec2d temp;
	double t;
	double distsqr;
	temp.v[0] = b[1].v[0]-b[0].v[0];
	temp.v[1] = b[1].v[1]-b[0].v[1];
	distsqr = SST_Math_Vec2dMagnitudeSquared(&temp);
	t = ((a->v[0]-b[0].v[0])*temp.v[0] + (a->v[1]-b[0].v[1])*temp.v[1]) / distsqr;
	if(t>1.0)
		t = 1.0;
	if(t<0.0)
		t = 0.0;

	/* close[i] = b[i]+ t * temp[i]; */
	SST_Math_Vec2dScale(&temp,t,close);
	SST_Math_Vec2dAddLocal(close,b);

	//temp[i] = close[i]-a[i];
	SST_Math_Vec2dSubtract(close,a,&temp);
	
	return SST_Math_Vec2dMagnitude(&temp);
}

float PointToPoint3f(const SST_Vec3f* a,const SST_Vec3f* b)
{
	SST_Vec3f temp;
	SST_Math_Vec3fSubtract(a,b,&temp);
	return SST_Math_Vec3fMagnitude(&temp);
}
float PointToPointSquared3f(const SST_Vec3f* a,const SST_Vec3f* b)
{
	SST_Vec3f temp;
	SST_Math_Vec3fSubtract(a,b,&temp);
	return SST_Math_Vec3fMagnitudeSquared(&temp);
}
float PointToLineSegment3f(SST_Vec3f* close, const SST_Vec3f* a, const SST_Vec3f* b)
{
	/* Line segment b is defined with two points b[0:1] and b[2:3] */
	SST_Vec3f temp;
	float t;
	float distsqr;
	temp.v[0] = b[1].v[0]-b[0].v[0];
	temp.v[1] = b[1].v[1]-b[1].v[1];
	temp.v[2] = b[1].v[2]-b[2].v[2];
	distsqr = SST_Math_Vec3fMagnitudeSquared(&temp);
	t = ((a->v[0]-b[0].v[0])*temp.v[0] + (a->v[1]-b[0].v[1])*temp.v[1]+(a->v[2]-b[0].v[2])*temp.v[2]) / distsqr;
	if(t>1.f)
		t = 1.f;
	if(t<0.f)
		t = 0.f;

	/* close[i] = b[i]+ t * temp[i]; */
	SST_Math_Vec3fScale(&temp,t,close);
	SST_Math_Vec3fAddLocal(close,b);

	/* temp[i] = close[i]-a[i]; */
	SST_Math_Vec3fSubtract(close,a,&temp);
	
	return SST_Math_Vec3fMagnitude(&temp);
}
double PointToPoint3d(const SST_Vec3d* a,const SST_Vec3d* b)
{
	SST_Vec3d temp;
	SST_Math_Vec3dSubtract(a,b,&temp);
	return SST_Math_Vec3dMagnitude(&temp);
}
double PointToPointSquared3d(const SST_Vec3d* a,const SST_Vec3d* b)
{
	SST_Vec3d temp;
	SST_Math_Vec3dSubtract(a,b,&temp);
	return SST_Math_Vec3dMagnitudeSquared(&temp);
}
double PointToLineSegment3d(SST_Vec3d* close, const SST_Vec3d* a, const SST_Vec3d* b)
{
	/* Line segment b is defined with two points b[0:1] and b[2:3] */
	SST_Vec3d temp;
	double t;
	double distsqr;
	temp.v[0] = b[1].v[0]-b[0].v[0];
	temp.v[1] = b[1].v[1]-b[0].v[1];
	temp.v[2] = b[1].v[2]-b[0].v[2];
	distsqr = SST_Math_Vec3dMagnitudeSquared(&temp);
	t = ((a->v[0]-b[0].v[0])*temp.v[0] + (a->v[1]-b[0].v[1])*temp.v[1]+(a->v[2]-b[0].v[2])*temp.v[2]) / distsqr;
	if(t>1.0)
		t = 1.0;
	if(t<0.0)
		t = 0.0;

	/* close[i] = b[i]+ t * temp[i]; */
	SST_Math_Vec3dScale(&temp,t,close);
	SST_Math_Vec3dAddLocal(close,b);

	/* temp[i] = close[i]-a[i]; */
	SST_Math_Vec3dSubtract(close,a,&temp);
	
	return SST_Math_Vec3dMagnitude(&temp);
}

double PointToPlane3(const SST_Vec3d* a, const SST_Vec3d plane[3])
{
#pragma message("PointToPlane3-NOT IMPLEMENTED YET")
	return (double)(0.0);
}
#include <stdio.h>
bool SST_Geo_RayPlaneIntersectionD(const SST_Vec3d* RESTRICT ray, const SST_Vec3d* RESTRICT ray_point, const SST_Vec3d* RESTRICT p0, const SST_Vec3d* RESTRICT p1,const SST_Vec3d* RESTRICT p2, SST_Vec3d* RESTRICT Intersection)
{
	/* 
	 *  The x=inv(A)*b
	 [t; u; v] = [l_a-l_b, p1-p0, p2-p0]^-1 * [l_a-p0] 
	Source: Wiki
	In this formulation (to save on computation, t is actually -t from the wiki)
	 */

	SST_Vec3d  s;
	SST_Mat33d A;
	double t;
	bool inTriangle;
	inTriangle = false;

	/* First column */
	SST_Math_Mat33dFromVec3d(&A,ray_point,0);

	/* Second column */
	SST_Math_Vec3dSubtract(p1,p0,&s);
	SST_Math_Mat33dFromVec3d(&A,&s,1);

	/* Third column */
	SST_Math_Vec3dSubtract(p2,p0,&s);
	SST_Math_Mat33dFromVec3d(&A,&s,2);

	/* form b */
	SST_Math_Vec3dSubtract(ray,p0,&s);
	SST_Math_Mat33dCreateLULocal(&A);
	SST_Math_Mat33dApplyLUVec(&A,&s,Intersection);

	/* if u,v in [0,1] and (u+v) <= 1:
	 * ==> then the intersection point is in the plane inside the triangle spanned by the three points p_{i}
	 */
#define SST_Math_RangeContains(x,a,b) ( ( (x) >= a ) & ( (x) <= b ) )
	//printf("t %f, u %f, v %f\n",Intersection->x, Intersection->y, Intersection->z);
	if(SST_Math_RangeContains(Intersection->v[1],0.0,1.0) & SST_Math_RangeContains(Intersection->v[2],0.0,1.0) & SST_Math_RangeContains(Intersection->v[1]+Intersection->v[2],0.0,1.0)) { 
		inTriangle = true; 
	}
#undef SST_Math_RangeContains
	/* calculate intersection point */
	t = -Intersection->v[0];
	/* ray_point + Intersection->v[0] * ray */
	SST_Math_Vec3dScale(ray,t,Intersection);
	SST_Math_Vec3dAddLocal(Intersection,ray_point);

	return inTriangle;
}
bool SST_Geo_RayPlaneIntersectionF(const SST_Vec3f* RESTRICT ray, const SST_Vec3f* RESTRICT ray_point, const SST_Vec3f* RESTRICT p0, const SST_Vec3f* RESTRICT p1,const SST_Vec3f* RESTRICT p2, SST_Vec3f* RESTRICT Intersection)
{
	/* 
	 *  The x=inv(A)*b
	 [t; u; v] = [l_a-l_b, p1-p0, p2-p0]^-1 * [l_a-p0] 
	Source: Wiki
	 */

	SST_Vec3f  s;
	SST_Mat33f A;
	float t;
	bool inTriangle;
	inTriangle = false;

	/* First column */
	SST_Math_Mat33fFromVec3f(&A,ray_point,0);

	/* Second column */
	SST_Math_Vec3fSubtract(p1,p0,&s);
	SST_Math_Mat33fFromVec3f(&A,&s,1);

	/* Third column */
	SST_Math_Vec3fSubtract(p2,p0,&s);
	SST_Math_Mat33fFromVec3f(&A,&s,2);

	/* form b */
	SST_Math_Vec3fSubtract(ray,p0,&s);
	SST_Math_Mat33fCreateLULocal(&A);
	SST_Math_Mat33fApplyLUVec(&A,&s,Intersection);

	/* if u,v in [0,1] and (u+v) <= 1:
	 * ==> then the intersection point is in the plane inside the triangle spanned by the three points p_{i}
	 */
#define SST_Math_RangeContains(x,a,b) ( ( (x) >= a ) & ( (x) <= b ) )
	//printf("t %f, u %f, v %f\n",Intersection->x, Intersection->y, Intersection->z);
	if(SST_Math_RangeContains(Intersection->v[1],0.0f,1.0f) & SST_Math_RangeContains(Intersection->v[2],0.0f,1.0f) & SST_Math_RangeContains(Intersection->v[1]+Intersection->v[2],0.0f,1.0f)) { 
		inTriangle = true; 
	}
#undef SST_Math_RangeContains
	/* calculate intersection point */
	t = -Intersection->v[0];
	/* ray_point + Intersection->v[0] * ray */
	SST_Math_Vec3fScale(ray,t,Intersection);
	SST_Math_Vec3fAddLocal(Intersection,ray_point);

	return inTriangle;
}
