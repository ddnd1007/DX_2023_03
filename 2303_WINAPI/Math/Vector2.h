#pragma once
class Vector2
{
    
    public:
        Vector2()
            : x(0), y(0)
        {
        }

        Vector2(int x, int y)
            : x((float)x), y((float)y)
        {
            //  * this
            // this->x = x;
        }

        Vector2(float x, float y)
            : x(x), y(y)
        {

        }

         

        // 복사대입 생성자
        Vector2(const Vector2& other)
            : x(other.x), y(other.y)
        {
          
        }


        // 벡터의 덧셈 연산자 오버로딩
        Vector2 operator+(const Vector2& other)
        {
            Vector2 result;
            result.x = this->x + other.x;
            result.y = this->y + other.y;

            return result;
        }

       

        Vector2 operator-(const int& value)
        {
            Vector2 result;
            return result = Vector2(this->x * value, this->y * value);
        }

     
        Vector2& operator=(const Vector2& other)
        {
         
            x = other.x;
            y = other.y;  

            return *this;
        }

       
        float Length() const
        {
            float result = sqrtf(x * x + y * y);

            return result;
        }

        float Dot(const Vector2& other) const
        {
            float result = x * other.x + y * other.y;
            return result;
        }

        float Cross(const Vector2& other) const
        {
            float result = x * other.y - other.x * y;

            return result;
        }

        float Angle() const
        {
          

            float result = atan2f(y, x);
            return result;
        }

    public:
        float x = 0.0;
        float y = 0.0;
 
};

