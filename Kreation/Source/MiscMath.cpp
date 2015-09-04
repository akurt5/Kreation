#include "MiscMath.h"

float MiscMath::DegToRad(float _Angle)
{
	float Angle = _Angle * (180 / PI);
	return Angle; 
}

/*glm::vec2 MiscMath::PolToCartCoords(float _Angle, float _Radius)
{
	glm::vec2 Pos;
	Pos.x = _Radius * cos(_Angle);//Degrees or Radians??????????????????????????
	Pos.y = _Radius * sin(_Angle);
	return Pos;
}*/
double MiscMath::Ninety(float _Angle)//func is to help with the lerp in the calc points func
{
	double Angle = _Angle;
	if(Angle > 90.0f)//we want to have the angle less than 90
	{
		Angle -= 90.0f;
	}
	else
	{
		return Angle;
	}
	return Ninety((float)Angle);//this should repeat the func until angle is less than 90
}
/*float MiscMath::Trigonometry(float _Opposite, float _Adjacent, float _Hypotenuse, float _Angle)
{
	float Opposite = _Opposite, Adjacent = _Adjacent, Hypotenuse = _Hypotenuse, Angle = _Angle;
	if(_Opposite == NULL)//CAH
	{
		if(_Angle == NULL)//iCAH?
		{

		}
		//We must know angle if we get here so we're solving for either adjacent or hypotenuse
	}
	if(_Adjacent == NULL)//SOH
	{
		if(_Angle == NULL)//iSOH?
		{

		}
	}
	if(_Hypotenuse == NULL)//TOA
	{
		if(_Angle == NULL)//iTOA?
		{

		}
		
	}
}*/
float MiscMath::Pythagorus(float _A, float _B, float _C)
{
	if(_A == NULL)
	{
		return CalcB(_B, _C);
	}
	else if(_B == NULL)
	{
		return CalcB(_A, _C);
	}
	else if(_C == NULL)
	{
		float A = _A, B = _B;
		return (float)sqrt(((A*A) + (B*B)));
	}
	return 0.0f;
}
float MiscMath::CalcB(float _A, float _C)
{
	float A = _A, C = _C;
	A *= A;C *= C;
	C -= A;
	if(C < 0){C *= -1.0f;}
	return (float)sqrt(C);

}