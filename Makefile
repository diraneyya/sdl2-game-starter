wasm:
	emcc -g index.c -s MODULARIZE -s USE_SDL=2 -o index.mjs