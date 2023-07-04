#include "framework.h"
#include "MathUtility.h"

int MathUtility::RandomInt(int min, int max)
{
    // 50 ~ 100

    return rand() % (max - min) + min;
}

float MathUtility::RandomFloat(float min, float max)
{
    // 5.0f ~ 6.0f;
    float temp = rand() / (float)RAND_MAX;

    return (max - min) * temp + min;
<<<<<<< HEAD
}
=======
}
>>>>>>> 5069b615e54763b25dd1f2f94990ab3fc9b6b805
