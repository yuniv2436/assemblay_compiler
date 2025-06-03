
# Two-Pass Assembler Compiler

This project implements a **two-pass compiler** that translates simplified assembly language into a custom machine-level binary format. It is written entirely in C, focusing on modular design, clear memory management, and robust error handling. The resulting binaries can be used in a simulated environment to test low-level instructions and data operations.

---

## 🚀 Features

✅ **Two-Pass Compilation**  
- **First Pass**: Parses the source code, builds the symbol table, and resolves labels and memory addresses.  
- **Second Pass**: Encodes validated instructions and operands into machine-level binary format.

✅ **Macro Processing**  
- A preprocessor identifies and expands user-defined macros, enabling code reuse and clarity.

✅ **Symbol Table Management**  
- Dynamically allocates and updates symbol entries, managing scope and usage (e.g., data, code, external, entry).

✅ **Robust Parsing**  
- Validates instructions, operands, labels, and data declarations with detailed error reporting.

✅ **Advanced Error Handling**  
A standout feature of this assembler is its **robust, user-friendly error reporting system**. The compiler detects and reports a wide range of syntax and semantic errors during both passes, including:
- Invalid or duplicate label names  
- Misplaced commas or extraneous text  
- Instruction word mismatches  
- Operand count and format errors  
- String and data declaration issues  
- Label length and character restrictions  

Each error is accompanied by the exact line number and a detailed message, ensuring clarity for debugging and correctness in the compiled binary output.

✅ **Custom Output Formats**  
- Generates:  
  - `.object` file containing the binary code and data sections.  
  - `.ext` file listing external symbols and their usage.  
  - `.ent` file listing entry points for the program.

✅ **Memory-Safe Implementation**  
- Uses explicit memory allocation (`malloc`, `free`) with consistent cleanup to avoid memory leaks.

---

## 📂 Project Structure

```
.
├── main.c             # Entry point for compilation process
├── macro.c/h          # Macro processing logic
├── ride1.c/h          # First pass: label parsing, symbol table construction
├── ride2.c/h          # Second pass: binary encoding, output file generation
├── symbols.c/h        # Symbol table linked list implementation
├── utils.c/h          # Utility functions for parsing and string manipulation
├── globals.c/h        # Global definitions, instruction metadata
├── makefile           # Build automation
└── README.md          # Project overview and usage
```

---

## 🛠️ Build & Run

### Build
Use the included `makefile` for convenient compilation:
```bash
make
```

This will generate the executable `assembler`.

### Usage
```bash
./assembler <source-file>.as
```

Example:
```bash
./assembler myProgram.as
```

The assembler will produce `.object`, `.ext`, and `.ent` output files.

---

## ⚙️ Core Components

### 🔹 Preprocessor
Expands macros and produces an `.am` file with inline macro code.

### 🔹 Symbol Table
Maintains a linked list of labels and their attributes, including:
- Address
- Type (data/code/external/entry)
- Usage across instructions

### 🔹 First Pass (`ride1`)
- Parses each line for label definitions and directives.
- Validates syntax and builds the symbol table.

### 🔹 Second Pass (`ride2`)
- Generates machine-level binary code for instructions and data.
- Resolves symbols using the previously constructed symbol table.
- Outputs formatted binary code to object and supplementary files.

---

## 📜 Key Implementation Highlights

- **Bit Field Structures**: Custom binary format encoding via bit fields for first, second, and additional words.
- **Dynamic Memory Handling**: Clean and consistent `malloc`/`free` usage for symbol tables, macros, and parsing buffers.
- **Error Handling**: Clear, line-specific error messages for invalid syntax and edge cases.
- **Modular Design**: Cleanly separated source files for maintainability and ease of understanding.

---

## 🌟 Why This Project Stands Out

✅ Comprehensive assembler compiler, written from scratch in C.  
✅ Demonstrates deep understanding of parsing, dynamic data structures, and low-level binary encoding.  
✅ Highlights engineering best practices in modularity, error handling, and resource management.  
✅ An excellent showcase of your ability to build robust, efficient systems from the ground up!

---

## 📜 License

This project is licensed under the MIT License.

---

## 🔗 Contact

For questions or further discussion, feel free to reach out!
