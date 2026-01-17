# XFIChecker

XFIChecker is a cross-platform, lightweight, fast CLI and TUI based tool for calculating file hash and verify file hash integrity.

<table>
<tr>
<td width="256" valign="top" align="center">
  <a href="https://github.com/anonyaro/XFIChecker">
    <img 
      src="https://github.com/user-attachments/assets/7bf99ca8-a433-4c6f-abce-c1fec3f920f7"
      width="256" height="200"
      alt="logo"
      style="display:block;"
    />
  </a>
</td>
<td valign="top" style="padding-left:20px;">
  <strong style="font-size:22px; display:block; margin-bottom:0.5em;">
    XFIChecker v1.0.0 — Interactive File Integrity Tool
  </strong>
  <p style="margin:0 0 1em 0;">
    High-speed integrity verification using lightweight hash algorithms.
  </p>
  <b style="display:block; margin-bottom:0.5em;">
    Key Features
  </b>
  <p style="margin:0;">
    • <b>Optimized Speed:</b> Uses fast algorithms like FNV1a, DJB2, and Adler32.<br/>
    • <b>Dual Interface:</b> Full TUI interactive menu or quick CLI commands.<br/>
    • <b>Verification:</b> Easily check files against expected hex hashes.<br/>
    • <b>Resource Efficient:</b> Minimal RAM and CPU footprint.
  </p>
  <p style="margin-top:0.5em;">
    <strong>⚠️ PLEASE READ THE <a href="https://github.com/anonyaro/XFIChecker/blob/master/LICENSE">LICENSE</a> BEFORE INSTALLING AND USING XFICHECKER.</strong>
  </p>
</td>
</tr>
</table>

# Usage

### 🖥️ Interactive Mode (TUI)
Launch the interactive menu by running the program without arguments:
```bash
./XFIChecker

Menu Structure:

[1] Calculate Hash

[2] Verify Integrity

[3] About XFIChecker

[4] Support the XFIChecker

[5] Help & Usage Samples

⚡ CLI Mode (Command Line)

Execute actions directly using flags:

Calculate hash:
XFIChecker --calculate <file> <algo>
Available algorithms: -fnv1a, -djb2, -adler32
Example: XFIChecker --calculate filename -fnv1a

Verify file integrity:
XFIChecker --verify <file> --expected <hex>
(Accepts 0x prefix or raw hex)
Example: XFIChecker --verify filename --expected 0xA1B2C3D4F5

General flags:

-a, --about: Show author, project and license info.

-s, --support: Show donation link.

-h, --help: Show help message.

Support the Project

XFIChecker is free and open-source. Your support helps keep the project alive!

Donate via DonationAlerts

<a href="https://www.donationalerts.com/r/xenyaro">
<img
src="https://github.com/user-attachments/assets/c89418ad-5a77-4cca-961f-bd8613ad0466"
width="300" height="200"
alt="support"
style="display:block;"
/>
</a>

Installation
Windows x64

Download the latest release from Releases.

Unzip the archive and run XFIChecker.exe.

Linux x86-64

Download the binary.

Make it executable: chmod +x ./XFIChecker

Run it: ./XFIChecker

Building from Source

Requirements:

C++20 compatible compiler (MSVC 2022, GCC 11+, or Clang 13+)

CMake 3.20+

code
Bash
download
content_copy
expand_less
git clone https://github.com/anonyaro/XFIChecker.git
cd XFIChecker
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
<a name="license"></a>License & Mandatory Attribution

This project is licensed under the GNU Affero General Public License v3.0 (AGPLv3).

🔴 Section 7(b) Mandatory Notice

In accordance with Section 7(b) of the GNU AGPLv3, any work incorporating this software must preserve and display the following legal notices in its user interface:

Author: anonyaro (https://github.com/anonyaro)

Project: XFIChecker (https://github.com/anonyaro/XFIChecker)

Support: https://www.donationalerts.com/r/xenyaro

These notices, including the "Verified by XFIChecker" message and donation links, must remain visible in the TUI/CLI output, "About" dialogs, and any derivative works.

Copyright (C) 2026 anonyaro
