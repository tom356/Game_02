#ifndef _GAME_UTILITIES_H
#define _GAME_UTILITIES_H

#include <cmath>
#include <chrono>
namespace Utils
{
	class Timer
	{
		private:
		
		typedef std::chrono::high_resolution_clock::time_point TIME_POINT;
		typedef std::chrono::high_resolution_clock CLOCK;
		typedef std::chrono::milliseconds MILLIS;
		
		TIME_POINT start;
		TIME_POINT current;
		int millis_epleased;
		int tick;
		
		void count_duration();
		
		public:
		
		Timer();
		Timer(int tick);
		~Timer();
		bool isTime();
		void reset();
		void setTick(int tick);
	};
	struct Keyboard
	{
		bool a,s,d,w;
		Keyboard();
	};
	struct Mouse
	{
		int x, y;
		bool lmb, rmb;
		Mouse();
	};
	struct MathVector
	{		
		double x,y,len;
		
		MathVector operator*(double v2);
		MathVector operator*(const MathVector &v2);
		MathVector operator+(const MathVector &v2);
		MathVector operator-(const MathVector &v2);/*
		MathVector operator*=(double v2);
		MathVector operator*=(const MathVector &v2);		
		MathVector operator+=(const MathVector &v2);		
		MathVector operator-=(const MathVector &v2);*/		
		MathVector();
		MathVector(double x, double y);
		void normalize();
	};
}
#endif