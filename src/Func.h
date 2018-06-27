#pragma once
#include "cinder/app/AppNative.h"

namespace MyFanc {
	template<typename T>
	T Clamp(T value, T minValue, T maxValue) {
		return value > maxValue ? maxValue : (value < minValue ? minValue : value);
	}

	inline ci::Vec3f Vec3fClamp(ci::Vec3f value, ci::Vec3f minValue, ci::Vec3f maxValue) {
		value.x = value.x > maxValue.x ? maxValue.x : (value.x < minValue.x ? minValue.x : value.x);
		value.y = value.y > maxValue.y ? maxValue.y : (value.y < minValue.y ? minValue.y : value.y);
		value.z = value.z > maxValue.z ? maxValue.z : (value.z < minValue.z ? minValue.z : value.z);

		return value;
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

	inline bool CircleCollider(ci::Vec3f pos, float radius, ci::Vec3f pos2, float radius2) {
		return pos.distance(pos2) < radius + radius2 ? true : false;
	}
}

