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

#include <gtest/gtest.h>
#include "HashUtils/hashing.h"

// 1. FNV-1a (64-bit)
TEST(HashingLogic, FNV1a_Test) {
    const char* data = "test";
    uint64_t offset = 0xcbf29ce484222325;
    
    uint64_t result = Hashing::FNV1a(data, 4, offset);
    
    EXPECT_EQ(result, 0xf9e6e6ef197c2b25);
}

// 2. DJB2
TEST(HashingLogic, DJB2_Test) {
    const char* data = "test";
    uint64_t offset = 5381; 
    
    uint64_t result = Hashing::DJB2(data, 4, offset);
    
    EXPECT_EQ(result, 6385723493ULL); 
}

// 3. Adler-32
TEST(HashingLogic, Adler32_Test) {
    const char* data = "test";
    uint64_t offset = 1; 
    
    uint64_t result = Hashing::ADLER32(data, 4, static_cast<uint32_t>(offset));
    
    EXPECT_EQ(static_cast<uint32_t>(result), 0x045D01C1);
}

// 4. EmptyChar 
TEST(HashingLogic, EmptyInput) {
    const char* data = "";
    
// Check that the program does not crash and return the initial offsets
    EXPECT_EQ(Hashing::FNV1a(data, 0, 0xcbf29ce484222325), 0xcbf29ce484222325);
    EXPECT_EQ(Hashing::DJB2(data, 0, 5381), 5381);
    EXPECT_EQ(Hashing::ADLER32(data, 0, 1), 1);
}
