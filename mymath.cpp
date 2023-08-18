#include "mymath.h"

float vall = 180.0 / PI;
float decc = PI / 180;

/**
* theta: degree
*
* return: [-1, 1]
*/
float cos_deg(float theta)
{
	return cos(theta * decc);
}

/**
* theta: degree
*
* return: [-1, 1]
*/
float sin_deg(float theta)
{
	return sin(theta * decc);
}

/**
* theta: degree
*
* return: [-1, 1]
*/
float tan_deg(float theta)
{
	return tan(theta * decc);
}




/**
* num: [-1, 1]
* 
* return: degree
*/
float acos_deg(float num)  
{
	return acos(num) * vall;
}

/**
* num: [-1, 1]
*
* return: degree
*/
float asin_deg(float num)
{
	return asin(num) * vall;
}

/**
* num: [-1, 1]
*
* return: degree
*/
float atan_deg(float num)
{
	return atan(num) * vall;
}