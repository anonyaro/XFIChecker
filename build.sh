#!/usr/bin/env bash
set -e

APP_NAME="XFIChecker"
BUILD_DIR=""
BUILD_TYPE=""
VERBOSE=""
LINK="https://github.com/anonyaro/XFIChecker"

echo "===================================="
echo "  ${APP_NAME} build & run script"
echo "===================================="
echo

# --- required tools ---
echo "[INFO] Checking required tools..."
for tool in cmake ninja; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "[ERROR] Required tool '$tool' not found"
        echo "        Please install it and try again"
        exit 1
    fi
done
echo "[DONE] All required tools found"
echo

# --- build type ---
read -r -p "Select build type ([R]elease/[D]ebug): " bt
bt=${bt:-R}
case "$bt" in
    R|r|Release|release)
        BUILD_TYPE="Release"
        BUILD_DIR="release"
        ;;
    D|d|Debug|debug)
        BUILD_TYPE="Debug"
        BUILD_DIR="debug"
        ;;
    *)
        echo "[WARNING] Unknown option, defaulting to Release"
        BUILD_TYPE="Release"
        BUILD_DIR="release"
        ;;
esac
echo "[INFO] Selected build type: $BUILD_TYPE"
echo "[INFO] Defined build dir: /$BUILD_DIR"
echo

# --- compilation output ---
read -r -p "Enable compilation process output? [y/n]: " vb
case "$vb" in
    y|Y|yes|YES)
        VERBOSE="--verbose"
        ;;
    *)
        VERBOSE=""
        ;;
esac
echo

# --- configure project ---
echo "[INFO] Configuring project ($BUILD_TYPE)..."
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -G Ninja -DBUILD_TESTING=OFF
echo "[DONE] Configuration complete"
echo

# --- build project ---
echo "[INFO] Building project..."
cmake --build "$BUILD_DIR" $VERBOSE
echo "[DONE] Build finished"
echo

# --- check binary ---
BIN_PATH="./$BUILD_DIR/$APP_NAME"
if [[ ! -f "$BIN_PATH" ]]; then
    echo "[ERROR] Binary '$BIN_PATH' not found! Check $LINK for more info"
    exit 1
fi

# --- ask before running ---
echo "[INFO] Build and compilation completed. Proceed to run"
read -r -p "Do you want to run ${APP_NAME} now? [y/n]: " answer
echo
case "$answer" in
    y|Y|yes|YES)
        echo "[INFO] Launching ${APP_NAME}..."
        cd "$BUILD_DIR"
        "./$APP_NAME"
        ;;
    *)
        echo "[INFO] Build completed. Launch skipped."
        echo "You can run it later with: $BIN_PATH"
        ;;
esac
