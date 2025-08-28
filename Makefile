BUILD_DIR := build
WEB_BUILD_DIR := build-web

EXE_NAME := Arkanoid
EXE := $(BUILD_DIR)/$(EXE_NAME)
WEB_EXE := $(WEB_BUILD_DIR)/$(EXE_NAME).js
WEB_HTML := web/$(EXE_NAME).html

# Default target.
# Build project and produce executable
exe: $(EXE)
$(EXE): $(BUILD_DIR)
	@cmake -S . -B "$(BUILD_DIR)" -DCMAKE_BUILD_TYPE=Release
	@cmake --build "$(BUILD_DIR)" --target $(EXE_NAME)

run: $(EXE)
	@"./$(EXE)"

# WebGL build with Emscripten
webgl: $(WEB_EXE)

$(WEB_EXE): $(WEB_BUILD_DIR)
	@emcmake cmake -S . -B "$(WEB_BUILD_DIR)" -DCMAKE_BUILD_TYPE=Release
	@cmake --build "$(WEB_BUILD_DIR)" --target $(EXE_NAME)
	@cp "$(WEB_HTML)" "$(WEB_BUILD_DIR)/index.html"

web-run: webgl
	@emrun --port 8080 "$(WEB_BUILD_DIR)"

# Create necessary directories
$(BUILD_DIR) $(WEB_BUILD_DIR):
	@mkdir -p "$@"

# Clean rule
clean:
	@rm -rf "$(BUILD_DIR)" "$(WEB_BUILD_DIR)"

.PHONY: exe $(EXE) $(WEB_EXE) run webgl web-run clean
