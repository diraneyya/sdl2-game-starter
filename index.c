#include <SDL2/SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdlib.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;

void drawRandomPixels() {
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    Uint8 * pixels = surface->pixels;
    
    for (int i=0; i < 32 * 32 * 4; i++) {
        char randomByte = rand() % 255;
        pixels[i] = randomByte;
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(screenTexture);

}

#define FPS 30

int main(int argc, char* argv[]) {
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer, 32, 32);

    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(drawRandomPixels, FPS, 1);
#else
    while (1) {
        // Variable to store GUI events
        SDL_Event event;

        Uint64 timeout = SDL_GetTicks64() + (Uint8)(1000.0f / FPS);
        drawRandomPixels();
        
        if (SDL_WaitEventTimeout(&event, timeout - SDL_GetTicks64()))
        {
            if (event.type == SDL_QUIT)
                // Break out of the loop on quit
                break;
        }
    }

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
#endif
}
