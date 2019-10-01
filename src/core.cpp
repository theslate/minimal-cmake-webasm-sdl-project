#include <SDL2/SDL.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cstdlib>

EM_JS(int, canvas_get_width, (), {
  return window.innerWidth;
});

EM_JS(int, canvas_get_height, (), {
  return window.innerHeight;
});

struct context
{
    SDL_Renderer *renderer;
    int iteration;
};

void mainloop(void *arg)
{
    context *ctx = static_cast<context*>(arg);
    SDL_Renderer *renderer = ctx->renderer;
    
    // example: draw a moving rectangle
    
    // red background
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    // moving blue rectangle
    SDL_Rect r;
    r.x = ctx->iteration % canvas_get_width();
    r.y = 50;
    r.w = 50;
    r.h = 50;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
    SDL_RenderFillRect(renderer, &r );

    SDL_RenderPresent(renderer);

    ctx->iteration++;
}

int emscWindowSizeChanged(int whoKnows, const EmscriptenUiEvent* event, void *arg)
{
    SDL_Window *window = static_cast<SDL_Window*>(arg);

    SDL_SetWindowSize(window, canvas_get_width(), canvas_get_height());
}

int main()
{   
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(canvas_get_width(), canvas_get_height(), 0, &window, &renderer);

    context ctx;
    ctx.renderer = renderer;
    ctx.iteration = 0;

    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)
    
    emscripten_set_resize_callback(nullptr, window, false, emscWindowSizeChanged); 
    emscripten_set_main_loop_arg(mainloop, &ctx, fps, simulate_infinite_loop);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
