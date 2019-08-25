#ifndef PMTRACER_VIEWPLANE_H
#define PMTRACER_VIEWPLANE_H

#include "SamplerState.h"

namespace pm {

class Sampler;

class ViewPlane
{
  public:
	ViewPlane()
	    : width_(1920), height_(1080), pixelSize_(1.0f), gamma_(1.0f),
	      invGamma_(1.0f / gamma_), maxDepth_(1) {}

	inline int width() const { return width_; }
	inline int &editWidth() { return width_; }
	inline int height() const { return height_; }
	inline int &editHeight() { return height_; }
	void setDimensions(int width, int height);

	inline float pixelSize() const { return pixelSize_; }
	inline float &editPixelSize() { return pixelSize_; }
	inline float gamma() const { return gamma_; }
	void setGamma(float gamma);
	inline int maxDepth() const { return maxDepth_; }
	inline int &editMaxDepth() { return maxDepth_; }

	inline const SamplerState &samplerState() const { return samplerState_; }

	const Sampler *sampler() const { return samplerState_.sampler(); }
	Sampler *sampler() { return samplerState_.sampler(); }
	inline void setSampler(Sampler *sampler) { samplerState_.setSampler(sampler); }

  private:
	int width_;
	int height_;
	float pixelSize_;
	float gamma_;
	float invGamma_;
	int maxDepth_;
	SamplerState samplerState_;
};

inline void ViewPlane::setDimensions(int width, int height)
{
	width_ = width;
	height_ = height;
}

inline void ViewPlane::setGamma(float gamma)
{
	gamma_ = gamma;
	invGamma_ = 1.0f / gamma;
}

}

#endif
