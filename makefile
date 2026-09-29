# ====================================================================
#   TEMPLATE Makefile (Auto Wildcard + Header Dependencies)
# ====================================================================

CXX       = g++

# Recursive function to find all .cpp files nested in subdirectories
rwildcard = $(foreach d,$(wildcard $(1)/*),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Collect all C++ source files automatically
SRC       = main.cpp $(call rwildcard, src, *.cpp)

# === Build Mode Selection (Default: debug) ===
MODE ?= debug

ifeq ($(MODE),release)
	MODE_DIR   = release
	MODE_FLAGS = -O3 -DNDEBUG
else
	MODE_DIR   = debug
	MODE_FLAGS = -g -O0 -DDEBUG
endif

# Output directories, object files, and header dependency trackers (.d)
OBJDIR    = obj/$(MODE_DIR)
BINDIR    = bin/$(MODE_DIR)
OBJ       = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS      = $(OBJ:.o=.d)
SRC_COUNT = $(words $(SRC))

# Flags to generate header dependency mapping files
DEPFLAGS  = -MMD -MP

# Include search path for headers inside src/
INCLUDES  = -Isrc -Isrc/lib

# === OS Detection and Dependency Mapping ===
ifeq ($(OS),Windows_NT)
	# --- Windows Settings ---
	OUT       = $(BINDIR)/engine.exe
	
	PKG_FLAGS_C := $(shell pkg-config --cflags sdl2 SDL2_image 2>nul)
	PKG_FLAGS_L := $(shell pkg-config --libs sdl2 SDL2_image 2>nul)

	ifneq ($(PKG_FLAGS_C),)
		CXXFLAGS  = $(MODE_FLAGS) $(DEPFLAGS) $(INCLUDES) $(PKG_FLAGS_C)
		LDFLAGS   = 
		LIBS      = $(PKG_FLAGS_L)
	else
		SDL_DIR  ?= C:/SDL/SDL2/src
		CXXFLAGS  = $(MODE_FLAGS) $(DEPFLAGS) $(INCLUDES) -I$(SDL_DIR)/include
		LDFLAGS   = -L$(SDL_DIR)/lib
		LIBS      = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	endif

	ifeq ($(MODE),release)
		LIBS += -mwindows
	endif

	# Uses Get-Date instead of Measure-Command so stdout isn't hidden
	TIME_CMD  = powershell -Command "$$start = Get-Date; $(MAKE) --no-print-directory build MODE=$(MODE); $$elapsed = (Get-Date) - $$start; Write-Host ('`nBuild completed in {0:N2} seconds.' -f $$elapsed.TotalSeconds) -ForegroundColor Green"
	RM_CMD    = powershell -Command "Remove-Item -Recurse -Force bin, obj -ErrorAction SilentlyContinue"
	MKDIR     = powershell -Command "New-Item -ItemType Directory -Force -Path (Split-Path -Path '$@')" >nul 2>&1
	
	# Detect and copy all DLLs from the root workspace to the BINDIR
	COPY_DLLS = @powershell -Command "if (Test-Path '*.dll') { Copy-Item -Path '*.dll' -Destination '$(BINDIR)' -Force; Write-Host 'Copied workspace DLLs to bin directory.' }"
else
	# --- Linux / macOS Settings ---
	UNAME_S := $(shell uname -s)
	OUT       = $(BINDIR)/engine
	
	CXXFLAGS  = $(MODE_FLAGS) $(DEPFLAGS) $(INCLUDES) $(shell pkg-config --cflags sdl2 SDL2_image 2>/dev/null || sdl2-config --cflags)
	LDFLAGS   = 
	LIBS      = $(shell pkg-config --libs sdl2 SDL2_image 2>/dev/null || sdl2-config --libs) -lSDL2_image
	
	TIME_CMD  = sh -c 'start=$$(date +%s); $(MAKE) --no-print-directory build MODE=$(MODE); end=$$(date +%s); echo "\nBuild completed in $$((end-start)) seconds."'
	RM_CMD    = rm -rf bin obj
	MKDIR     = mkdir -p $(dir $@)
	
	# Unix systems use rpath or global libraries, no DLL copying needed
	COPY_DLLS = 
	
	ifeq ($(UNAME_S),Darwin)
		CXXFLAGS += -I/opt/homebrew/include
		LDFLAGS  += -L/opt/homebrew/lib
	endif
endif

# ====================================================================
#   Build Targets and Rules
# ====================================================================

.PHONY: all debug release build run run-debug run-release clean trigger_build trigger_run

all: debug

# Build Targets
debug:
	@$(MAKE) --no-print-directory MODE=debug trigger_build

release:
	@$(MAKE) --no-print-directory MODE=release trigger_build

trigger_build:
	@echo "========================================"
	@echo " Starting [$(MODE)] Build: $(SRC_COUNT) files"
	@echo "========================================"
	@$(TIME_CMD)

build: $(OUT)

# Compilation & Linker Rules
$(OUT): $(OBJ)
	@echo "Linking final executable -> $(OUT)"
	@$(MKDIR)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT) $(LDFLAGS) $(LIBS)
	$(COPY_DLLS)

$(OBJDIR)/%.o: %.cpp
	@echo "Compiling -> $<"
	@$(MKDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Automatically load header dependency files (.d)
-include $(DEPS)

# Run Commands
run:
	@$(MAKE) --no-print-directory MODE=$(MODE) trigger_run

run-debug:
	@$(MAKE) --no-print-directory MODE=debug trigger_run

run-release:
	@$(MAKE) --no-print-directory MODE=release trigger_run

trigger_run: build
	@echo "Running [$(MODE)] engine..."
	@./$(OUT)

clean:
	@echo "Cleaning obj/ and bin/ folders..."
	@$(RM_CMD)
	@echo "Clean complete."