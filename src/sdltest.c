#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdlib.h>

SDL_Surface *screen;

void drawRandomPixels() {
    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    Uint8 * pixels = screen->pixels;
    
    for (int i=0; i < 1048576; i++) {
        char randomByte = rand() % 255;
        pixels[i] = randomByte;
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen);
}

void sdl_proc() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_KEYDOWN: /* any key to stop */
    case SDL_QUIT: /* window close */
        SDL_Quit();
	exit(0);
    default:
	drawRandomPixels();
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(512, 512, 32, SDL_SWSURFACE);
#ifdef __EMSCRIPTEN__ 
    emscripten_set_main_loop(sdl_proc, 60, 1);
#else
    while(1) {
	    sdl_proc();
	    SDL_Delay(16);
    }
#endif
}

