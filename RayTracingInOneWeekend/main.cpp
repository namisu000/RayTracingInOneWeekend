#include "vec3.h"
#include "color.h"
#include "ray.h"

#include<iostream>
using namespace std;

color ray_color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0); //unit_direction y의 범위를 [0, 1]로 변환. -1에서 1 사이이니. 1.0을 더하고 0, 2로 변환, 이후 / 2
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); //선형보긴
}

int main()
{
	//image 
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = int(image_width / aspect_ratio); //높이 결정하면 width는 height에 ratio를 곱한 값으로 결정 됨.
	image_height = (image_height < 1) ? 1 : image_height;

	auto focal_length = 1.0;
	// 뷰포트는 3D 세계 안에 있는 가상의 직사각형으로, 이미지 픽셀 위치들의 격자를 담고 있다. 장면의 광선들이 통과할 지점.
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);
	// viewport_width를 계산할 때 왜 그냥 aspect_ratio를 쓰지 않는 이유 <  image_width, height는 int로 변환된 값이라. 실제 비율과 다를 수 있어서.

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	auto viewport_u = vec3(viewport_width, 0, 0); 
	auto viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_u = viewport_u / image_width; //픽셀 간격
	auto pixel_delta_v = viewport_v / image_height;
	//뷰포트 = 실수 좌표로 정의된 연속적인 사각형 영역. 그 위의 어느 점이든 광선을 쏠 수 있다
	//이미지 = 그 연속된 영역을 몇 개의 점으로 샘플링할지 정한 것.
	//그래서 image_width/height로 나눠서 뷰포트를 픽셀 수만큼의 칸으로 쪼갬.

	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; 
	// 카메라 위치에서 -z로 focal_length만큼 간 곳이 뷰포트 중심, 거기서 u/2, v/2를 빼서 upper_left를 구함
	// 뷰포트 크기는 viewport_height(2.0)와 이미지 비율로 정해짐 (이미지 해상도와는 무관)
	// 이미지 해상도는 뷰포트를 몇 칸으로 나눌지(pixel_delta)만 결정
	// viewport_v는 아래 방향이라 빼면 위로 올라감

	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // (0,0) 픽셀 칸의 중심. 



	//render
	cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int i = 0; i < image_width; i++) {
		clog << "\rScanlines remaining: " << (image_width - i) << ' ' << flush;
		for (int j = 0; j < image_height; j++)
		{
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
			write_color(cout, pixel_color);
		}

		clog << "\rDone.\n";
	}
}