#pragma once
extern int width;
extern int height;

namespace CCraft
{
	class Button
	{
	public:
		bool mousedOver = false;
		bool pressed = false;
		float* data;
		float recalculatedData[4];
	public:
		Button(float data[]);
	private:
		void recalculateForResolution();
		void recalculateForGLFW();
	};
}