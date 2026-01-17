# Contributing to XFIChecker

First of all, thanks for taking the time to contribute! 

## How Can I Help?

### 🐛 Reporting Bugs
- Check the [Issues](https://github.com/anonyaro/XFIChecker/issues) to see if the bug has already been reported.
- If not, create a new issue. 
- Please include:
  - Your Operating System (Windows/Linux).
  - Compiler version (GCC/Clang/MSVC).
  - Steps to reproduce the bug.

### 💡 Feature Requests
Feel free to open an issue to suggest new hash algorithms or TUI/CLI improvements!
Fast and optimized hash algorithms integrations are welcome!
Do not try to integrate third party API's nor frameworks or libraries, without discussing it

### 🔧 Pull Requests
1. Fork the repo and create your branch from `master`.
2. **Code Style**: Keep it clean and follow C++17 standards. Use TABS for indentation. Keep the codebase readable.
3. **Manual Verification**: Since we don't have automated tests yet (in progress), please verify your changes manually:
   - Ensure the project builds without errors using CMake & Ninja.
   - Run XFIChecker on a few files and verify that hash calculations are correct.
   - Check that the TUI/CLI doesn't crash.
4. Open a Pull Request with a description of what you've changed.

## 📜 License
By contributing, you agree that your contributions will be licensed under the project's [LICENSE](LICENSE).
