#pragma once

#include "IFilter.hpp"

namespace DSP {
namespace Filter {
  class MonoBiquad {
  public:
    MonoBiquad();

    void setCoefficients(float b0, float b1, float b2, float a0, float a1, float a2);

    int16_t filter(int16_t x);

  private:
    static const int FRAC_BITS_COEF = 25; //signed 6.25 fixed point
    static const int FRAC_BITS_SAMPLE = 16; //signed 15.16 fixed point

    static int32_t convertCoefficient(float coef);
    
    int32_t m_b0, m_b1, m_b2, m_a1, m_a2;
    int32_t m_x1, m_x2, m_y1, m_y2;
  };

  class BiquadFilter : public IFilter {
  public:
    void processSamples(uint8_t* data, uint32_t len) override;

  protected:
    void setCoefficients(float b0, float b1, float b2, float a0, float a1, float a2);

  private:
    MonoBiquad m_leftBiquad, m_rightBiquad;
  };

  namespace Biquad {
    class ManualFilter : public BiquadFilter {
    public:
      ManualFilter(float b0, float b1, float b2, float a0, float a1, float a2);

      void setSampleRate(int sampleRate) override;
    private:
      float m_b0, m_b1, m_b2, m_a0, m_a1, m_a2;
    };

    class LPF : public BiquadFilter {
    public:
      LPF(float fc, float Q);

      void setSampleRate(int sampleRate) override;

    private:
      float m_fc, m_Q;
    };

    class HPF : public BiquadFilter {
    public:
      HPF(float fc, float Q);

      void setSampleRate(int sampleRate) override;

    private:
      float m_fc, m_Q;
    };

    class PeakingEQ : public BiquadFilter {
    public:
      PeakingEQ(float f0, float Q, float A);

      void setSampleRate(int sampleRate) override;

    private:
      float m_f0, m_Q, m_A;
    };

    class LowShelf : public BiquadFilter {
    public:
      LowShelf(float f0, float Q, float A);

      void setSampleRate(int sampleRate) override;

    private:
      float m_f0, m_Q, m_A;
    };
    
    class HighShelf : public BiquadFilter {
    public:
      HighShelf(float f0, float Q, float A);

      void setSampleRate(int sampleRate) override;

    private:
      float m_f0, m_Q, m_A;
    };
  }
}
}
