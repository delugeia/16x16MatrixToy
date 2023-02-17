#pragma once
#include "../global.hpp"

static const CRGB BallColors[] = {CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::Orange, CRGB::Indigo};

class BouncingBallEffect {
 private:
  double InitialBallSpeed(double height) const { return sqrt(-2 * Gravity * height); }

  size_t _cLength;
  size_t _cBalls;
  byte _Fade;
  bool _bMirrored;
  double _SpeedKnob;

  const double Gravity = -9.81;
  const double StartHeight = 1;
  const double ImpactVelocity = InitialBallSpeed(StartHeight);
  const double SpeedKnob = 4.0;

  vector<double> ClockTimeAtLastBounce, Height, BallSpeed, Dampening;
  vector<CRGB> Colors;

  double Time() const {
    timeval tv = {0};
    gettimeofday(&tv, nullptr);
    return (double)(tv.tv_usec / (double)1000000 + (double)tv.tv_sec);
  }

 public:
  // https://youtu.be/ysI30OrkiAc?t=676

  BouncingBallEffect(size_t cLength, size_t ballCount = 3, byte fade = 0, double SpeedKnob = 4.0, bool bMirrored = false)
      : _cLength(cLength - 1),
        _cBalls(ballCount),
        _Fade(fade),
        _bMirrored(bMirrored),
        _SpeedKnob(SpeedKnob),
        ClockTimeAtLastBounce(ballCount),
        Height(ballCount),
        BallSpeed(ballCount),
        Dampening(ballCount),
        Colors(ballCount) {
    for (size_t i = 0; i < ballCount; i++) {
      Height[i] = StartHeight;
      ClockTimeAtLastBounce[i] = Time();
      Dampening[i] = 0.90 - i / pow(_cBalls, 2);
      BallSpeed[i] = InitialBallSpeed(Height[i]);
      Colors[i] = BallColors[i % ARRAYSIZE(BallColors)];
    }
  }

  virtual void Draw() {
    if (_Fade) {
      for (size_t i = 0; i < _cLength; i++) {
        g_LEDs[i].fadeToBlackBy(_Fade);
      }
    } else {
      FastLED.clear();
    }

    for (size_t i = 0; i < _cBalls; i++) {
      double TimeSinceLastBounce = (Time() - ClockTimeAtLastBounce[i]) / SpeedKnob;

      Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce, 2.0) + BallSpeed[i] * TimeSinceLastBounce;

      if (Height[i] < 0) {
        Height[i] = 0;
        BallSpeed[i] = Dampening[i] * BallSpeed[i];
        ClockTimeAtLastBounce[i] = Time();

        if (BallSpeed[i] < 1.0) {
          BallSpeed[i] = InitialBallSpeed(StartHeight) * Dampening[i];
        }
      }

      size_t position = (size_t)(Height[i] * (_cLength - 1) / StartHeight);
      g_LEDs[position] += Colors[i];
      g_LEDs[position + 1] += Colors[i];

      if (_bMirrored) {
        g_LEDs[_cLength - 1 - position] += Colors[i];
        g_LEDs[_cLength - position] += Colors[i];
      }
    }
  }
};
