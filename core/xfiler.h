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

#ifndef XFILE_H
#define XFILE_H

#include <string>
#include <map>
#include <cstdint>
#include <array>

class XFile final
{
public:
	enum class HashType : size_t {
		FNV1a,
		DJB2,
		ADLER_32,
		ENDPOINT
	};

struct VerifyResult {
	uint64_t actualValue;
	bool isMatching;
};
	XFile() = default;
	uint64_t calculateHash(const std::string& path2file, HashType type = HashType::FNV1a);
	std::map<HashType, VerifyResult> verifyDataAll(
		const std::string& path2file,
		const std::array<uint64_t, static_cast<size_t>(HashType::ENDPOINT)>& expectedHashes
	);
	~XFile() = default;
	
private:
	std::map<HashType, bool> results;
	static constexpr std::size_t bufferSize = 4096;
};

#endif