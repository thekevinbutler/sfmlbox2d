//utility functions

namespace convert
{
	const double PIXELS_PER_METER = 128.0; 
	const double PI = 3.14159265358979323846;
	template<typename T>
	const T pixelsToMeters(const T& x)
	{
		return x / PIXELS_PER_METER;
	};
	template<typename T>
	const T metersToPixels(const T& x)
	{
		return x*PIXELS_PER_METER;
	}
	template<typename T>
	const T degToRad(const T& x)
	{ 
		return PI*x / 180.0; 
	}
	template<typename T>
	const T radToDeg(const T& x){ return 180.0*x / PI; }
}