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
#include <string_view>
#include <array>

namespace xfic { 

    namespace mainTUI {
        inline constexpr std::string_view MAIN = R"(
__________________________________________________________
>  __  __ _____ ___   ____ _               _             <
>  \ \/ /|  ___|_ _| / ___| |__   ___  ___| | _____ _ __ <
>   \  / | |_   | | | |   | '_ \ / _ \/ __| |/ / _ \ '__|<
>   /  \ |  _|  | | | |___| | | |  __/ (__|   <  __/ |   <
>  /_/\_\|_|   |___| \____|_| |_|\___|\___|_|\_\___|_|   <
>________________________________________________~ ~ ~ ~ <
                                            //  /   by   \
Support XFIChecker:                         \\__\anonyaro/
>https://dalink.to/xenyaro                       \______/
    )";

        inline constexpr std::string_view EXIT = "[0] Exit Program";
        inline constexpr std::string_view CALC = "[1] Calculate Hash";
        inline constexpr std::string_view CHECK = "[2] Verify Integrity";
        inline constexpr std::string_view ABOUT = "[3] About XFIChecker";
        inline constexpr std::string_view SUPPORT = "[4] Support the XFIChecker";
        inline constexpr std::string_view HELPER = "[5] Help to see more and usage sample";
        inline constexpr std::string_view UPDATER = "[6] Check for available updates and versions";
        inline constexpr std::string_view PROMPT = "\nSelect an option: ";
        inline constexpr std::string_view INVALID = " \n [!] Invalid command <-> Select \"5\" for help in main menu\n";
        inline constexpr std::string_view INVALID_TUI = " \n [!] Invalid input <-> Menu selection accepts only numbers, e.g: '1', '2', '3', '4', '5', '0' \n";
    }

