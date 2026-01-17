<table>
  <tr>
    <td width="256" align="center" valign="middle" style="padding: 0 !important; line-height: 0; background-color: transparent;">
      <a href="https://github.com/anonyaro/XFIChecker">
        <img 
          src="https://github.com/user-attachments/assets/e645f257-ed3f-46c2-ab80-7a304a6aed3e" 
          width="256" 
          style="display: block; width: 256px; height: auto; max-width: 100%; border: 0;"
          alt="logo"
        />
      </a>
    </td>
    <!-- Текстовая часть -->
    <td valign="middle" style="padding-left: 20px;">
      <strong style="font-size: 22px; display: block; margin-bottom: 0.5em;">
        XFIChecker v1.0.0 — Interactive File Integrity Tool
      </strong>
      <p style="margin: 0 0 1em 0;">
        High-speed integrity verification using lightweight hash algorithms.
      </p>
      <b>Key Features</b>
      <p style="margin: 0;">
        • <b>Optimized Speed:</b> Uses fast algorithms like FNV1a, DJB2, and Adler32.<br/>
        • <b>Dual Interface:</b> Full TUI interactive menu or quick CLI commands.<br/>
        • <b>Verification:</b> Easily check files against expected hex hashes.<br/>
        • <b>Resource Efficient:</b> Minimal RAM and CPU footprint.
      </p>
      <p style="margin-top: 0.5em;">
        <strong>PLEASE READ THE <a href="https://github.com/anonyaro/XFIChecker/blob/master/LICENSE">LICENSE</a> BEFORE INSTALLING AND USING XFICHECKER.</strong>
      </p>
    </td>
  </tr>
</table>

# Installation

### Windows x64
*Download and run XFIChecker.exe*

### Linux x86-64

*Download the project: ```git clone https://github.com/anonyaro/XFIChecker.git```*

*Move to the project dir: ```cd XFIChecker```*

*Finally run: ```bash build.sh``` or make it executable with +x flag and run ```./build.sh```*

*Proceed through installation script by just hitting enter it will do everything for you, make sure you have [Prerequisites](https://github.com/anonyaro/XFIChecker/blob/master/README.md#prerequisites) installed*

*Create an [issue](https://github.com/anonyaro/XFIChecker/issues/new) if you face installation problems make sure to describe an issue e.g below:*
```
Platform: your platform name
Error code: error code or log output
Error occurance file and line e.g: build.sh or !warning 55:58 core/xfiler.cpp exception ...
```
*Launch the interactive menu by running the program without arguments: ```./XFIChecker```*

# Usage
### Interactive Mode (TUI) Structure:

```
__________________________________________________________
>  __  __ _____ ___   ____ _               _             <
>  \ \/ /|  ___|_ _| / ___| |__   ___  ___| | _____ _ __ <
>   \  / | |_   | | | |   | '_ \ / _ \/ __| |/ / _ \ '__|<
>   /  \ |  _|  | | | |___| | | |  __/ (__|   <  __/ |   <
>  /_/\_\|_|   |___| \____|_| |_|\___|\___|_|\_\___|_|   <
>________________________________________________~ ~ ~ ~ <
                                            //  /   by   \
Support XFIChecker:                         \\__\anonyaro/
>https://dalink.to/xenyaro<                      \______/

[1] Calculate Hash
[2] Verify Integrity
[3] About XFIChecker
[4] Support the XFIChecker
[5] Help to see more and usage sample
[0] Exit Program
```
***Accepts numbers to proceed e.g: ```1 | 2 | 3 | 4 | 5```***  

# CLI Mode (Command Line)
### Execute actions directly using flags:

**Calculate hash:**
*```./XFIChecker --calculate <file> <-fnv1a|-djb2|-adler32>```*

**Verify file integrity:**
```./XFIChecker --verify <file> --expected <hash>```

***See ```./XFIChecker -help``` or ```./XFIChecker --h``` for detailed information***

***General flags:***

        -a, --about                      Show author, project and license info
        -s, --support                    Show donation link (Forward Redirection)
        -h, --help                       Show help message and available flags
        -v, --version                    Show current version info and license info
        -cu, --check-updates             Check for available updates and versions

# [XFIChecker is free and open-source. <br> Your support helps to keep the project alive](https://www.donationalerts.com/r/xenyaro) </br>

<a href="https://www.donationalerts.com/r/xenyaro">
<img
src="https://github.com/user-attachments/assets/9e259186-ca6b-459a-8344-252e49c7c8cd"
width="300" height="300"
alt="support"
style="display:block;"
/>
</a>

# Building from Source
*First clone the repo: ```git clone https://github.com/anonyaro/XFIChecker.git```*

*Then simply run: ```bash build.sh``` or make it executable with +x flag and run ```./build.sh```*

*For manual build follow steps below:*
```
cd XFIChecker
cmake -B build -DCMAKE_BUILD_TYPE=Release or Debug for debug build
cmake --build release or debug for debug build
```

# Prerequisites

- **Compiler**: C++17 (MSVC 2019+, GCC 8+, or Clang 7+)
- **Build System**: [CMake](https://cmake.org/) 3.15+
- **Generator**: [Ninja](https://ninja-build.org/) (recommended)


<a name="license"></a>

# License & Mandatory Attribution
### This project is licensed under the GNU Affero General Public License v3.0 (AGPLv3).

<strong> 
Section 7(b) Mandatory Notice

In accordance with Section 7(b) of the GNU AGPLv3, any work incorporating this software must preserve and display the following legal notices in its user interface:

Author: anonyaro (https://github.com/anonyaro)

Project: XFIChecker (https://github.com/anonyaro/XFIChecker)

Support: https://www.donationalerts.com/r/xenyaro

These notices, including the "Verified by XFIChecker" message and donation links, must remain visible in the TUI/CLI output, "About" dialogs, and any derivative works.

Copyright (C) 2026 anonyaro
</strong>
