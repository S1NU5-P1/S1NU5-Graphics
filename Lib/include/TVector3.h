#pragma once

#include <cmath>
#include <exception>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace SG
{

    class DivisionByZeroException : std::exception
    {
    public:
    private:
        [[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };

    template<typename T>
    class TVector3
    {
    public:
        T x;
        T y;
        T z;

        TVector3() : x(0), y(0), z(0) {}

        TVector3(T x) : x(x), y(x), z(x) {}

        TVector3(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

        double Length() const
        { return std::sqrt(x * x + y * y + z * z); }

        double SquaredLength()
        { return x * x + y * y + z * z; }

        TVector3 Normal()
        {
            double length = this->Length();
            if (length == 0)
                return TVector3<T>(0.);

            return *this / length;
        }

        bool IsNear(TVector3 vector3, double error) {
            return std::abs(this->Length() - vector3.Length()) < error;
        }

        double Dot(TVector3 rhs)
        { return x * rhs.x + y * rhs.y + z * rhs.z; }

        double Angle(TVector3 rhs)
        {
            return acos(this->Dot(rhs) / (this->Length() * rhs.Length()));
        }

        TVector3 Cross(TVector3 rhs)
        {
            return TVector3<T>(this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z,
                               this->x * rhs.y - this->y * rhs.x);
        }

        TVector3& operator=(TVector3 const& another)
        {
            if (this == &another)
            {
                return *this;
            }

            this->x = another.x;
            this->y = another.y;
            this->z = another.z;
            return *this;
        }

        TVector3 operator-()
        {
            TVector3<T> result;
            result.x = -this->x;
            result.y = -this->y;
            result.z = -this->z;
            return result;
        }

        TVector3 operator+(TVector3 const& another)
        {
            TVector3 result;
            result.x = this->x + another.x;
            result.y = this->y + another.y;
            result.z = this->z + another.z;
            return result;
        }

        TVector3 operator-(TVector3 const& another)
        {
            TVector3 result;
            result.x = this->x - another.x;
            result.y = this->y - another.y;
            result.z = this->z - another.z;
            return result;
        }

        void operator+=(TVector3 const& another)
        { this = this + another; }

        void operator-=(TVector3 const& another)
        { this = this - another; }

        TVector3 operator*(T const& scalar)
        {
            TVector3 result;
            result.x = this->x * scalar;
            result.y = this->y * scalar;
            result.z = this->z * scalar;
            return result;
        }
        
        friend TVector3 operator*(T scalar, TVector3<T> vector)
        {
            return vector * scalar;
        }

        TVector3 operator/(T const& scalar)
        {
            if (scalar == 0)
                throw DivisionByZeroException();

            TVector3 result;
            result.x = this->x / scalar;
            result.y = this->y / scalar;
            result.z = this->z / scalar;
            return result;
        }

        TVector3 operator/(TVector3<T> const& vector3)
        {
            TVector3<T> newVector = vector3;
            if (newVector.x == 0)
                newVector.x == 1;
            if (newVector.y == 0)
                newVector.y == 1;
            if (newVector.z == 0)
                newVector.z == 1;

            TVector3 result;
            result.x = this->x / newVector.x;
            result.y = this->y / newVector.y;
            result.z = this->z / newVector.z;
            return result;
        }

        void operator*=(T const& scalar)
        { *this = *this * scalar; }

        void operator/=(T const& scalar)
        { *this = *this / scalar; }

        bool operator==(const TVector3& rhs) const
        {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        bool operator!=(const TVector3& rhs) const
        { return !(rhs == *this); }

        bool operator<(const TVector3& rhs) const
        {
            return this->Length() < rhs.Length();
        }

        bool operator>(const TVector3& rhs) const
        { return rhs < *this; }

        bool operator<=(const TVector3& rhs) const
        { return !(rhs < *this); }

        bool operator>=(const TVector3& rhs) const
        { return !(*this < rhs); }

        friend std::ostream& operator<<(std::ostream& Os, const TVector3& vector3)
        {
            Os << "[" << vector3.x << "," << vector3.y << "," << vector3.z << "]";
            return Os;
        }

        std::string str()
        {
            std::ostringstream result;
            result << *this;
            return result.str();
        }

        static TVector3<T> min(TVector3<T> a, TVector3<T> b) {
            TVector3<T> result;
            result.x = std::min(a.x, b.x);
            result.y = std::min(a.y, b.y);
            result.z = std::min(a.z, b.z);
            return result;
        }

        static TVector3<T> max(TVector3<T> a, TVector3<T> b) {
            TVector3<T> result;
            result.x = std::max(a.x, b.x);
            result.y = std::max(a.y, b.y);
            result.z = std::max(a.z, b.z);
            return result;
        }
    };

} // namespace SG
