#pragma once

#include "Typedefs.h"

namespace mapv
{
	class Colour
	{
		f32 r = 1.f;
		f32 g = 1.f;
		f32 b = 1.f;
		f32 a = 1.f;

	public:
		Colour() = default;
		Colour(f32 r, f32 g, f32 b, f32 a = 1.f) :
			r(r),
			g(g),
			b(b),
			a(a)
		{}

		static const Colour black()		{ return { 0, 0, 0 }; }
		static const Colour white()		{ return { 1, 1, 1 }; }
		static const Colour red()		{ return { 1, 0, 0 }; }
		static const Colour green()		{ return { 0, 1, 0 }; }
		static const Colour blue()		{ return { 0, 0, 1 }; }
		static const Colour orange()	{ return { 1, 1, 0 }; }
		static const Colour yellow()	{ return { 1, 1, 0 }; }
		static const Colour magenta()	{ return { 1, 0, 1 }; }
		static const Colour violet()	{ return { 0.5f, 0, 1 }; }
		static const Colour ocean()		{ return { 0, 0.5f, 1 }; }
		static const Colour cyan()		{ return { 0, 1, 1 }; }
		static const Colour turquiose() { return { 0, 1, 0.5f }; }
	};
}