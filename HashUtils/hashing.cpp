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

#include "hashing.h"
#include <cstdint>

namespace Hashing {

    uint64_t FNV1a(const char* data, std::size_t size, uint64_t hash) {
        for (std::size_t i = 0; i < size; ++i) {
            hash ^= static_cast<unsigned char>(data[i]);
            hash *= FNV_PRIME;
        }
        return hash;
    }

    uint64_t DJB2(const char* data, std::size_t size, uint64_t hash) {
        for (std::size_t i = 0; i < size; ++i) {
            // avoid intermediate overflow 
            hash = hash * 33ULL + static_cast<unsigned char>(data[i]);
        }
        return hash;
    }

    uint32_t ADLER32(const char* data, std::size_t size, uint32_t hash) {
        // wider temps to avoid intermediate overflow before mod reduction
        uint64_t a = static_cast<uint64_t>(hash & 0xFFFF);
        uint64_t b = static_cast<uint64_t>(hash >> 16);
        for (std::size_t i = 0; i < size; ++i) {
            a = (a + static_cast<unsigned char>(data[i])) % MOD_ADLER;
            b = (b + a) % MOD_ADLER;
        }
        return static_cast<uint32_t>((b << 16) | a);
    }
}
