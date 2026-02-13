#pragma once

#include <imgui.h>

class ImGuiUtilities
{
public:
	static constexpr ImU32 Color(const unsigned _r, const unsigned _g, const unsigned _b, const unsigned _a = 0u) noexcept
	{
		return (_r << 24) | (_g << 16) | (_b << 8) | _a;
	}

	//static constexpr ImU32 Red = Color(255u, 0u, 0u, 0u);
};
