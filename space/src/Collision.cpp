#include "Collision.h"

float distanceToPlane(Line l, Plane p){
	float d;
	float ldotn = dot((l.dir - l.pos).normalize(), p.n);
	if (fabs(ldotn) < DELTA){
		return -1;
	}
	d = dot(p.pos - l.pos, p.n) / ldotn;
	return d;
	
}

float distanceToSegment(Line l, Segment s){
	Plane p;
	p.pos = s.a;
	p.n = s.n;
	float d = distanceToPlane(l, p);
	
	if (d == -1) return d;
	
}

int intersectsWithPlane(Line l, Plane p){
	float d = distanceToPlane(l, p);
	float len = (l.pos-l.dir).length();
	
	if (d > len){
		return 0;
	}
	
	if (d < 0){
		return 0;
	}
	
	return 1;
}

bool rayCircleIntersect(vec2 c_pos, float c_rad, vec2 r_end, vec2 r_start, vec2 &intersect_point){
	// found at http://stackoverflow.com/questions/1073336/circle-line-collision-detection
	// thanks, anonymous dude!

	vec2 f = r_start - c_pos;
	vec2 r_dir = r_end - r_start;
	float a = dot(r_dir,r_dir);
	float b = 2*dot(f,r_dir);
	float c = dot(f,f) - pow(c_rad,2);
	
	float disc = b*b-4*a*c;
	
	if (disc < 0){
		return false;
	}
	
	disc = sqrt(disc);
	
	float t1 = (-b + disc)/(2*a);
	float t2 = (-b -disc)/(2*a);
	
	if (t2>=0 && t2<=1){
		// t2 sol is on ray
		intersect_point = r_start + r_dir * t2;
		return true;
	}
	else {
		//t2 sol out of range
		return false;
	}
	
	if (t1 >=0 && t1<=1){
		// t1 sol is on ray
		intersect_point = r_start + r_dir * t1;
		return true;
	}
	else {
		// t1 sol out of range
		return false;
	}
	
	
	
}

bool checkAABBIntersect(AABB ab, vec2 abpos, AABB ab2, vec2 ab2pos, Plane& axisOfIntersect){
	vec2 diff = abpos - ab2pos;
	if (ab.right + diff.x < ab2.left ||
	    ab.top + diff.y < ab2.bottom ||
	    ab.left + diff.x > ab2.right ||
	    ab.bottom + diff.y > ab2.top){
			return false;
	    }
	    
	float l = fabs(ab2.left - (ab.right + diff.x));
	float r = fabs(ab2.right - (ab.left + diff.x));
	float t = fabs(ab2.top - (ab.bottom + diff.y));
	float b = fabs(ab2.bottom - (ab.top + diff.y));

	axisOfIntersect.pos = vec2(ab2pos.x, ab2pos.y);
	axisOfIntersect.n = vec2(0,0);
	
	if (l <= r && l <= t && l <= b){
		axisOfIntersect.pos.x = ab2.left + ab2pos.x;
		axisOfIntersect.n = vec2(-1,0);
	}	
	
	if (r <= l && r <= t && r <= b){
		axisOfIntersect.pos.x = ab2.right + ab2pos.x;
		axisOfIntersect.n = vec2(1,0);
	}
	
	if (t <= l && t <= r && t <= b){
		axisOfIntersect.pos.y = ab2.top + ab2pos.y;
		axisOfIntersect.n = vec2(0,1);
	}	
	
	if (b <= l && b <= r && b <= t){
		axisOfIntersect.pos.y = ab2.bottom + ab2pos.y;
		axisOfIntersect.n = vec2(0,-1);
	}
	
	return true;
}
