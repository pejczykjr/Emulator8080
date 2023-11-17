#pragma once

#ifdef _MSC_VER
	#define INLINE // __forceinline ???
#else
	#define INLINE inline __attribute__((always_inline))
#endif

#include <stdint.h>
#include <stdexcept>

namespace RegistersNamespace {

	typedef uint32_t regInt;
	typedef uint8_t flagInt;

	// Public enum types for register / flag selections

	enum class Flag {
		S,  // Sign flag
		Z,  // Zero flag
		P,  // Parity flag
		C,  // Carry flag
		AC  // Auxiliary carry flag
	};

	enum class Reg {

		// 8-bit registers
		A,          // Accumulator
		B, C, D, E, // General purpose registers
		H, L,       // Indirect address registers
		Flags,      // Flags register (internal, not accessible by operands)

		// 16-bit registers         MSB LSB
		PSW, // Program status word (A & Flags)
		BC,  // Register pair BC    (B & C)
		DE,  // Register pair DE    (D & E)
		HL,  // Also called M       (H & L)
		SP,  // Stack pointer       Always 16-bit
		PC   // Program counter     Always 16-bit
	};

	class Registers {
	public:

		// Templates and inlines require method definition directly in the .h file

		template<Reg reg> INLINE regInt getReg() {
			switch (reg) {
				// 8-bit register returns

				case Reg::A: return A;
				case Reg::B: return B;
				case Reg::C: return C;		
				case Reg::D: return D;	
				case Reg::E: return E;
				case Reg::H: return H;
				case Reg::L: return L;		

				//16-bit register returns

				case Reg::PSW: return ((A & 0x000000FF) << 8) | (flags.value & 0x000000FF);					
				case Reg::BC:  return ((B & 0x000000FF) << 8) | (C & 0x000000FF);
				case Reg::DE:  return ((D & 0x000000FF) << 8) | (E & 0x000000FF);
				case Reg::HL:  return ((H & 0x000000FF) << 8) | (L & 0x000000FF);
				case Reg::SP:  return SP;					
				case Reg::PC:  return PC;
					
				default:
					throw std::invalid_argument("Invalid register get");
					return 0;
			}
		}

		//template<Register reg> inline void setReg(regInt value) {}

		template<Flag flag> INLINE bool getFlag() {
			switch (flag) {
				case Flag::S:  return flags.bitField.S != 0;
				case Flag::Z:  return flags.bitField.Z != 0;
				case Flag::P:  return flags.bitField.P != 0;
				case Flag::C:  return flags.bitField.C != 0;
				case Flag::AC: return flags.bitField.AC != 0;

				default:
					throw std::invalid_argument("Invalid flag get");
					return 0;
			}
		}

		//template<Flag flag> inline void setFlag(bool value) {}

		INLINE void setAllFlags(flagInt value) {
			flags.value = value & 0b00011111;
		}

	private:

		// Physical register state variables

		regInt A, B, C, D, E, H, L, SP, PC;

		// Physical flag bit fields

		union Flags {
			struct {
				uint8_t S  : 1;
				uint8_t Z  : 1;
				uint8_t P  : 1;
				uint8_t C  : 1;
				uint8_t AC : 1;
			} bitField;
			flagInt value;
		} flags;
	};
}