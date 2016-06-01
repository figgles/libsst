#ifndef __SST_GEO_H__
#define __SST_GEO_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SST_2DLineSegmentIntersectType {
	SST2DLINESEGINTERSECT_NONE,
	SST2DLINESEGINTERSECT_POINT,
	SST2DLINESEGINTERSECT_OVERLAP
} SST_2DLineSegmentIntersectType;

SST_2DLineSegmentIntersectType SST_Geo_2DSegmentSegmentIntersectionF(  const SST_Vec2f* RESTRICT Astart,
                                                                       const SST_Vec2f* RESTRICT Aend,
                                                                       const SST_Vec2f* RESTRICT Bstart,
                                                                       const SST_Vec2f* RESTRICT Bend,
                                                                       SST_Vec2f* RESTRICT overlaps);
bool SST_Geo_RayPlaneIntersectionF(const SST_Vec3f* RESTRICT ray, const SST_Vec3f* RESTRICT ray_point, const SST_Vec3f* RESTRICT p0, const SST_Vec3f* RESTRICT p1,const SST_Vec3f* RESTRICT p2, SST_Vec3f* RESTRICT Intersection);
bool SST_Geo_RayPlaneIntersectionD(const SST_Vec3d* RESTRICT ray, const SST_Vec3d* RESTRICT ray_point, const SST_Vec3d* RESTRICT p0, const SST_Vec3d* RESTRICT p1,const SST_Vec3d* RESTRICT p2, SST_Vec3d* RESTRICT Intersection);

#ifdef __cplusplus
}
#endif

#endif
