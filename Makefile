MAKE_DIR=$(PWD)
FRAMEWORKS_DIR=$(MAKE_DIR)/Frameworks
SDL2_DMG_FILEPATH=$(FRAMEWORKS_DIR)/sdl2.dmg
SDL2_MOUNTROOT=$(FRAMEWORKS_DIR)/SDL2
emcc_command=$(command -v emcc)

# Empty wasm target, depends on "index.wasm"
wasm: index.wasm

# Empty macosx target, depends on "index.app"
macos: index.app

# The "emcc" dependency ensures that the emscripten c compiler command "emcc"
# is available in the current shell from which the make command is executed.
index.wasm: index.c emcc
	emcc -g index.c -s MODULARIZE -s USE_SDL=2 -o index.mjs

# Uses conditionals in a make file. Check the manual:
# https://www.gnu.org/software/make/manual/html_node/Conditional-Example.html
# https://www.gnu.org/savannah-checkouts/gnu/make/manual/html_node/Make-
# 	Control-Functions.html
emcc:
ifndef emcc_command
	$(error emcc not found. Aborting)
endif

# The Mac OS X native app target, depends on the SDL2 Framework
index.app: index.c $(SDL2_MOUNTROOT)
	clang -g index.c -F$(SDL2_MOUNTROOT) -framework SDL2 -o index.app

# The SDL2 Framework, depends on the SDL2 DMG file (merely the mounting of it)
$(SDL2_MOUNTROOT): $(SDL2_DMG_FILEPATH)
	hdiutil attach -mountroot $(FRAMEWORKS_DIR) $(SDL2_DMG_FILEPATH)

# The SDL2 DMG file, to be downloaded using cURL from GitHub.
$(SDL2_DMG_FILEPATH):
	curl https://github.com/libsdl-org/SDL/releases/download/release-2.24.1/SDL2-2.24.1.dmg \
		-L --output $(SDL2_DMG_FILEPATH)

# Eject or unmount the SDL2 framework (mounted from the DMG file)
eject:
	if [ -d "$(SDL2_MOUNTROOT)" ]; then hdiutil detach "$(SDL2_MOUNTROOT)"; fi

# The clean target ejects the framework as well as removes all the artifacts.
clean: eject
	rm -r index.app.dSym
	rm index.mjs index.app index.wasm "$(SDL2_DMG_FILEPATH)"