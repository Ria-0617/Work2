#pragma once
#include "cinder/app/AppNative.h"

namespace MyFanc {
	template<typename T>
	T Clamp(T value, T minValue, T maxValue) {
		return value > maxValue ? maxValue : (value < minValue ? minValue : value);
	}

	template<typename T>
	inline void Console(T show) {
		ci::app::console() << show << std::endl;
	}

	inline ci::Vec3f ToRadians(const ci::Vec3f& degrees) {
		return degrees * (float)M_PI / 180.f;
	}

	inline ci::Vec3f ToDegrees(const ci::Vec3f& radians) {
		return radians * 180.f / (float)M_PI;
	}

	inline bool CircleCollider(ci::Vec3f objPos,float radius, ci::Vec3f objPos2, float radius2) {
		return objPos.distance(objPos2) < radius + radius2 ? true : false;
	}
}
