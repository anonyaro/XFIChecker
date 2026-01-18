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

#include "xfiler.h"
#include <array>
#include <fstream>
#include "xfilerrorhandler.h"
#include <filesystem>
#include "hashing.h"
#include <map>
#include <string>
#include <cstdint>
#include <vector>
#include <string_view>
#include <stdexcept>

constexpr std::string_view ERR_MSG = " [ERROR] Unknown HashType failed to proceed\n [CODE]: ";

uint64_t XFile::calculateHash(const std::string& path2file, HashType type) {
    std::ifstream file(path2file, std::ios::binary);
    if (!file) throw XFileError(path2file);

    std::vector<char> buffer(bufferSize);

    uint64_t currentHash = 0;
    switch (type) {
    case HashType::FNV1a:   currentHash = Hashing::FNV_OFFSET; break;
    case HashType::DJB2:    currentHash = Hashing::DJB2_OFFSET; break;
    case HashType::ADLER_32: currentHash = Hashing::ADLER32_OFFSET; break;
    case HashType::ENDPOINT: 
    default: throw std::invalid_argument(static_cast<std::string>(ERR_MSG) + std::to_string(static_cast<int>(type)));
    }

    while (file.read(buffer.data(), bufferSize) || file.gcount() > 0) {
        std::streamsize bytesRead = file.gcount();
        if (bytesRead <= 0) break;

        switch (type) {
        case HashType::FNV1a:
            currentHash = Hashing::FNV1a(buffer.data(), static_cast<std::size_t>(bytesRead), currentHash);
            break;
        case HashType::DJB2:
            currentHash = Hashing::DJB2(buffer.data(), static_cast<std::size_t>(bytesRead), currentHash);
            break;
        case HashType::ADLER_32:
            currentHash = Hashing::ADLER32(buffer.data(), static_cast<std::size_t>(bytesRead), static_cast<uint32_t>(currentHash));
            break;
        case HashType::ENDPOINT:
        default:
            break;
        }
    }

    return currentHash;
}

std::map<XFile::HashType, XFile::VerifyResult> XFile::verifyDataAll(
    const std::string& path2file,
    const std::array<uint64_t, static_cast<size_t>(HashType::ENDPOINT)>& expectedHashes)
{
    if (!std::filesystem::exists(path2file) || !std::filesystem::is_regular_file(path2file)) 
        throw XFileError(path2file);

    std::map<HashType, VerifyResult> results;

    for (size_t i = 0; i < expectedHashes.size(); ++i) {
        HashType type = static_cast<HashType>(i);
        uint64_t actual = calculateHash(path2file, type);

        results[type] = { actual, (actual == expectedHashes[i]) };
    }

    return results;
}