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

#ifndef CLI_H
#define CLI_H

#include <vector>
#include <string>
#include <functional>
#include <string_view>
#include "xfiler.h"
#include <iostream>
#include <cstdint>
#include "cli_msgs.h"

class CLI final {
public:
    CLI() = default;
    CLI(int argc, char* argv[]) : m_argc(argc), m_argv(argv) {};
    void run(void);
    void onAbout(void);

private:
    void doQuickVerify(const std::string& path, uint64_t expectedHash);
    struct MenuItem {
    std::string_view title;
    std::function<void()> action; };

    inline void addItem(const std::string_view title, std::function<void()> action) {
        items.push_back({ title, action });
    }

    inline void clearScreen() {
        std::cout << "\033[2J\033[H" << std::flush;
    }

    inline std::string_view TypeToStr(XFile::HashType type)
    {
        size_t index = static_cast<size_t>(type);
        constexpr size_t hashNamesCount = sizeof(xfic::mainCLI::hashNames) / sizeof(xfic::mainCLI::hashNames[0]);
        return (index < hashNamesCount) ? xfic::mainCLI::hashNames[index] : xfic::errorMsg::UNDEFINED;
    }

    void doQuickHash(const std::string& path, XFile::HashType type);
    uint64_t parseHex(const std::string& hexStr);
    XFile::HashType StrToType(std::string_view method);

    void display(std::string_view header, std::string_view exitLabel, bool needRedraw);
	void hashFormat(XFile::HashType type);
    void pause(void);

    void onCalculate(void);
    void onVerify(void);
	void onSupport(void);
	void onHelp(void);
	void onUpdate(void);
	void getVersion(void);

    XFile xfile;
    std::vector<MenuItem> items;
    std::string path2file;
    bool running = true;
    int m_argc = 0;              
    char** m_argv = nullptr;    

};
#endif
