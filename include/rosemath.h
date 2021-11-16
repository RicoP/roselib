#pragma once

#define MATHC_USE_UNIONS
#include <mathc/mathc.h>
#include <cassert>
#include <cmath>

namespace math {
template <class T>
T sign(T val) {
  return val < 0 ? -1 : 1;
}

template <class T>
T abs(T val) {
  return val < 0 ? -val : val;
}

template <class T>
T min(T a, T b) {
  return a < b ? a : b;
}

template <class T>
T max(T a, T b) {
  return a > b ? a : b;
}

}  // namespace math
typedef struct vec2 vector2;
typedef struct vec3 vector3;
typedef struct vec4 vector4;
typedef struct mat3 matrix3;
typedef struct mat4 matrix4;
typedef struct quat quaternion;
typedef struct vec4 color4f;
typedef struct vec4 hsv4f;

// const cast is ok, because V is not mutated
#define UCONST(V) const_cast<float*>(V.v)

struct cube {
  vector3 pivot;
  vector3 size;
};

inline vector2 vector(float x, float y) {
  vector2 v;
  v.x = x;
  v.y = y;
  return v;
}

inline vector3 vector(float x, float y, float z) {
  vector3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

inline vector4 vector(float x, float y, float z, float w) {
  vector4 v;
  v.x = x;
  v.y = y;
  v.z = z;
  v.w = w;
  return v;
}

inline vector4 vector(const vector3& v3, float w) {
  vector4 v;
  v.x = v3.x;
  v.y = v3.y;
  v.z = v3.z;
  v.w = w;
  return v;
}

inline vector4 vector(const vector2& v2, float z, float w) {
  vector4 v;
  v.x = v2.x;
  v.y = v2.y;
  v.z = z;
  v.w = w;
  return v;
}

inline matrix4 inverse(const matrix4& mat) { return smat4_inverse(mat); }

inline quaternion qidentity() { return squat_null(); }

inline matrix4 identity4() { return smat4_identity(); }

// clang-format off

inline matrix4    matrix4_from_quaternion(const quaternion& q)              { return smat4_rotation_quat(q); }
inline quaternion quaternion_from_axis(const vector3& axis, float rad)      { return squat_from_axis_angle(axis, rad); }

inline float     dot       (const vector2& a, const vector2& b)    {                                     return                        svec2_dot(a, b); }
inline float     dot       (const vector3& a, const vector3& b)    {                                     return                        svec3_dot(a, b); }
inline float     length    (const vector2& v)                      {                                     return                        svec2_length(v); }
inline float     length    (const vector3& v)                      {                                     return                        svec3_length(v); }
inline float     length_sqr(const vector2& v)                      {                                     return                svec2_length_squared(v); }
inline float     length_sqr(const vector3& v)                      {                                     return                svec3_length_squared(v); }

inline bool      operator== (const vector2 & a, const vector2 & b) {                                     return                   svec2_is_equal(a,b); }
inline bool      operator!= (const vector2 & a, const vector2 & b) {                                     return                             !(a == b); }
inline vector2 & operator+= (      vector2 & a, const vector2 & b) { vec2_add     (a.v, a.v, UCONST(b)); return                                    a;  }
inline vector2   operator+  (const vector2 & a, const vector2 & b) { vector2 r = a;                      return                               r += b;  }
inline vector2 & operator-= (      vector2 & a, const vector2 & b) { vec2_subtract(a.v, a.v, UCONST(b)); return                                    a;  }
inline vector2   operator-  (const vector2 & a, const vector2 & b) { vector2 r = a;                      return                               r -= b;  }
inline vector2 & operator*= (      vector2 & a, const vector2 & b) { vec2_multiply(a.v, a.v, UCONST(b)); return                                    a;  }
inline vector2   operator*  (const vector2 & a, const vector2 & b) { vector2 r = a;                      return                               r *= b;  }
inline vector2 & operator*= (      vector2 & a, float f)           { vec2_multiply_f(a.v, a.v, f);       return                                    a;  }
inline vector2   operator*  (const vector2 & a, float f)           { vector2 r = a;                      return                               r *= f;  }
inline vector2   operator-  (const vector2 & a)                    { vector2 r = a;                      return                              r *= -1;  }
inline vector2   operator*  (float f,           const vector2 & a) {                                     return                                a * f;  }
inline vector2   operator+  (const vector2 & a, float f)           { vector2 r = a;                      return                     r += vector(f,f);  }
inline vector2   operator-  (const vector2 & a, float f)           { vector2 r = a;                      return                     r -= vector(f,f);  }

inline bool      operator== (const vector3 & a, const vector3 & b) {                                     return                   svec3_is_equal(a,b); }
inline bool      operator!= (const vector3 & a, const vector3 & b) {                                     return                             !(a == b); }
inline vector3 & operator+= (      vector3 & a, const vector3 & b) { vec3_add     (a.v, a.v, UCONST(b)); return                                    a;  }
inline vector3   operator+  (const vector3 & a, const vector3 & b) { vector3 r = a;                      return                               r += b;  }
inline vector3 & operator-= (      vector3 & a, const vector3 & b) { vec3_subtract(a.v, a.v, UCONST(b)); return                                    a;  }
inline vector3   operator-  (const vector3 & a, const vector3 & b) { vector3 r = a;                      return                               r -= b;  }
inline vector3 & operator*= (      vector3 & a, const vector3 & b) { vec3_multiply(a.v, a.v, UCONST(b)); return                                    a;  }
inline vector3   operator*  (const vector3 & a, const vector3 & b) { vector3 r = a;                      return                               r *= b;  }
inline vector3 & operator*= (      vector3 & a, float f)           { vec3_multiply_f(a.v, a.v, f);       return                                    a;  }
inline vector3   operator*  (const vector3 & a, float f)           { vector3 r = a;                      return                               r *= f;  }
inline vector3   operator-  (const vector3 & a)                    { vector3 r = a;                      return                              r *= -1;  }
inline vector3   operator*  (float f,           const vector3 & a) {                                     return                                a * f;  }
inline vector3   operator+  (const vector3 & a, float f)           { vector3 r = a;                      return                   r += vector(f,f,f);  }
inline vector3   operator-  (const vector3 & a, float f)           { vector3 r = a;                      return                   r -= vector(f,f,f);  }

inline bool      operator== (const vector4 & a, const vector4 & b) {                                     return                   svec4_is_equal(a,b); }
inline bool      operator!= (const vector4 & a, const vector4 & b) {                                     return                             !(a == b); }
inline vector4 & operator+= (      vector4 & a, const vector4 & b) { vec4_add     (a.v, a.v, UCONST(b)); return                                    a;  }
inline vector4   operator+  (const vector4 & a, const vector4 & b) { vector4 r = a;                      return                               r += b;  }
inline vector4 & operator-= (      vector4 & a, const vector4 & b) { vec4_subtract(a.v, a.v, UCONST(b)); return                                    a;  }
inline vector4   operator-  (const vector4 & a, const vector4 & b) { vector4 r = a;                      return                               r -= b;  }
inline vector4 & operator*= (      vector4 & a, const vector4 & b) { vec4_multiply(a.v, a.v, UCONST(b)); return                                    a;  }
inline vector4   operator*  (const vector4 & a, const vector4 & b) { vector4 r = a;                      return                               r *= b;  }
inline vector4 & operator*= (      vector4 & a, float f)           { vec4_multiply_f(a.v, a.v, f);       return                                    a;  }
inline vector4   operator*  (const vector4 & a, float f)           { vector4 r = a;                      return                               r *= f;  }
inline vector4   operator-  (const vector4 & a)                    { vector4 r = a;                      return                              r *= -1;  }
inline vector4   operator*  (float f,           const vector4 & a) {                                     return                                a * f;  }
inline vector4   operator+  (const vector4 & a, float f)           { vector4 r = a;                      return                 r += vector(f,f,f,f);  }
inline vector4   operator-  (const vector4 & a, float f)           { vector4 r = a;                      return                 r -= vector(f,f,f,f);  }

inline vector3   cross      (const vector3& a, const vector3& b)   {                                     return                      svec3_cross(a, b); }
inline vector2   normalized (const vector2& v)                     { assert(v != vector(0,0));           return                     svec2_normalize(v); }
inline vector3   normalized (const vector3& v)                     { assert(v != vector(0,0,0));         return                     svec3_normalize(v); }
inline vector4   normalized (const vector4& v)                     { assert(v != vector(0,0,0,0));       return                     svec4_normalize(v); }

inline bool      operator== (const quaternion & a, const quaternion & b) {                               return                   squat_is_equal(a,b); }
// clang-format on

inline vector3 operator*(const vector4& v, const matrix4& mat) {
  vector4 r4 = svec4_multiply_mat4(v, mat);
  vector3 r;
  r.x = r4.x;
  r.y = r4.y;
  r.z = r4.z;
  return r;
}

inline vector3 operator*(const vector3& v, const matrix3& mat) {
  return svec3_multiply_mat3(v, mat);
}

inline vector3& operator*=(vector3& v, const quaternion& q) {
  matrix4 mat = matrix4_from_quaternion(q);
  vector4 v4 = vector(v, 0);
  return v = v4 * mat;
}

inline vector3 operator*(const vector3& v, const quaternion& q) {
  vector3 r = v;
  return r *= q;
}

inline quaternion operator*(const quaternion& q1, const quaternion& q2) {
  quaternion r;
  quat_multiply(r.v, UCONST(q1), UCONST(q2));
  return r;
}

inline vector3 operator/(const vector4& v, const matrix4& mat) { return v * inverse(mat); }

inline matrix4 operator*=(matrix4& dest, const matrix4& m) {
  mat4_multiply(dest.v, dest.v, UCONST(m));
  return dest;
}

inline matrix4 operator*(const matrix4& lhs, const matrix4& rhs) {
  matrix4 r = lhs;
  return r *= rhs;
}

inline bool operator==(const matrix4& lhs, const matrix4& rhs) {
  for(int i = 0; i != 16; ++i)
    if (lhs.v[i] != rhs.v[i])
      return false;
  return true;
}

inline void construct_defaults(vector2& v) { v = vector(0, 0); }
inline void construct_defaults(vector3& v) { v = vector(0, 0, 0); }
inline void construct_defaults(vector4& v) { v = vector(0, 0, 0, 0); }
inline void construct_defaults(matrix4& m) { m = identity4(); }
inline void construct_defaults(quaternion& q) { q = qidentity(); }

inline matrix4 smat4_mvt(vector3 position, quaternion rotation, vector3 scale) {
  matrix4 mtrans = identity4();
  mtrans = smat4_translation(mtrans, position);

  matrix4 mrotat = smat4_rotation_quat(rotation);

  matrix4 mscale = identity4();
  mscale = smat4_scale(mscale, scale);

  matrix4 mat = identity4();
  mat *= mtrans;
  mat *= mrotat;
  mat *= mscale;

  return mat;
}

// https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
inline vector3 QuaternionToEulerAngles(const quaternion& q1) {
  float heading, attitude, bank;
  float test = q1.x * q1.y + q1.z * q1.w;
  if (test > 0.499) {  // singularity at north pole
    heading = 2 * atan2(q1.x, q1.w);
    attitude = MPI / 2;
    bank = 0;
    return vector(attitude, heading, bank);
  }
  if (test < -0.499) {  // singularity at south pole
    heading = -2 * atan2(q1.x, q1.w);
    attitude = -MPI / 2;
    bank = 0;
    return vector(attitude, heading, bank);
  }
  float sqx = q1.x * q1.x;
  float sqy = q1.y * q1.y;
  float sqz = q1.z * q1.z;
  heading = atan2(2 * q1.y * q1.w - 2 * q1.x * q1.z, 1 - 2 * sqy - 2 * sqz);
  attitude = asin(2 * test);
  bank = atan2(2 * q1.x * q1.w - 2 * q1.y * q1.z, 1 - 2 * sqx - 2 * sqz);

  return vector(attitude, heading, bank);
}

inline quaternion EulerAnglesToQuaternion(vector3 axis)  // yaw (Z), pitch (Y), roll (X)
{
  float yaw = axis.z;
  float pitch = axis.y;
  float roll = axis.x;
  // Abbreviations for the autoious angular functions
  float cy = cos(yaw * 0.5f);
  float sy = sin(yaw * 0.5f);
  float cp = cos(pitch * 0.5f);
  float sp = sin(pitch * 0.5f);
  float cr = cos(roll * 0.5f);
  float sr = sin(roll * 0.5f);

  quaternion q;
  q.w = cr * cp * cy + sr * sp * sy;
  q.x = sr * cp * cy - cr * sp * sy;
  q.y = cr * sp * cy + sr * cp * sy;
  q.z = cr * cp * sy - sr * sp * cy;

  return q;
}

struct vertex {
  vector3 position;
  vector3 normal;  // TODO: unused for now
  vector3 color;
  vector2 uv;

  vertex() : position(vector(0, 0, 0)), normal(vector(0, 0, 0)), color(vector(0, 0, 0)), uv(vector(0, 0)) {}
};

struct Triangle {
  vertex vertice[3];
};

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
inline quaternion RotationBetweenVectors(vector3 start, vector3 dest) {
  start = normalized(start);
  dest = normalized(dest);

  float cosTheta = dot(start, dest);
  vector3 rotationAxis;

  if (cosTheta < -1 + 0.001f) {
    // special case when vectors in opposite directions:
    // there is no "ideal" rotation axis
    // So guess one; any will do as long as it's perpendicular to start
    rotationAxis = cross(vector(0.0f, 0.0f, 1.0f), start);
    if (length_sqr(rotationAxis) < 0.01f)  // bad luck, they were parallel, try again!
      rotationAxis = cross(vector(1.0f, 0.0f, 0.0f), start);

    rotationAxis = normalized(rotationAxis);
    return EulerAnglesToQuaternion(rotationAxis);
  }

  rotationAxis = cross(start, dest);

  float s = sqrt((1.0f + cosTheta) * 2.0f);
  float invs = 1 / s;

  return quaternion{rotationAxis.x * invs, rotationAxis.y * invs, rotationAxis.z * invs, s * 0.5f};
}

// color stuff
inline unsigned int colorToInt(color4f c) {
  unsigned int r = (unsigned int)(255 * c.x);
  unsigned int g = (unsigned int)(255 * c.y);
  unsigned int b = (unsigned int)(255 * c.z);
  unsigned int a = (unsigned int)(255 * c.w);

  a <<= 24;
  b <<= 16;
  g <<= 8;
  r <<= 0;
  return r | g | b | a;
}

#undef UCONST

//COLORS
namespace colors {
// clang-format off
const vector3 AliceBlue         = {0.941176f, 0.972549f, 1.000000f};
const vector3 AntiqueWhite      = {0.980392f, 0.921569f, 0.843137f};
const vector3 Aquamarine        = {0.498039f, 1.000000f, 0.831373f};
const vector3 Azure             = {0.941176f, 1.000000f, 1.000000f};
const vector3 Beige             = {0.960784f, 0.960784f, 0.862745f};
const vector3 Bisque            = {1.000000f, 0.894118f, 0.768627f};
const vector3 Black             = {0.000000f, 0.000000f, 0.000000f};
const vector3 BlanchedAlmond    = {1.000000f, 0.921569f, 0.803922f};
const vector3 Blue              = {0.000000f, 0.000000f, 1.000000f};
const vector3 BlueViolet        = {0.541176f, 0.168627f, 0.886275f};
const vector3 Brown             = {0.647059f, 0.164706f, 0.164706f};
const vector3 BurlyWood         = {0.870588f, 0.721569f, 0.529412f};
const vector3 CadetBlue         = {0.372549f, 0.619608f, 0.627451f};
const vector3 Chartreuse        = {0.498039f, 1.000000f, 0.000000f};
const vector3 Chocolate         = {0.823529f, 0.411765f, 0.117647f};
const vector3 Coral             = {1.000000f, 0.498039f, 0.313726f};
const vector3 CornflowerBlue    = {0.392157f, 0.584314f, 0.929412f};
const vector3 Cornsilk          = {1.000000f, 0.972549f, 0.862745f};
const vector3 Crimson           = {0.862745f, 0.078431f, 0.235294f};
const vector3 Cyan              = {0.000000f, 1.000000f, 1.000000f};
const vector3 DarkBlue          = {0.000000f, 0.000000f, 0.545098f};
const vector3 DarkCyan          = {0.000000f, 0.545098f, 0.545098f};
const vector3 DarkGoldenRod     = {0.721569f, 0.525490f, 0.043137f};
const vector3 DarkGray          = {0.662745f, 0.662745f, 0.662745f};
const vector3 DarkGreen         = {0.000000f, 0.392157f, 0.000000f};
const vector3 DarkKhaki         = {0.741176f, 0.717647f, 0.419608f};
const vector3 DarkMagenta       = {0.545098f, 0.000000f, 0.545098f};
const vector3 DarkOliveGreen    = {0.333333f, 0.419608f, 0.184314f};
const vector3 DarkOrange        = {1.000000f, 0.549020f, 0.000000f};
const vector3 DarkOrchid        = {0.600000f, 0.196078f, 0.800000f};
const vector3 DarkRed           = {0.545098f, 0.000000f, 0.000000f};
const vector3 DarkSalmon        = {0.913725f, 0.588235f, 0.478431f};
const vector3 DarkSeaGreen      = {0.560784f, 0.737255f, 0.560784f};
const vector3 DarkSlateBlue     = {0.282353f, 0.239216f, 0.545098f};
const vector3 DarkSlateGray     = {0.184314f, 0.309804f, 0.309804f};
const vector3 DarkTurquoise     = {0.000000f, 0.807843f, 0.819608f};
const vector3 DarkViolet        = {0.580392f, 0.000000f, 0.827451f};
const vector3 DeepPink          = {1.000000f, 0.078431f, 0.576471f};
const vector3 DeepSkyBlue       = {0.000000f, 0.749020f, 1.000000f};
const vector3 DimGray           = {0.411765f, 0.411765f, 0.411765f};
const vector3 DodgerBlue        = {0.117647f, 0.564706f, 1.000000f};
const vector3 FireBrick         = {0.698039f, 0.133333f, 0.133333f};
const vector3 FloralWhite       = {1.000000f, 0.980392f, 0.941176f};
const vector3 ForestGreen       = {0.133333f, 0.545098f, 0.133333f};
const vector3 Gainsboro         = {0.862745f, 0.862745f, 0.862745f};
const vector3 GhostWhite        = {0.972549f, 0.972549f, 1.000000f};
const vector3 Gold              = {1.000000f, 0.843137f, 0.000000f};
const vector3 GoldenRod         = {0.854902f, 0.647059f, 0.125490f};
const vector3 Gray              = {0.501961f, 0.501961f, 0.501961f};
const vector3 Green             = {0.000000f, 0.501961f, 0.000000f};
const vector3 GreenYellow       = {0.678431f, 1.000000f, 0.184314f};
const vector3 HoneyDew          = {0.941176f, 1.000000f, 0.941176f};
const vector3 HotPink           = {1.000000f, 0.411765f, 0.705882f};
const vector3 IndianRed         = {0.803922f, 0.360784f, 0.360784f};
const vector3 Indigo            = {0.294118f, 0.000000f, 0.509804f};
const vector3 Ivory             = {1.000000f, 1.000000f, 0.941176f};
const vector3 Khaki             = {0.941176f, 0.901961f, 0.549020f};
const vector3 Lavender          = {0.901961f, 0.901961f, 0.980392f};
const vector3 LavenderBlush     = {1.000000f, 0.941176f, 0.960784f};
const vector3 LawnGreen         = {0.486275f, 0.988235f, 0.000000f};
const vector3 LemonChiffon      = {1.000000f, 0.980392f, 0.803922f};
const vector3 LightBlue         = {0.678431f, 0.847059f, 0.901961f};
const vector3 LightCoral        = {0.941176f, 0.501961f, 0.501961f};
const vector3 LightCyan         = {0.878431f, 1.000000f, 1.000000f};
const vector3 LightGoldenYellow = {0.980392f, 0.980392f, 0.823529f};
const vector3 LightGray         = {0.827451f, 0.827451f, 0.827451f};
const vector3 LightGreen        = {0.564706f, 0.933333f, 0.564706f};
const vector3 LightPink         = {1.000000f, 0.713726f, 0.756863f};
const vector3 LightSalmon       = {1.000000f, 0.627451f, 0.478431f};
const vector3 LightSeaGreen     = {0.125490f, 0.698039f, 0.666667f};
const vector3 LightSkyBlue      = {0.529412f, 0.807843f, 0.980392f};
const vector3 LightSlateGray    = {0.466667f, 0.533333f, 0.600000f};
const vector3 LightSteelBlue    = {0.690196f, 0.768627f, 0.870588f};
const vector3 LightYellow       = {1.000000f, 1.000000f, 0.878431f};
const vector3 Lime              = {0.000000f, 1.000000f, 0.000000f};
const vector3 LimeGreen         = {0.196078f, 0.803922f, 0.196078f};
const vector3 Linen             = {0.980392f, 0.941176f, 0.901961f};
const vector3 Magenta           = {1.000000f, 0.000000f, 1.000000f};
const vector3 Maroon            = {0.501961f, 0.000000f, 0.000000f};
const vector3 MediumAquaMarine  = {0.400000f, 0.803922f, 0.666667f};
const vector3 MediumBlue        = {0.000000f, 0.000000f, 0.803922f};
const vector3 MediumOrchid      = {0.729412f, 0.333333f, 0.827451f};
const vector3 MediumPurple      = {0.576471f, 0.439216f, 0.858824f};
const vector3 MediumSeaGreen    = {0.235294f, 0.701961f, 0.443137f};
const vector3 MediumSlateBlue   = {0.482353f, 0.407843f, 0.933333f};
const vector3 MediumSpringGreen = {0.000000f, 0.980392f, 0.603922f};
const vector3 MediumTurquoise   = {0.282353f, 0.819608f, 0.800000f};
const vector3 MediumVioletRed   = {0.780392f, 0.082353f, 0.521569f};
const vector3 MidnightBlue      = {0.098039f, 0.098039f, 0.439216f};
const vector3 MintCream         = {0.960784f, 1.000000f, 0.980392f};
const vector3 MistyRose         = {1.000000f, 0.894118f, 0.882353f};
const vector3 Moccasin          = {1.000000f, 0.894118f, 0.709804f};
const vector3 NavajoWhite       = {1.000000f, 0.870588f, 0.678431f};
const vector3 Navy              = {0.000000f, 0.000000f, 0.501961f};
const vector3 OldLace           = {0.992157f, 0.960784f, 0.901961f};
const vector3 Olive             = {0.501961f, 0.501961f, 0.000000f};
const vector3 OliveDrab         = {0.419608f, 0.556863f, 0.137255f};
const vector3 Orange            = {1.000000f, 0.647059f, 0.000000f};
const vector3 OrangeRed         = {1.000000f, 0.270588f, 0.000000f};
const vector3 Orchid            = {0.854902f, 0.439216f, 0.839216f};
const vector3 PaleGoldenRod     = {0.933333f, 0.909804f, 0.666667f};
const vector3 PaleGreen         = {0.596078f, 0.984314f, 0.596078f};
const vector3 PaleTurquoise     = {0.686275f, 0.933333f, 0.933333f};
const vector3 PaleVioletRed     = {0.858824f, 0.439216f, 0.576471f};
const vector3 PapayaWhip        = {1.000000f, 0.937255f, 0.835294f};
const vector3 PeachPuff         = {1.000000f, 0.854902f, 0.725490f};
const vector3 Peru              = {0.803922f, 0.521569f, 0.247059f};
const vector3 Pink              = {1.000000f, 0.752941f, 0.796078f};
const vector3 Plum              = {0.866667f, 0.627451f, 0.866667f};
const vector3 PowderBlue        = {0.690196f, 0.878431f, 0.901961f};
const vector3 Purple            = {0.501961f, 0.000000f, 0.501961f};
const vector3 RebeccaPurple     = {0.400000f, 0.200000f, 0.600000f};
const vector3 Red               = {1.000000f, 0.000000f, 0.000000f};
const vector3 RosyBrown         = {0.737255f, 0.560784f, 0.560784f};
const vector3 RoyalBlue         = {0.254902f, 0.411765f, 0.882353f};
const vector3 SaddleBrown       = {0.545098f, 0.270588f, 0.074510f};
const vector3 Salmon            = {0.980392f, 0.501961f, 0.447059f};
const vector3 SandyBrown        = {0.956863f, 0.643137f, 0.376471f};
const vector3 SeaGreen          = {0.180392f, 0.545098f, 0.341176f};
const vector3 SeaShell          = {1.000000f, 0.960784f, 0.933333f};
const vector3 Sienna            = {0.627451f, 0.321569f, 0.176471f};
const vector3 Silver            = {0.752941f, 0.752941f, 0.752941f};
const vector3 SkyBlue           = {0.529412f, 0.807843f, 0.921569f};
const vector3 SlateBlue         = {0.415686f, 0.352941f, 0.803922f};
const vector3 SlateGray         = {0.439216f, 0.501961f, 0.564706f};
const vector3 Snow              = {1.000000f, 0.980392f, 0.980392f};
const vector3 SpringGreen       = {0.000000f, 1.000000f, 0.498039f};
const vector3 SteelBlue         = {0.274510f, 0.509804f, 0.705882f};
const vector3 Tan               = {0.823529f, 0.705882f, 0.549020f};
const vector3 Teal              = {0.000000f, 0.501961f, 0.501961f};
const vector3 Thistle           = {0.847059f, 0.749020f, 0.847059f};
const vector3 Tomato            = {1.000000f, 0.388235f, 0.278431f};
const vector3 Turquoise         = {0.250980f, 0.878431f, 0.815686f};
const vector3 Violet            = {0.933333f, 0.509804f, 0.933333f};
const vector3 Wheat             = {0.960784f, 0.870588f, 0.701961f};
const vector3 White             = {1.000000f, 1.000000f, 1.000000f};
const vector3 WhiteSmoke        = {0.960784f, 0.960784f, 0.960784f};
const vector3 Yellow            = {1.000000f, 1.000000f, 0.000000f};
const vector3 YellowGreen       = {0.603922f, 0.803922f, 0.196078f};
// clang-format on
}  // namespace colors
