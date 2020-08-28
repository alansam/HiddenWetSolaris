/*
 *  @see: https://en.cppreference.com/w/cpp/utility/bitset/bitset
 */

#include <iostream>
#include <iomanip>
#include <ios>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <climits>

using namespace std::string_literals;

//  MARK: - Definitions.
template<typename T>
std::ostream& operator<<(std::ostream & os, const std::vector<T> & vec) {
  for (auto & el : vec) {
      os << el << ' ';
  }
  return os;
}

//  MARK: Struct S
#define B 3
#define C 12
#define D 4
struct S {
  uint32_t b : B;
  bool       : 1;  //  filler ~ 1 bit.
  uint32_t c : C;
  uint64_t   : 0;  //  filler ~ next int
  bool       : 8;  //  filler ~ next byte
  uint32_t d : D;
};

//  MARK: Prototypes
void me_sample(void);
void cppreference_sample(void);
template <class T>
void me_prdump(T const & s, std::string const & title); 

//  MARK: - Implementation
/*
 *  MARK: main()
 */
int main() {
  std::vector<std::string> vec = {
    "Hello", "from",
    "GCC", __VERSION__,
    "\n          ",
    "C++", std::to_string(__cplusplus),
    "!"
  };
  std::cout << vec << std::endl;

  me_sample();
  cppreference_sample();

  return EXIT_SUCCESS;
}

/*
 *  MARK: me_sample()
 */
void me_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  //  set up the struct bin-3, bin-12, bin-4
  S s { .b = 0b101, .c = 0b111011101110, .d = 0b1011, };

  //  create bitsets from the struct parts
  std::bitset<B> bB(s.b);
  std::bitset<C> bC(s.c);
  std::bitset<D> bD(s.d);

  //  display the struct contents
  std::cout << std::setw(6) << s.b << ' '
            << std::setw(2) << std::setfill('0') << std::hex << s.b << ' '
            << std::setw(8) << std::setfill(' ') << bB
            << " : "
            << std::setw(4) << std::setfill('0') << std::hex << s.c << ' '
            << std::setw(16) << std::setfill(' ') << bC
            << " : "
            << std::setw(4) << std::setfill('0') << std::hex << s.d << ' '
            << std::setw(8) << std::setfill(' ') << bD
            << std::endl;

  //  do a print dump of the structure
  me_prdump(s, "Struct \'S\'"s);

  return;
}

/*
 *  MARK: cppreference_sample()
 *  @see: https://en.cppreference.com/w/cpp/utility/bitset/bitset
 */
void cppreference_sample(void) {
  std::ios init(nullptr);
  init.copyfmt(std::cout);  //  save cout state

  std::cout.width(40);
  std::cout.fill('.');
  std::cout << '\n';
  std::cout << "Func: " << __func__ << '\n' << std::endl;
  std::cout.copyfmt(init);  //  restore cout state

  // empty constructor
  std::bitset<8> b1; // [0,0,0,0,0,0,0,0]

  // unsigned long long constructor
  std::bitset<8> b2(42);          // [0,0,1,0,1,0,1,0]
  std::bitset<70> bl(ULLONG_MAX); // [0,0,0,0,0,0,1,1,1,...,1,1,1] in C++11
  std::bitset<8> bs(0xfff0);      // [1,1,1,1,0,0,0,0]

  // string constructor
  std::string bit_string = "110010";
  std::bitset<8> b3(bit_string);       // [0,0,1,1,0,0,1,0]
  std::bitset<8> b4(bit_string, 2);    // [0,0,0,0,0,0,1,0]
  std::bitset<8> b5(bit_string, 2, 3); // [0,0,0,0,0,0,0,1]

  // string constructor using custom zero/one digits
  std::string alpha_bit_string = "aBaaBBaB";
  std::bitset<8> b6(alpha_bit_string, 0, alpha_bit_string.size(),
                    'a', 'B');         // [0,1,0,0,1,1,0,1]

  // char* constructor using custom digits
  std::bitset<8> b7("XXXXYYYY", 8, 'X', 'Y'); // [0,0,0,0,1,1,1,1]

  std::cout << b1 << '\n' << b2 << '\n' << bl << '\n' << bs << '\n'
            << b3 << '\n' << b4 << '\n' << b5 << '\n' << b6 << '\n'
            << b7 << '\n';

  return;
}

/*
 *  MARK: me_prdump()
 *  Print a dump (hex, decimal octal, binary & character)
 *  of an instance of a class/struct etc.
 * Copyright (C) Alan Sampson, 202. All rights reserved.
 */
template<class T>
void me_prdump(T const & s, std::string const & title) {

  uint8_t const * sp;
  sp = reinterpret_cast<uint8_t const *>(&s);

  std::cout << '\n' << title
            << " - Size: " << std::dec << std::setw(6)
            << sizeof(T)
            << " ["
            << std::setw(8) << std::setfill('0') << std::hex
            << sizeof(T)
            << "]"
            << std::endl;
  std::cout << "Dump address: "
            << static_cast<void const *>(sp)
            << std::endl;
  std::cout << "Offset: Hex - Dec - Oct - Bin      - Char"
            << std::endl;
  uint16_t offset = 0;
  for (size_t p_ = 0; p_ < sizeof(T); ++p_) {
    uint8_t ibyte = *sp++;
    std::bitset<8> bbyte(ibyte);
    std::cout << "  "
              << std::hex << std::setw(4) << std::setfill('0')
              << offset++ << ": "
              << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<uint16_t>(ibyte)
              << "  - "
              << std::dec << std::setw(3) << std::setfill('0')
              << static_cast<uint16_t>(ibyte)
              << " - "
              << std::oct << std::setw(3) << std::setfill('0')
              << static_cast<uint16_t>(ibyte)
              << " - "
              << std::hex << std::setw(8) << std::setfill(' ')
              << bbyte
              << " - "
              << std::dec << std::setw(1) << std::setfill(' ')
              << (std::isprint(ibyte) ? static_cast<char>(ibyte) : '.')
              << '\n';
  }
  std::cout << std::endl;

  return;
}
