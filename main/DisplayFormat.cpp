#include "DisplayFormat.hpp"

const string BandToString(Band v)
{
	switch (v)
	{
	case b160m:   return string("160");
	case b80m:   return string("80");
	case b60m: return string("60");
	case b40m: return string("40");
	case b30m: return string("30");
	case b20m: return string("20");
	case b17m: return string("17");
	case b15m: return string("15");
	case b12m: return string("12");
	case b10m: return string("10");
	case b6m: return string("6");
	default:      return string("??");
	}
}

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