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

#pragma once

#include <cstdio>
#include <array>
#include <string>
#include <iostream>
#include <ostream>
#include <exception>
#include "cli_msgs.h"

inline std::string execExternalCommand(const std::string& cmd) {
    std::array<char, 128> buffer{};
    std::string result;
#ifdef _WIN32
    auto pipe = _popen(cmd.c_str(), "r");
#else
    auto pipe = popen(cmd.c_str(), "r");
#endif
    if (!pipe) return "";
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    return result;
}


inline void checkUpdates() {
    const std::string url = std::string(xfic::updater::API_URL_BASE) +
        std::string(xfic::updater::SOURCE) +
        std::string(xfic::updater::API_URL_SUFFIX);
    const std::string cmd = "curl " + std::string(xfic::updater::CURL_FLAGS) +
        " -H \"User-Agent: " + std::string(xfic::updater::USER_AGENT) + "\" " +
        url + std::string(xfic::updater::CURL_REDIR_ERR);

    std::cout << xfic::mainTUI::MAIN << xfic::updater::MSG_INFO_START << std::endl;

    try {
        std::string response = execExternalCommand(cmd);

        if (response.empty()) {
            std::cout << xfic::updater::MSG_ERR_CURL << std::endl;
            return;
        }

        //if (response.length() > xfic::updater::MAX_RESPONSE_PREVIEW) {
        //    std::cout << xfic::updater::MSG_INFO_RESP << response.substr(0, xfic::updater::MAX_RESPONSE_PREVIEW) << "}" << std::endl;
        //} dbg usecase only
        //else {
        //    std::cout << xfic::updater::MSG_INFO_RESP << response << std::endl;
        //}

        size_t tagKeyPos = response.find(xfic::updater::JSON_TAG_KEY);
        if (tagKeyPos != std::string::npos) {
            size_t openQ = response.find("\"", tagKeyPos + xfic::updater::JSON_TAG_KEY.length());
            if (openQ != std::string::npos) {
                size_t start = openQ + 1;
                size_t end = response.find("\"", start);
                std::string latestVersion = response.substr(start, end - start);


                std::cout << xfic::updater::MSG_INFO_CURR << xfic::updater::CURRENT_VERSION << "\n"
                    << xfic::updater::MSG_INFO_LATE << latestVersion << std::endl;

                if (latestVersion != xfic::updater::CURRENT_VERSION) {
                    std::cout << "\n" << xfic::updater::MSG_NEW_VER << latestVersion << "\n";
                    std::cout << xfic::updater::MSG_DOWNLOAD << xfic::updater::GITHUB_BASE
                    << xfic::updater::SOURCE << xfic::updater::RELEASE_PATH << "\n";
					std::cout << xfic::updater::MSG_GIT_CMD << xfic::updater::GIT_PREFIX
					<< xfic::updater::GITHUB_BASE << xfic::updater::SOURCE 
                        << xfic::updater::MSG_CHECK_README << std::endl;
                }
                else {
                    std::cout << xfic::updater::MSG_INFO_NONE << "\n"
                        << xfic::updater::MSG_INFO_LATEST << std::endl;
                }
            }
        }
        else {
            std::cout << xfic::updater::MSG_ERR_TAG << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << xfic::updater::MSG_ERR_EXCEPT << e.what() << std::endl;
    }
}