#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;
using namespace std;

void write_color(ostream& out, const color& pixel_color) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// [0,1] 범위의 값을 [0,255] 정수로 변환
	// 255.999를 곱하는 이유: int()는 소수점을 버리므로 255를 곱하면 1.0일 때만 255가 됨
	// 255.999를 곱하면 0~255 구간이 고르게 나뉘고, 1.0도 255로 떨어짐
	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	//출력
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
#endif