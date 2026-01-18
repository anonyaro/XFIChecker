# Contributing to XFIChecker

***First of all, thanks for taking the time to contribute! We appreciate your help in making XFIChecker more robust and faster.***

## How Can I Help?

### 🐛 Reporting Bugs
- Check the [Issues](https://github.com/anonyaro/XFIChecker/issues) to see if the bug has already been reported.
- If not, create a new issue. 
- Please include:
  - Your Operating System (Windows/Linux).
  - Compiler version (GCC/Clang/MSVC).
  - Steps to reproduce the bug.
  - If possible, the file type or size that caused the issue.

### 💡 Feature Requests
*Feel free to open an issue to suggest new hash algorithms or TUI/CLI improvements!*
*Fast and optimized hash algorithm integrations are always welcomed.*

**Important:** Please discuss any third-party APIs, frameworks, or libraries with the maintainers before starting work. We aim to keep the project lightweight and "bloat-free" with minimal external dependencies.**

### 🔧 Pull Requests
1. **Fork the repo** and create your branch from `master`.
2. **Code Style**: 
   *- Use **TABS** for indentation.*
   *- Follow **C++17** standards.*
   *- Keep the code clean, readable, and well scalable.*
3. **Automated Testing (Mandatory)**:
   *We use **Google Test (GTest)** for unit testing.* 
   *- If you modify the hashing logic or core engine, **run the existing tests**:*
     ```bash
     cmake -B build -DBUILD_TESTING=ON
     cmake --build build --target xfichecker_unit_tests
     ./build/xfichecker_unit_tests
     ```
   *- If you add a new algorithm, you **must** add a corresponding test case in `unit_tests/unit_test.cpp` with verified "ground truth" values.*
4. **Build Verification**:
   *- Ensure the project builds without errors/warnings using **CMake** and **Ninja/Make**.*
   *- Verify that your changes don't break the TUI/CLI menu's.*
5. **Mandatory Attribution**:
   *- Do not remove or modify the author attribution or donation links in the UI/Output unless specifically discussed.*

## 📜 License & Legal
**By contributing, you agree that your contributions will be licensed under the project's [AGPLv3 License](LICENSE).**

**You also acknowledge the mandatory attribution requirements as stated in the [NOTICE](NOTICE) file.**
