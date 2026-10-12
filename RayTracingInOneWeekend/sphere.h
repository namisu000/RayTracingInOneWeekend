#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere(const point3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override
    {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        auto root = (h - sqrtd) / a;              // 작은 근 = 가까운 교차점 우선
        if (root <= ray_tmin || ray_tmax <= root) // 작은 근이 범위 밖이면
        {
            root = (h + sqrtd) / a;                   // 큰 근(먼 교차점) 시도. ex) 카메라가 구 안
            if (root <= ray_tmin || ray_tmax <= root) // 큰 근도 범위 밖이면
                return false;                         // 유효한 교차 없음
        }

        rec.t = root;                                    // 구한 t 갱신
        rec.p = r.at(rec.t);                             // t를 넣어서 교차점 좌표 P를 구함
        vec3 outward_normal = (rec.p - center) / radius; // P로 법선 계산
        rec.set_face_normal(r, outward_normal);          // normal 및 face 계산
        return true;
    }

private:
    point3 center;
    double radius;
};

#endif