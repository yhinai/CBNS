# 🧮 CBNS Calculator

<div align="center">

[![Live Demo](https://img.shields.io/badge/🌐_Live_Demo-Visit_Calculator-blue?style=for-the-badge)](http://cbns-calculator.herokuapp.com/)
[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Node.js](https://img.shields.io/badge/Node.js-43853D?style=for-the-badge&logo=node.js&logoColor=white)](https://nodejs.org/)
[![SystemVerilog](https://img.shields.io/badge/SystemVerilog-FF6B35?style=for-the-badge&logo=systemverilog&logoColor=white)](https://www.systemverilog.io/)

**Revolutionary Complex Binary Number System Calculator**  
*Bridging the gap between complex mathematics and efficient computation*

</div>

---

## ✨ What is CBNS?

**CBNS (Complex Binary Number System)** is an innovative numerical representation system that elegantly handles complex number arithmetic in binary format. Unlike traditional approaches that separate real and imaginary components, CBNS provides a unified, efficient method for complex number computation.

```
Traditional: (a + bi) + (c + di) = (a+c) + (b+d)i
CBNS:        Direct binary operations on unified representation
```

## 🚀 Features

### 🔢 **Core Mathematics**
- ➕ **Addition & Subtraction** - Lightning-fast complex arithmetic
- ✖️ **Multiplication & Division** - Precision complex operations  
- 🔄 **Seamless Conversion** - Decimal ↔ CBNS transformation
- 🎯 **High Precision** - Maintains accuracy across operations

### 💻 **Multi-Platform Implementation**
- 🌐 **Web Interface** - Interactive calculator with real-time results
- ⚡ **Native C++ Engine** - High-performance computation core
- 🔧 **Hardware Design** - SystemVerilog FPGA implementation
- 🚀 **Node.js Integration** - Seamless web-to-native binding

### 🎨 **User Experience**
- 🖱️ **Intuitive Interface** - Clean, responsive design
- 📱 **Cross-Platform** - Works on desktop, tablet, and mobile
- 🔍 **Real-time Visualization** - See CBNS representation instantly
- 📊 **Detailed Results** - Comprehensive operation breakdown

---

## 🛠️ Quick Start

### 🌐 Try It Online
Experience CBNS Calculator instantly in your browser:
```
🔗 http://cbns-calculator.herokuapp.com/
```

### 💻 Local Development

#### Prerequisites
```bash
# Required tools
- Node.js (v12 or higher)
- npm or yarn
- C++ compiler (GCC/MSVC)
- Python (for node-gyp)
```

#### Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/CBNS.git
cd CBNS

# Navigate to web calculator
cd website/cbns-calculator

# Install dependencies
npm install

# Build native modules
npm run rebuild

# Start the server
npm start
```

#### C++ Standalone
```bash
# Compile the standalone version
g++ -std=c++17 main.cpp -o cbns_calculator

# Run interactive calculator
./cbns_calculator
```

---

## 📋 Usage Examples

### Web Interface
```javascript
// Simple addition
(2.5, 3.0j) + (1.5, 2.0j) = 11010110000101011 + 1101000110110101 
                           = 11011111100111111 
                           = (4.0, 5.0j)
```

### C++ API
```cpp
#include "libCBNS.h"

// Create complex numbers
complex<float> a(2.5, 3.0);
complex<float> b(1.5, 2.0);

// Perform CBNS operations
string result = addComplex(a, b);
cout << "CBNS Result: " << result << endl;

// Convert back to complex
complex<float> final = CBNStoDec(result);
cout << "Final: " << final << endl;
```

### Hardware Implementation
```systemverilog
// ALU module instantiation
ALU #(16) calculator(
    .operation(op_code),
    .operand_1(cbns_a),
    .operand_2(cbns_b),
    .Res(cbns_result)
);
```

---

## 🏗️ Project Structure

```
CBNS/
├── 📁 HW_implementation/          # Hardware design files
│   ├── 🔧 ALU.sv                 # Main ALU implementation
│   ├── ➕ addComplex.sv          # Addition logic
│   ├── ✖️ multiComplex.sv        # Multiplication logic
│   └── 🧪 addComplex_tb.sv       # Testbench files
├── 📁 website/cbns-calculator/   # Web application
│   ├── 🌐 index.js              # Express server
│   ├── ⚙️ src/calculator.cc      # Native C++ bindings
│   ├── 📚 src/libCBNS.h         # Core CBNS library
│   └── 🎨 views/                # Frontend templates
├── 📚 libCBNS.h                 # Standalone C++ library
├── 🚀 main.cpp                  # Console application
└── 📖 README.md                 # You are here!
```

---

## 🔬 Technical Deep Dive

### Algorithm Overview
The CBNS system uses a base `(-1+j)` representation, enabling:

- **Unified Storage**: Single binary string for complex numbers
- **Efficient Operations**: Direct binary manipulation
- **Hardware Optimization**: Simplified FPGA/ASIC implementation
- **Precision Maintenance**: No floating-point accumulation errors

---

## 🤝 Contributing

We welcome contributions! Here's how you can help:

### 🐛 **Found a Bug?**
- Open an issue with detailed reproduction steps
- Include input values and expected vs actual output

### 💡 **Have an Enhancement?**
- Fork the repository
- Create a feature branch: `git checkout -b feature/amazing-feature`
- Implement your changes with tests
- Submit a pull request

### 📝 **Improve Documentation?**
- Help us make CBNS more accessible
- Add examples, tutorials, or clarifications



## 📚 Research & Citations

This project implements concepts from cutting-edge research in computer arithmetic and number system design. If you use CBNS in academic work, please consider citing:

```bibtex
@software{cbns_calculator,
  title={CBNS Calculator: Complex Binary Number System Implementation},
  author={[Yahya Alhinai]},
  year={2024},
  url={https://github.com/yhinai/CBNS}
}
```
