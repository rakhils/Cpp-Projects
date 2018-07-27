#pragma once
#include <string>
class Rgba
{
public:

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Rgba::Rgba(); // Default-constructs to opaque white (255,255,255,255)

	explicit Rgba::Rgba( unsigned char redByte, unsigned char greenByte,unsigned char blueByte, unsigned char alphaByte=255 );

	void Rgba::SetAsBytes( unsigned char redByte, unsigned char greenByte, unsigned char blueByte, unsigned char alphaByte=255 );

	void Rgba::SetAsFloats( float normalizedRed, float normalizedgreen,float normalizedblue, float normalizedAlpha=1.0f );

	void Rgba::GetAsFloats( float& out_normalizedRed,float& out_normalizedGreen,float& out_normalizedBlue,float& out_normalizedAlpha ) const;

	void Rgba::ScaleRGB( float rgbScale ); // Scales (and clamps) RGB components, but not A

	void Rgba::ScaleAlpha( float alphaScale ); // Scales (and clamps) Alpha, RGB is untouched

	void Rgba::SetFromText(const char* text);

	std::string Rgba::getAsString();

	static Rgba WHITE;
	static Rgba RED;
	static Rgba GREEN;
	static Rgba BLUE;
	static Rgba BLACK;
	static Rgba FADED_BLACK;

};