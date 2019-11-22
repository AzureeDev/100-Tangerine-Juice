#include "Utils.h"
#include <time.h>
#include <algorithm>
#define NOMINMAX
#include <Windows.h>
#include <random>

std::vector<unsigned int> Utils::unpackColor(const SDL_Color& color)
{
	return std::vector<unsigned int>({
		color.r,
		color.g,
		color.b,
		color.a
		});
}

float Utils::lerp(const float a, const float b, const float t)
{
	return a + t * (b - a);
}

#pragma warning( push )
#pragma warning( disable : 4244)
SDL_Color Utils::colorLerp(const FColor a, const FColor b, float t)
{
	SDL_Color ret;
	t = clamp<float>(t, 0.f, 1.f);

	ret.a = lerp(a.a, b.a, t) * 255;
	ret.r = lerp(a.r, b.r, t) * 255;
	ret.g = lerp(a.g, b.g, t) * 255;
	ret.b = lerp(a.b, b.b, t) * 255;

	return ret;
}
#pragma warning( pop )

const std::string Utils::getDateTime()
{
	// Snippet from TrungTN: https://stackoverflow.com/a/10467633/7334657

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%d/%m/%Y - %X", &tstruct);

	return buf;
}

std::string Utils::strToUpper(const std::string str)
{
	std::string upper = str;
	std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
	return upper;
}

void Utils::openBrowserLink(const std::string link)
{
	ShellExecute(0, 0, LPCSTR(link.c_str()), 0, 0, SW_SHOW);
}

int Utils::randBetween(const int min, const int max)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	const std::uniform_int_distribution<int> dist(min, max);
	const int randomNumber = dist(engine);

	return randomNumber;
}
