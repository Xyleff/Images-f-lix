#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>



int main(int argc, char* argv[])
{
    const int SCREEN_WIDTH =1200;
    const int SCREEN_HEIGHT = 600;

    ///////////
    // init necessary bullshit :

    SDL_Window* window;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) // change to just what you want to support
    {
        printf("SDL Init Fail: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // --------------- SETUP SDL
    // 01 Create Window
    window = SDL_CreateWindow(
        "SDL2 window Ready for Pixels",    // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x
        SDL_WINDOWPOS_UNDEFINED,           // initial y
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0 // you would add any specific stuff here, like OPENGL support
    );

    if (window == NULL)
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    // end of init necessary bullshit, fun stuff begins
    ///////////////////

    // draw a white square, then grow it every time you click on it

    // the rectangle we'll be drawing around
    SDL_Rect rect;
    rect.w = 60;
    rect.h = 60;

    // coordinates are top-left, center on screen
    rect.x = (SCREEN_WIDTH / 2) - (rect.w / 2);
    rect.y = (SCREEN_HEIGHT / 2) - (rect.h / 2);

    // by using these functions we avoid a LOT of bullshit with bit depth and the like
    Uint32 noir = SDL_MapRGB(surface->format, 0, 0, 0);


    int bleu = 255;
    int rouge = 255;
    int vert = 255;

    int sec = 10;

    int point = 0;

    

    Uint32 couleur = SDL_MapRGB(surface->format, vert, rouge, bleu);

    // draw a white box (of course move this to a function asap)
    SDL_LockSurface(surface);
    SDL_FillRect(surface, &rect, couleur);
    SDL_UnlockSurface(surface);
    SDL_UpdateWindowSurface(window);

    int quit = 0; // oh shit that's right no bools in C 
    SDL_Event event;


    
    while (!quit) // you have absolute control over the main process thread from here, PollEvent will feed you whatever happens 
    {
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                
                
                SDL_Point mousePos = { event.button.x, event.button.y };
                if (SDL_PointInRect(&mousePos, &rect))
                {

                   // SDL_LockSurface(surface);
                   // SDL_FillRect(surface, &rect, noir);
                   // SDL_UnlockSurface(surface);
                   // SDL_UpdateWindowSurface(window);
                    
                    point++;

                    printf("tu as %d points\n", point);
                    //rect.h -= 1;
                    //rect.w -= 1;
                    rect.x =  rand() % (SCREEN_WIDTH - rect.w);
                    rect.y = rand() % (SCREEN_HEIGHT - rect.h); ;
                    rouge = rand();
                    bleu = rand();
                    vert = rand();
                    couleur = SDL_MapRGB(surface->format, vert, rouge, bleu);
                    sec = 10;

                    // same as earlier, so yeah function please
                    SDL_LockSurface(surface);
                    SDL_FillRect(surface, &rect, couleur );
                    SDL_UnlockSurface(surface);
                    SDL_UpdateWindowSurface(window);

                    // grow rect for next time
                    
                }
               
                
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS; // we succeeded at quitting!
}
