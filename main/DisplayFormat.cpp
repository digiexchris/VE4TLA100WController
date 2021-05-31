#include "DisplayFormat.hpp"

string leftPadDoubleToStringWithPrecision(int width, double number,  int precision = 2)
{
	number = roundUp(number, precision);
	return rightAlignWidth(width, toStringWithPrecision(number, precision));
}

string toStringWithPrecision(double a_value, const int n)
{
	ostringstream out;
	out.precision(n);
	out << fixed << a_value;
	return out.str();
}

string rightAlignWidth(int width, string s) {
	/*if(s.length() > width) {
	    return s;
	}*/
	s.insert(s.begin(), width - s.length(), ' ');

	return s;
}

double roundUp(double value, int decimal_places) {
	const double multiplier = std::pow(10.0, decimal_places);
	return round(value * multiplier) / multiplier;
}