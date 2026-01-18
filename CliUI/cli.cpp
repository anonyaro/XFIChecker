/*
 * Copyright (C) 2026 anonyaro (github.com/anonyaro)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * --- MANDATORY ATTRIBUTION NOTICE ---
 * In accordance with Section 7(b) of the GNU AGPLv3, the following
 * appropriate legal notices must be preserved and displayed in the
 * user interface of any work incorporating this software:
 *
 * Author: anonyaro (github.com/anonyaro)
 * Project: XFIChecker (https://github.com/anonyaro/XFIChecker)
 * Support: https://dalink.to/xenyaro
 */

#include "cli.h"
#include <array>
#include "xfilerrorhandler.h"
#include <iostream>
#include <limits>
#include <fstream> 
#include <filesystem>
#include <string>
#include <string_view>
#include <functional>
#include <cstdlib>
#include <cstdint>
#include "xfiler.h"
#include <stdexcept>
#include "cli_msgs.h"
#include "fastupdater.h"

void CLI::run(void) {
    if (m_argv != nullptr && m_argc > 1) {
        std::string_view cli(m_argv[1]);

        if (cli == xfic::mainCLI::CLI_ABOUT || cli == xfic::mainCLI::CLI_ABOUT_S) { onAbout(); return; }
        if (cli == xfic::mainCLI::CLI_SUPPORT || cli == xfic::mainCLI::CLI_SUPPORT_S) { onSupport(); return; }
        if (cli == xfic::mainCLI::CLI_HELPER || cli == xfic::mainCLI::CLI_HELPER_S) { onHelp(); return; }
        if (cli == xfic::mainCLI::CLI_VERSION || cli == xfic::mainCLI::CLI_VERSION_S) { getVersion(); return; }
        if (cli == xfic::mainCLI::CLI_UPDATER || cli == xfic::mainCLI::CLI_UPDATER_S) { onUpdate(); return; }

        if (cli == xfic::mainCLI::CLI_VERIFY) {
            if (m_argc != 5 || std::string_view(m_argv[3]) != xfic::mainCLI::CLI_EXPECTED)
                throw std::runtime_error(static_cast<std::string>(xfic::mainCLI::CLI_VERIFY_NOTIFICATOR));

            uint64_t expected = parseHex(m_argv[4]);
            doQuickVerify(m_argv[2], expected);
            return;
        }

        if (cli == xfic::mainCLI::CLI_CALCULATE) {
            if (m_argc != 4)
                throw std::runtime_error(static_cast<std::string>(xfic::mainCLI::CLI_CALC_NOTIFICATOR));

            auto type = StrToType(m_argv[3]);
            doQuickHash(m_argv[2], type);
            return;
        }

        throw std::runtime_error(static_cast<std::string>(xfic::errorMsg::UNKNOWN_C) + std::string(cli) +
            static_cast<std::string>(xfic::mainCLI::CLI_NOTIFICATOR));
    }

    items.clear();

    addItem(xfic::mainTUI::CALC, [this]() { onCalculate(); });
    addItem(xfic::mainTUI::CHECK, [this]() { onVerify(); });
    addItem(xfic::mainTUI::ABOUT, [this]() { onAbout(); });
    addItem(xfic::mainTUI::SUPPORT, [this]() { onSupport(); });
    addItem(xfic::mainTUI::HELPER, [this]() { onHelp(); });
    addItem(xfic::mainTUI::UPDATER, [this]() { onUpdate(); });

    display(xfic::mainTUI::MAIN, xfic::mainTUI::EXIT, true);
}

//small, cheap-to-copy and scalar type
void CLI::doQuickHash(const std::string& path, XFile::HashType type) {
    auto hash = xfile.calculateHash(path, type);
    std::cout << TypeToStr(type) << xfic::logMsg::HASH_MSG
        << std::hex << std::uppercase << hash << std::dec << "\n"
        << xfic::logMsg::SUPPORT_MSG;
}

//trivially-copyable 
XFile::HashType CLI::StrToType(std::string_view method) {
    if (method == xfic::mainCLI::FNV1A)   return XFile::HashType::FNV1a;
    if (method == xfic::mainCLI::DJB2)    return XFile::HashType::DJB2;
    if (method == xfic::mainCLI::ADLER32) return XFile::HashType::ADLER_32;
    throw std::runtime_error(static_cast<std::string>(xfic::errorMsg::UNKNOWN) + std::string(method));
}

