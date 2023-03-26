#pragma once

#include <array>
#include <cstddef>
namespace engine {

  // Template class, which allows for getting the change in an array
  // of variables.

  // It takes and array of variables and returns the difference
  // between those variables and the ones from the last time it was
  // called, then it stores the given variables for next time.

  template <typename T, std::size_t Size>
  class DeltaVariable {
  private:
    // Array of variables from last vall.
    std::array<T, Size> m_LastVars;
  public:

    // Initialize array of last variables in constructor.
    DeltaVariable(std::array<T, Size> Start) {
      m_LastVars = Start;
    }

    std::array<T, Size> GetDelta(std::array<T, Size> Absolute) {
      std::array<T, Size> Delta;
      for(int i = 0; i < Size; i++) {
	Delta[i] = Absolute[i] - m_LastVars[i];
	m_LastVars[i] = Absolute[i];
      }
      return Delta;
    }

    std::size_t GetSize() {
      return Size;
    }
  };

}
