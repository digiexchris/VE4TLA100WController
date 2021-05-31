#pragma once

#include <string>
#include <cmath>
#include <sstream>

using namespace std;
string leftPadDoubleToStringWithPrecision(int width, double number,  int precision);
double roundUp(double value, int decimal_places);
string rightAlignWidth(int width, string s);
string toStringWithPrecision(double a_value, const int n = 2);