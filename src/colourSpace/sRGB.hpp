#pragma once

#include "ColorSpace.hpp"
#include <cmath>
#include <sstream>

class sRGB : public ColorSpace {
public:
  sRGB(const double r = 0, const double g = 0, const double b = 0) : ColorSpace(r, g, b) {};
  sRGB(const sRGB& other) : ColorSpace(other) {};

  double GetR() const { return m_a; };
  double GetG() const { return m_b; };
  double GetB() const { return m_c; };

  uint8_t GetRUInt() const;
  uint8_t GetGUInt() const;
  uint8_t GetBUInt() const;

  static double UInt8ToDouble(const uint8_t v) { return double(v) / 255.; };

  sRGB& operator/=(const sRGB& other);
  sRGB& operator*=(const sRGB& other);
  sRGB& operator+=(const sRGB& other);
  sRGB& operator-=(const sRGB& other);
  sRGB& operator*=(const double scalar);

  sRGB operator/(const sRGB& other) const { sRGB out(*this); out /= other; return out; };
  sRGB operator*(const sRGB& other) const { sRGB out(*this); out *= other; return out; };
  sRGB operator+(const sRGB& other) const { sRGB out(*this); out += other; return out; };
  sRGB operator-(const sRGB& other) const { sRGB out(*this); out -= other; return out; };
  sRGB operator*(const double scalar) const { sRGB out(*this); out *= scalar; return out; };

  void Clamp() {
    m_a = std::max(std::min(m_a, 1.), 0.);
    m_b = std::max(std::min(m_b, 1.), 0.);
    m_c = std::max(std::min(m_c, 1.), 0.);
  }

  bool IsInside() const;

  std::string Debug(const double maxValue = 1.) const;
  std::string UintDebug() const;

  static sRGB HexTosRGB(const std::string hex);
  std::string sRGBtoHex() const;
};


inline uint8_t sRGB::GetRUInt() const {
  int o = (int)std::round(m_a * 255.);
  o = o > 255 ? 255 : o;
  return uint8_t(o < 0 ? 0 : o);
}

inline uint8_t sRGB::GetGUInt() const {
  int o = (int)std::round(m_b * 255.);
  o = o > 255 ? 255 : o;
  return uint8_t(o < 0 ? 0 : o);
}

inline uint8_t sRGB::GetBUInt() const {
  int o = (int)std::round(m_c * 255.);
  o = o > 255 ? 255 : o;
  return uint8_t(o < 0 ? 0 : o);
}

inline sRGB& sRGB::operator/=(const sRGB& other) {
  ColorSpace lhs(other);
  ColorSpace::operator/=(lhs);
  return *this;
}

inline sRGB& sRGB::operator*=(const sRGB& other) {
  ColorSpace lhs(other);
  ColorSpace::operator*=(lhs);
  return *this;
}

inline sRGB& sRGB::operator+=(const sRGB& other) {
  ColorSpace lhs(other);
  ColorSpace::operator+=(lhs);
  return *this;
}

inline sRGB& sRGB::operator-=(const sRGB& other) {
  ColorSpace lhs(other);
  ColorSpace::operator-=(lhs);
  return *this;
}

inline sRGB& sRGB::operator*=(const double scalar) {
  ColorSpace::operator*=(scalar);
  return *this;
}

inline bool sRGB::IsInside() const {
  return m_a <= 1 && m_b <= 1 && m_c <= 1 && m_a >= 0 && m_b >= 0 && m_c >= 0;
}

inline std::string sRGB::Debug(const double maxValue) const {
  return std::to_string(m_a * maxValue) + ' ' + std::to_string(m_b * maxValue) + ' ' + std::to_string(m_c * maxValue);
}

inline std::string sRGB::UintDebug() const {
  return std::to_string((*this).GetRUInt()) + ' ' + std::to_string((*this).GetGUInt()) + ' ' + std::to_string((*this).GetBUInt());
}

inline sRGB sRGB::HexTosRGB(const std::string hex) {
  const unsigned int hexInt = std::stoi(hex, 0, 16);

  const unsigned int rMask = 0xFF0000;
  const unsigned int gMask = 0x00FF00;
  const unsigned int bMask = 0x0000FF;

  return sRGB(double((hexInt & rMask) >> 16) / 255., double((hexInt & gMask) >> 8) / 255., double(hexInt & bMask) / 255.);
}

inline std::string sRGB::sRGBtoHex() const {
  const unsigned int r = (unsigned int)(*this).GetRUInt();
  const unsigned int g = (unsigned int)(*this).GetGUInt();
  const unsigned int b = (unsigned int)(*this).GetBUInt();

  const unsigned int rgb = (r << 16) | (g << 8) | b;

  std::stringstream ss;
  ss << std::hex << std::uppercase << rgb;

  std::string out = ss.str();
  while (out.length() < 6) {
    out = "0" + out;
  }
  return out;
}