    namespace subTUI {
        inline constexpr std::string_view HASH_MENU = R"(
--------------------------------------------------
-- Available Hash Calculation Algorithm Methods --
           Please support the author
           https://dalink.to/xenyaro
--------------------------------------------------
)";
        inline constexpr std::string_view BACK = "0. [ACTION] Back to Main Menu";
        inline constexpr std::string_view FNV_1A = "1. [METHOD] FNV-1a (64-bit)";
        inline constexpr std::string_view DJB_2 = "2. [METHOD] DJB2 (64-bit)";
        inline constexpr std::string_view ADLER_32 = "3. [METHOD] Adler-32 (32-bit)";
        inline constexpr std::string_view VERIFY_MENU = "--- Integrity Verification ---";
        inline constexpr std::string_view FILE_PATH = "\n [ACTION] Integrity Check\n Enter path to file: ";
        inline constexpr std::string_view EXPECTED_HASH = " Enter expected hash (in hex): ";
        inline constexpr std::string_view PATH2FILE = "\n Enter path to file: ";
        inline constexpr std::string_view RETURN = "\n[Press \"Enter\" to return...]";
        inline constexpr std::string_view TOSKIP = "\n [ACTION] Press \"Enter\" to skip or...\n";
    }

    namespace logMsg {
        inline constexpr std::string_view CALCULATION_LOG = " <-> Calculating hash...";
        inline constexpr std::string_view FNV = " [SUCCESS] FNV-1a Hash: 0x";
        inline constexpr std::string_view DJB = " [SUCCESS] DJB2 Hash: 0x";
        inline constexpr std::string_view ADLER = " [SUCCESS] Adler-32 Hash: 0x";
        inline constexpr std::string_view COMPLETION = "\n [*] Operation completed. Returning...\n";

        inline constexpr std::string_view ABOUTMSG = R"(
XFIChecker v1.0.0 (stable)
Copyright (C) 2026 anonyaro
Core Status: Verified (4/4 Unit-Tests Passed)

Project Home: https://github.com/anonyaro/XFIChecker
Author: anonyaro (https://github.com/anonyaro)
License: GNU AGPLv3

Support the project: https://dalink.to/xenyaro

"This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU Affero General Public License."
    )";

        inline constexpr std::string_view VERIFIER_MSG = R"(
--------------------------------------------------
Verified by XFIChecker. Please support the author:
            https://dalink.to/xenyaro                                                                                                        
--------------------------------------------------
)";

        inline constexpr std::string_view SUPPORT_URL = "https://dalink.to/xenyaro";
        inline constexpr std::string_view ONSUPPORT_LOG = "\n [*] Opening support 'XFIChecker' page in your default browser...\n";
        inline constexpr std::string_view FILE_INTACT = " [OK] File is intact. Hashes match!\n";
        inline constexpr std::string_view HASH_MISMATCH = " [FAILED] WARNING! Hash mismatch! File may be corrupted.";
        inline constexpr std::string_view OPTIONAL_MSG = "<->(optionally)";

        inline constexpr std::string_view UNMATCH = "[X] NO MATCH. The file integrity check failed for all algorithms.\n";
        inline constexpr std::string_view MATCH_FOUND = "[OK] MATCH FOUND!\n";
        inline constexpr std::string_view ALGO = "Algorithm: ";

        inline constexpr std::string_view MATCH = "[MATCH]\n";
        inline constexpr std::string_view MISMATH = "[MISMATCH]\n";
        inline constexpr std::string_view SKIPPED = "[SKIPPED]\n\n";

        inline constexpr std::string_view HASH_MSG = " Hash: 0x";
        inline constexpr std::string_view SUPPORT_MSG = " Support the project: https://dalink.to/xenyaro\n";

        inline constexpr std::string_view SUCCESS = " [SUCCESS] Provided hashes matched!\n";
        inline constexpr std::string_view WARNING = " [WARNING] Some provided hashes mismatched!\n";

        inline constexpr std::string_view INFO = "\n[INFO] No hashes provided for verification. Returning to menu...\n";
        inline constexpr std::string_view EXPECTED = "  Expected: 0x";
        inline constexpr std::string_view ACTUAL = "  Actual: 0x";
        inline constexpr std::string_view TARGET = "Target:   ";
        inline constexpr std::string_view VERIFICATION_MODE_MSG = "\n--- [Verification Mode] ---\n";
        inline constexpr std::string_view VERIFICATION_MSG = " <-> Verification Results \n";
    }

    namespace mainCLI {
        inline constexpr std::array<std::string_view, 3> hashNames = { " [FNV-1a]", " [DJB2]", " [ADLER-32]" };
        inline constexpr std::string_view FNV1A = "-fnv1a";
        inline constexpr std::string_view DJB2 = "-djb2";
        inline constexpr std::string_view ADLER32 = "-adler32";

        inline constexpr std::string_view HELPER_MSG = R"(
        XFIChecker - Interactive File Integrity Tool

        Usage:
        ./XFIChecker                   Launch interactive TUI menu
        XFIChecker[command][options]   Execute quick CLI action

        Commands:
        --calculate <filename> <-fnv1a|-djb2|-adler32>      Calculate hash for a specific file
        Available algorithms:                               -fnv1a, -djb2, -adler32

        --verify <filename> --expected <hex> Check if file matches the expected hash
        (Accepts 0x prefix or raw hex)

        -a, --about                      Show author, project and license info
        -s, --support                    Show donation link (Forward Redirection)
        -h, --help                       Show this help message
        -v, --version                    Show current version info and license info
        -cu, --check-updates             Check for available updates and versions

        Examples:
        XFIChecker --calculate filename -fnv1a  
        XFIChecker --verify filename --expected 0xA1B2C3D4F5
        )";

        inline constexpr std::string_view CLI_NOTIFICATOR = "\n [NOTE] See --help or -h for available options";
        inline constexpr std::string_view CLI_CALC_NOTIFICATOR = "Wrong specifiers | Usage: --calculate <filename> <-fnv1a|-djb2|-adler32>";
        inline constexpr std::string_view CLI_VERIFY_NOTIFICATOR = "Wrong specifiers | Usage: --verify <filename> --expected <hash>";

        inline constexpr std::string_view CLI_ABOUT = "--about";
        inline constexpr std::string_view CLI_ABOUT_S = "-a";
        inline constexpr std::string_view CLI_SUPPORT = "--support";
        inline constexpr std::string_view CLI_SUPPORT_S = "-s";
        inline constexpr std::string_view CLI_HELPER = "--help";
        inline constexpr std::string_view CLI_HELPER_S = "-h";
        inline constexpr std::string_view CLI_VERSION = "--version";
        inline constexpr std::string_view CLI_VERSION_S = "-v";
        inline constexpr std::string_view CLI_UPDATER = "--check-updates";
        inline constexpr std::string_view CLI_UPDATER_S = "-cu";
        inline constexpr std::string_view CLI_VERIFY = "--verify";
        inline constexpr std::string_view CLI_EXPECTED = "--expected";
        inline constexpr std::string_view CLI_CALCULATE = "--calculate";
    }
    namespace updater {
        // repo
        inline constexpr std::string_view SOURCE = "anonyaro/XFIChecker";
        inline constexpr std::string_view CURRENT_VERSION = "v1.0.0";
        inline constexpr std::string_view DOWNLOAD_URL_BASE = "git clone ";

        // API 
        inline constexpr std::string_view API_URL_BASE = "https://api.github.com/repos/";
        inline constexpr std::string_view API_URL_SUFFIX = "/releases/latest";
        inline constexpr std::string_view GITHUB_BASE = "https://github.com/";
        inline constexpr std::string_view RELEASE_PATH = "/releases/latest";
        inline constexpr std::string_view GIT_PREFIX = "git clone ";

        // curl params
        inline constexpr std::string_view USER_AGENT = "XFIChecker-App";
        inline constexpr std::string_view CURL_FLAGS = "-s -L -m 5";
        inline constexpr std::string_view CURL_REDIR_ERR = " 2>&1";
        inline constexpr size_t MAX_RESPONSE_PREVIEW = 76;

        // (UI)
        inline constexpr std::string_view MSG_INFO_START = "\n[CONNECTING] Starting update check...";
        //inline constexpr std::string_view MSG_INFO_RESP = "[GETTING] Response: ";
        inline constexpr std::string_view MSG_INFO_CURR = "[VERSION] Current: ";
        inline constexpr std::string_view MSG_INFO_LATE = "[VERSION] Latest:  ";

		// Status messages
        inline constexpr std::string_view MSG_INFO_NONE = "[INFO] No update needed";
        inline constexpr std::string_view MSG_INFO_LATEST = "[VERSION_CHECK] Using latest version";
		inline constexpr std::string_view MSG_CHECK_README = ".git and check README.md";

        inline constexpr std::string_view MSG_ERR_CURL = "[ERROR] Error: curl returned 0x0.";
        inline constexpr std::string_view MSG_ERR_TAG = "[ERROR] Could not find 'tag_name'. Check internet connection or repository releases.";
        inline constexpr std::string_view MSG_ERR_EXCEPT = "[ERROR] Fast update caught an exception: ";

        inline constexpr std::string_view MSG_NEW_VER = "[!] NEW VERSION AVAILABLE: ";
        inline constexpr std::string_view MSG_DOWNLOAD = "[Windows x64] Download: ";
        inline constexpr std::string_view MSG_GIT_CMD = "[Linux x86-64] Run: ";

        // Parsing keys
        inline constexpr std::string_view JSON_TAG_KEY = "\"tag_name\":";
    }
    namespace errorMsg {
        inline constexpr std::string_view UNDEFINED = "Unknown hash or undefined";
        inline constexpr std::string_view X_ERROR = " [Error occured] ";
        inline constexpr std::string_view UNKNOWN = "Unknown algorithm: ";
        inline constexpr std::string_view BROWSER_INVALID = " [!] Could not open default browser. Please visit: ";
        inline constexpr std::string_view INVALID_FORMAT = " [!] Invalid hex format.\n";
        inline constexpr std::string_view ERROR_MSG = " [ERROR] ";
        inline constexpr std::string_view EXTRA_C = "extra characters";
        inline constexpr std::string_view UNKNOWN_C = "unknown argument option(s): ";
        inline constexpr std::string_view ERROR = " [ERROR] Integrity failed!\n";
        inline constexpr std::string_view FILE_NF = "File not found: ";
    }

} // namespace xfic
