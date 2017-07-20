#include "Utils.h"
using namespace Utils;
//-------------Timer------------
Timer::Timer()
{
	reset();
	tick = 1000;	
}
Timer::Timer(int tick):tick(tick){	reset(); }
Timer::~Timer(){}		
void Timer::count_duration()
{
	current = CLOCK::now();
	millis_epleased = std::chrono::duration_cast<MILLIS>(current - start).count();
}
bool Timer::isTime(){		
	count_duration();
	if(millis_epleased > tick){
		reset();
		return true;
	}
	return false;
}
void Timer::reset()
{
	millis_epleased = 0;
	start = CLOCK::now();
}
void Timer::setTick(int tick){this->tick = tick;}

//-------------MathVector------------
MathVector::MathVector()
{
	x = 0;
	y = 0;
}
MathVector::MathVector(double x, double y):x(x),y(y){}
MathVector MathVector::operator*(double v2)
{
	MathVector v;
	v.x = x * v2;
	v.y = y * v2;
	return v;
};
MathVector MathVector::operator*(const MathVector &v2)
{
	MathVector v;
	v.x = x * v2.x;
	v.y = y * v2.y;
	return v;
}
MathVector MathVector::operator+(const MathVector &v2)
{
	MathVector v;
	v.x = x + v2.x;
	v.y = y + v2.y;
	return v;
}
MathVector MathVector::operator-(const MathVector &v2)
{
	MathVector v;
	v.x = x - v2.x;
	v.y = y - v2.y;
	return v;
}/*
MathVector MathVector::operator*=(double v2)
{
	v.x = x * v2;
	v.y = y * v2;
	return v;
}
MathVector MathVector::operator*=(const MathVector &v2)
{
	MathVector v;	
	v.x = x * v2.x;
	v.y = y * v2.y;
	return v;
}
MathVector MathVector::operator+=(const MathVector &v2)
{
	MathVector v;	
	v.x = x + v2.x;
	v.y = y + v2.y;
	return v;
}
MathVector MathVector::operator-=(const MathVector &v2)
{
	MathVector v;	
	v.x = x - v2.x;
	v.y = y - v2.y;
	return v;
}*/
void MathVector::normalize()
{
	len = sqrt(pow(x,2)+pow(y,2));
	x /= len;
	y /= len;
};

//-------------Keyboard------------
Keyboard::Keyboard()
{
	w = false;
	s = false;
	a = false;
	d = false;
}

//-------------Mouse------------
Mouse::Mouse()
{
	x = 0;
	y = 0;
	lmb = false;
	rmb = false;
}