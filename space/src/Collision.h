#pragma once
#include "Vec2.h"
#include <stdio.h>

#define DELTA .000001

struct Ray{
	vec2 origin;
	float angle;
};

struct Line{
	vec2 pos;
	vec2 dir;
};

struct Plane{
	vec2 pos;
	vec2 n;
};

struct Segment{
	vec2 a;
	vec2 b;
	vec2 n;
};

struct AABB{
	float top;
	float left;
	float bottom;
	float right;
};

struct fixture{
	vec2 pos;
	AABB bounds;
};

float distanceToPlane(Line l, Plane p);

float distanceToSegment(Line l, Segment s);

int intersectsWithPlane(Line l, Plane p);

bool rayCircleIntersect(vec2 c_pos, float c_rad, vec2 r_end, vec2 r_start, vec2 &intersect_point);

bool checkAABBIntersect(AABB a, vec2 apos, AABB b, vec2 bpos, Plane& axisOfIntersection);
