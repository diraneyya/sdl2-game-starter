#include <SDL.h>
#include <emscripten.h>
#include <stdlib.h>

SDL_Surface *screen;

void drawRandomPixels() {
    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    Uint8 * pixels = screen->pixels;
    
    for (int i=0; i < 32 * 32 * 4; i++) {
        char randomByte = rand() % 255;
        pixels[i] = randomByte;
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen);
}

int main(int argc, char* argv[]) {
    
    SDL_Init(SDL_INIT_VIDEO);

    EM_ASM(
        SDL.defaults.copyOnLock = false;
        SDL.defaults.discardOnLock = true;
        SDL.defaults.opaqueFrontBuffer = false;
    );

    screen = SDL_SetVideoMode(32, 32, 32, SDL_SWSURFACE);
    
    emscripten_set_main_loop(drawRandomPixels, 0, 1);
}