BUILD_DIR := build

EXE_NAME := Arkanoid
EXE := $(BUILD_DIR)/$(EXE_NAME)

# Default target.
# Build project and produce executable
exe: $(EXE)
$(EXE): $(BUILD_DIR)
	@cmake -S . -B "$(BUILD_DIR)" -DCMAKE_BUILD_TYPE=Release
	@cmake --build "$(BUILD_DIR)" --target $(EXE_NAME)

run: $(EXE)
	@"./$(EXE)"

# Create necessary directories
$(BUILD_DIR):
	@mkdir -p "$@"

# Clean rule
clean:
	@rm -rf "$(BUILD_DIR)"

.PHONY: $(EXE) run clean
