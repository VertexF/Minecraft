#include "GeneralMaths.h"

namespace acid 
{
    float bilinearInterpolation(float bottonLeft, float topLeft, float bottonRight, float topRight,
        float xMin, float xMax,
        float zMin, float zMax,
        float xToCalc, float zToCalc) 
    {
        float width = xMax - xMin;
        float height = zMax - zMin;

        float xDistanceToMaxValue = xMax - xToCalc;
        float zDistanceToMaxValue = zMax - zToCalc;

        float xDistanceToMinValue = xToCalc - xMin;
        float zDistanceToMinValue = zToCalc - zMin;

        return 1.f / (width * height) * 
            (
                bottonLeft * xDistanceToMaxValue * zDistanceToMaxValue +
                bottonRight * xDistanceToMinValue * zDistanceToMaxValue +
                topLeft * xDistanceToMaxValue * zDistanceToMinValue +
                topRight * xDistanceToMinValue * zDistanceToMinValue
            );
    }
}