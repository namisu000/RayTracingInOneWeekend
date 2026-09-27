#include "vec3.h"
#include "color.h"

#include<iostream>
using namespace std;
int main()
{
	//image 
	int image_width = 256;
	int image_height = 256;

	//render
	cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int i = 0; i < image_width; i++) {
		clog << "\rScanlines remaining: " << (image_width - i) << ' ' << flush;
		for (int j = 0; j < image_height; j++)
		{
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			auto pixel_color = color(r, g, b);
			write_color(cout, pixel_color);
		}

		clog << "\rDone.\n";
	}
}