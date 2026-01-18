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

#ifndef HASHING_H
#define HASHING_H

#include <cstdint>
#include <cstddef> //for std::size_t since size_t is used in function signatures and some compilers may require this header for size_t definition

namespace Hashing 
{
    static constexpr uint64_t FNV_OFFSET = 14695981039346656037ULL;
    static constexpr uint64_t FNV_PRIME = 1099511628211ULL;

    static constexpr uint64_t DJB2_OFFSET = 5381;
    static constexpr uint32_t ADLER32_OFFSET = 1;
    static constexpr uint32_t MOD_ADLER = 65521;

    uint64_t FNV1a(const char* data, std::size_t size, uint64_t hash = FNV_OFFSET);
    uint64_t DJB2(const char* data, std::size_t size, uint64_t hash = DJB2_OFFSET);
    uint32_t ADLER32(const char* data, std::size_t size, uint32_t hash = ADLER32_OFFSET);

}

#endif