uint64_t CLI::parseHex(const std::string& hexStr) {
    try {
        size_t pos = 0;
        uint64_t val = std::stoull(hexStr, &pos, 16);
        if (pos != hexStr.length()) throw std::invalid_argument(static_cast<std::string>(xfic::errorMsg::EXTRA_C));
        return val;
    }
    catch (...) {
        throw std::runtime_error(static_cast<std::string>(xfic::errorMsg::INVALID_FORMAT) + hexStr + "'");
    }
}

//small, cheap-to-copy and scalar type
void CLI::doQuickVerify(const std::string& path, uint64_t expectedHash) {
    if (!std::filesystem::exists(path)) throw std::runtime_error(static_cast<std::string>(xfic::errorMsg::FILE_NF) + path);

    std::cout << xfic::logMsg::VERIFICATION_MODE_MSG << "\n";
    std::cout << xfic::logMsg::TARGET << path << "\n";
    std::cout << xfic::logMsg::EXPECTED << std::hex << std::uppercase << expectedHash << std::dec << "\n\n";

    bool found = false;
    const int count = static_cast<int>(XFile::HashType::ENDPOINT);

    for (int i = 0; i < count; ++i) {
        auto type = static_cast<XFile::HashType>(i);
        auto actual = xfile.calculateHash(path, type);

        if (actual == expectedHash) {
            std::cout << xfic::logMsg::MATCH_FOUND;
            std::cout << xfic::logMsg::ALGO << TypeToStr(type) << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << xfic::logMsg::UNMATCH;
    }

    // MANDATORY ATTRIBUTION (AGPLv3)
    std::cout << xfic::logMsg::VERIFIER_MSG << std::endl;
}

void CLI::pause(void) {
    std::cout << xfic::subTUI::RETURN << std::flush;

    std::cin.clear();

    std::cin.get();

    clearScreen();
}

void CLI::onCalculate(void) {
    try {
        std::cout << xfic::subTUI::RETURN << xfic::logMsg::OPTIONAL_MSG << std::endl << xfic::subTUI::FILE_PATH;
        if (!std::getline(std::cin, path2file) || path2file.empty()) {
            return;
        }
        std::ifstream file(path2file);
        if (!file.is_open()) {
            throw XFileError(path2file);
        }

        CLI subMenu;

        auto addHashItem = [&](auto label, auto prefix, XFile::HashType type) {
            subMenu.addItem(label, [this, prefix, type]() {
                std::cout << " [" << path2file << "] " << xfic::logMsg::CALCULATION_LOG << '\n';
                auto hash = xfile.calculateHash(path2file, type);
                std::cout << prefix << std::hex << std::uppercase
                    << hash << std::dec << xfic::logMsg::COMPLETION << '\n';
                });
            };

        addHashItem(xfic::subTUI::FNV_1A, xfic::logMsg::FNV, XFile::HashType::FNV1a);
        addHashItem(xfic::subTUI::DJB_2, xfic::logMsg::DJB, XFile::HashType::DJB2);
        addHashItem(xfic::subTUI::ADLER_32, xfic::logMsg::ADLER, XFile::HashType::ADLER_32);

        subMenu.display(xfic::subTUI::HASH_MENU, xfic::subTUI::BACK, false);
    }
    catch (const XFileError& ex) {
        std::cerr << xfic::errorMsg::ERROR_MSG << ex.what() << "\n";
        pause();
    }
}

void CLI::onVerify(void) {
    try {

        bool allMatch = true;
        bool anyMatch = false;
        bool anyProvided = false;

        std::cout << xfic::subTUI::RETURN << xfic::logMsg::OPTIONAL_MSG << std::endl << xfic::subTUI::FILE_PATH;
        if (!std::getline(std::cin, path2file) || path2file.empty()) return;

        if (!std::filesystem::exists(path2file) || !std::filesystem::is_regular_file(path2file))
            throw XFileError(path2file);

        const size_t hashCount = static_cast<size_t>(XFile::HashType::ENDPOINT);
        std::array<uint64_t, hashCount> expectedHashes{};
        std::array<bool, hashCount> isSkipped{};
        std::cout << xfic::subTUI::TOSKIP;
        for (size_t i = 0; i < hashCount; ++i) {
            hashFormat(static_cast<XFile::HashType>(i));

            std::string hexInput;
            std::getline(std::cin, hexInput);

            if (hexInput.empty()) {
                isSkipped[i] = true;
                continue;
            }

            try {
                expectedHashes[i] = std::stoull(hexInput, nullptr, 16);
                anyProvided = true;
            }
            catch (...) {
                std::cout << xfic::errorMsg::INVALID_FORMAT << std::endl;
                i--;
                continue;
            }
        }

        if (!anyProvided) {
            std::cout << xfic::logMsg::INFO;
            pause();
            return;
        }

        std::cout << std::dec << "\n [" << path2file << "]" << xfic::logMsg::VERIFICATION_MSG;

        auto results = xfile.verifyDataAll(path2file, expectedHashes);

        for (size_t i = 0; i < hashCount; ++i) {
            auto type = static_cast<XFile::HashType>(i);
            auto& result = results[type];

            std::cout << TypeToStr(type) << ": ";

            if (isSkipped[i]) {
                std::cout << xfic::logMsg::SKIPPED;
                continue;
            }

            if (result.isMatching) {
                std::cout << xfic::logMsg::MATCH;
                anyMatch = true;
            }
            else {
                std::cout << xfic::logMsg::MISMATH;
                std::cout << xfic::logMsg::EXPECTED << std::hex << std::uppercase << expectedHashes[i] << "\n";
                std::cout << xfic::logMsg::ACTUAL << result.actualValue << std::dec << "\n\n";
                allMatch = false;
            }
        }

        if (allMatch) {
            std::cout << xfic::logMsg::SUCCESS << xfic::logMsg::VERIFIER_MSG;
        }
        else if (anyMatch && !allMatch) {
            std::cout << xfic::logMsg::WARNING << xfic::logMsg::VERIFIER_MSG;
        }
        else {
            std::cout << xfic::errorMsg::ERROR << xfic::logMsg::VERIFIER_MSG;
        }

        pause();
    }
    catch (const XFileError& ex) {
        std::cerr << xfic::errorMsg::ERROR_MSG << ex.what() << "\n";
        pause();
    }
}

void CLI::hashFormat(XFile::HashType type) {
    std::cout
        << xfic::subTUI::EXPECTED_HASH.substr(0, xfic::subTUI::EXPECTED_HASH.find(':'))
        << " for ->"
        << TypeToStr(static_cast<XFile::HashType>(type))
        << ": ";
}

void CLI::onUpdate(void) {
    clearScreen();
    checkUpdates();
    pause();
}

void CLI::getVersion(void) {
    clearScreen();
    std::cout << xfic::logMsg::ABOUTMSG << std::endl;
    pause();
}
void CLI::onHelp(void)
{
    clearScreen();
    std::cout << xfic::mainTUI::MAIN << xfic::mainCLI::HELPER_MSG << std::endl;
    pause();
}

void CLI::onAbout(void) {
    clearScreen();
    std::cout << xfic::logMsg::ABOUTMSG << xfic::mainTUI::MAIN;
    pause();
}
void CLI::onSupport(void) {
    std::cout << xfic::logMsg::ONSUPPORT_LOG;

#if defined(_WIN32) || defined(_WIN64)
    // Windows
    std::string command = "start \"\" \"" + static_cast<std::string>(xfic::logMsg::SUPPORT_URL) + "\"";
    system(command.c_str());

#elif defined(__APPLE__)
    // macOS
    std::string command = "open " + static_cast<std::string>(xfic::logMsg::SUPPORT_URL);
    system(command.c_str());

#else
    // Linux & other Unix-like systems *using xdg-open for variety of DE's*
    std::string command = "xdg-open " + static_cast<std::string>(xfic::logMsg::SUPPORT_URL) + " > /dev/null 2>&1";
    int result = system(command.c_str());

    if (result != 0)
        std::cout << xfic::errorMsg::BROWSER_INVALID << xfic::logMsg::SUPPORT_URL << std::endl;
#endif
    pause();
}

void CLI::display(std::string_view header, std::string_view exitLabel, bool isPersistent) {
    clearScreen();
    std::cout << header << "\n";
    for (const auto& item : items) {
        std::cout << item.title << "\n";
    }
    std::cout << exitLabel << "\n";

    while (running) {
        std::cout << xfic::mainTUI::PROMPT;
        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << xfic::mainTUI::INVALID_TUI;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) break;

        if (choice > 0 && static_cast<size_t>(choice) <= items.size()) {
            items[static_cast<size_t>(choice) - 1].action();
            if (isPersistent) {
                clearScreen();
                std::cout << header << "\n";
                for (const auto& item : items) std::cout << item.title << "\n";
                std::cout << exitLabel << "\n";
            }
        }
        else {
            std::cout << xfic::mainTUI::INVALID << std::endl;
        }
    }
}
