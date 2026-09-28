#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

	const point3& origin() const { return orig; } 
	const point3& direction() const { return dir; }
	//앞 const : 반환된 참조로 수정 불가
	//뒤 const : 이 함수 안에서 멤버 수정 불가

	point3 at(double t) const {
		return orig + t*dir;
	}

private:
	point3 orig; //시작위치 (A)
	vec3 dir; //방향 (b)
};

#endif