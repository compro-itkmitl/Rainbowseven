#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
SDL_Surface* background_surface ;
SDL_Texture* background_texture;
SDL_Surface* start_surface ;
SDL_Texture* start_texture;
SDL_Surface* background_gamesurface;
SDL_Texture* background_gametexture;
SDL_Renderer* grenderer;
SDL_Window* window = NULL;
SDL_Surface* screensurface = NULL;
SDL_Rect start_position = {1920/2-200/2, 1080/2-100/2, 200, 100};
SDL_Texture* display;
bool game_menu = true;
bool ingame = false;
bool init(){
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            grenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (grenderer == NULL){
                printf("Error : %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}




bool loadmedia(){
    bool success = true;
    background_surface = IMG_Load("Menu.png");
    if (background_surface == NULL)
    {
        printf("load menu.png failed %s\n", IMG_GetError());
        success = false;
    }
    background_texture = SDL_CreateTextureFromSurface(grenderer, background_surface);

    start_surface = IMG_Load("start.png");
    if (start_surface == NULL)
    {
        printf("load start.png failed %s\n", IMG_GetError());
        success = false;
    }
    start_texture = SDL_CreateTextureFromSurface(grenderer, start_surface);

    background_gamesurface = IMG_Load("yeah.png");
    if (background_gamesurface == NULL)
    {
        printf("load yeah.png failed %s\n", IMG_GetError());
        success = false;
    }
    background_gametexture = SDL_CreateTextureFromSurface(grenderer, background_gamesurface);
    return success;
}

int main(int first, char* array[] ){
    if(!init()){
        printf("init failed\n");
    }
    else{
        if(!loadmedia()){
            printf("load media failed\n");
        }
        else{
            display = background_texture;
            int quit = 0;
            while (!quit){
                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT){
                        quit = 1;
                    }
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
                        display = background_gametexture;
                        game_menu = false;
                        ingame = true;
                    }
                }
                SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(grenderer);
                if(game_menu){
                    SDL_RenderCopy(grenderer, background_texture, NULL, NULL);
                    SDL_RenderCopy(grenderer, start_texture, NULL, &start_position);
                }
                else if(ingame){
                    SDL_RenderCopy(grenderer, background_gametexture, NULL, NULL);
                }
                SDL_RenderPresent(grenderer);
            }

        }
    }
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
