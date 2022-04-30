#pragma once

namespace OhEngine {

class Vertex {
private:
  float m_arCoord[4]; // x, y, z, w

public:
  Vertex() : m_arCoord({0, 0, 0, 0}) {}
  Vertex(float fX, float fY, float fZ) : m_arCoord({fX, fY, fZ, 0}) {}
  ~Vertex();

  inline float x() const { return m_arCoord[0]; }
  inline float y() const { return m_arCoord[1]; }
  inline float z() const { return m_arCoord[2]; }
  inline float w() const { return m_arCoord[3]; }
};

} // namespace OhEngine
