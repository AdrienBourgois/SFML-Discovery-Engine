#pragma once

#include "Texture.h"

class AnimatedTileSet : public Texture
{
public:
	explicit AnimatedTileSet(const std::string& _path) : Texture(_path) {}

	void SetSpeed(float& _speed) const
	{
		_speed = speed;
	}

	float GetSpeed() const
	{
		return speed;
	}

private:
	float speed = 0.5f;
};
