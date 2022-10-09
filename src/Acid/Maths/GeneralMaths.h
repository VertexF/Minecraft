#ifndef GENERAL_MATHS_HDR
#define GENERAL_MATHS_HDR

namespace acid 
{
    float bilinearInterpolation(float bottonLeft, float topLeft, float bottonRight, float topRight,
                                float xMin, float xMax,
                                float zMin, float zMax,
                                float xToCalc, float zToCalc);
}

#endif // !GENERAL_MATHS_HDR
