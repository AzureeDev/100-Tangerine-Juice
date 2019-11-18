#pragma once
#include <SDL.h>
#include <string>
#include <vector>

enum class ColorIndex {
	Red,
	Green,
	Blue,
	Alpha
};

// SDL_Color but with floats | 0 = 0, 1 = 255
typedef struct FColor {
	float r;
	float g;
	float b;
	float a;
} FColor;

struct Utils
{
	static std::vector<unsigned int> unpackColor(const SDL_Color& color);

	template <typename Nb>
	static Nb clamp(Nb number, const Nb min, const Nb max);
	static float lerp(const float a, const float b, const float t);
	static SDL_Color colorLerp(const FColor a, const FColor b, float t);
	static const std::string getDateTime();
};

template<typename Nb>
inline Nb Utils::clamp(Nb number, const Nb min, const Nb max)
{
	number = number > max ? max : number;
	number = number < min ? min : number;

	return number;
}