#ifndef PMTRACER_VIEWPLANE_H
#define PMTRACER_VIEWPLANE_H

#include <memory>
#include "Regular.h"

namespace pm {

class ViewPlane
{
public:
	ViewPlane() : width_(1920), height_(1080), pixelSize_(1.0f), gamma_(1.0f),
	  invGamma_(1.0f / gamma_), maxDepth_(1), sampler_(std::make_unique<Regular>(1)) { }

	inline int width() const { return width_; }
	inline void setWidth(int width) { width_ = width; }
	inline int height() const { return height_; }
	inline void setHeight(int height) { height_ = height; }
	inline void setDimensions(int width, int height) { width_ = width; height_ = height; }

	inline float pixelSize() const { return pixelSize_; }
	inline void setPixelSize(float pixelSize) { pixelSize_ = pixelSize; }
	inline float gamma() const { return gamma_; }
	inline void setGamma(float gamma) { gamma_ = gamma; invGamma_ = 1.0f / gamma; }
	inline int maxDepth() const { return maxDepth_; }
	inline void setMaxDepth(int maxDepth) { maxDepth_ = maxDepth; }

	inline Sampler &sampler() const { return *sampler_; }
	inline void setSampler(std::unique_ptr<Sampler> sampler) { sampler_ = std::move(sampler); }

private:
	int width_;
	int height_;
	float pixelSize_;
	float gamma_;
	float invGamma_;
	int maxDepth_;
	std::unique_ptr<Sampler> sampler_;
};

}

#endif
