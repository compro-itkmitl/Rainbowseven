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
SDL_Surface* player_stand_suface;
SDL_Texture* player_stand_texture;
SDL_Surface* player_walk1_suface;
SDL_Texture* player_walk1_texture;
SDL_Surface* player_walk2_suface;
SDL_Texture* player_walk2_texture;
SDL_Surface* player_jump_suface;
SDL_Texture* player_jump_texture;
SDL_Texture* player;
SDL_Renderer* grenderer;
SDL_Window* window = NULL;
SDL_Surface* screensurface = NULL;
SDL_Rect start_position = {1920/2-200/2, 1080/2-100/2, 200, 100};
SDL_Rect player_position = {300, 710, 80, 110};
SDL_Texture* display;
SDL_Texture* player;
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

    player_stand_suface = IMG_Load("../graphic/player_stand.png");
    if (player_stand_suface == NULL)
    {
        printf("load player_stand.png failed %s\n", IMG_GetError());
        success = false;
    }
    player_stand_texture = SDL_CreateTextureFromSurface(grenderer, player_stand_suface);

    player_walk1_suface = IMG_Load("../graphic/player_walk1.png");
    if (player_walk1_suface == NULL)
    {
        printf("load player_walk1.png failed %s\n", IMG_GetError());
        success = false;
    }
    player_walk1_texture = SDL_CreateTextureFromSurface(grenderer, player_walk1_suface);

    player_walk2_suface = IMG_Load("../graphic/player_walk2.png");
    if (player_walk2_suface == NULL)
    {
        printf("load player_walk2.png failed %s\n", IMG_GetError());
        success = false;
    }
    player_walk2_texture = SDL_CreateTextureFromSurface(grenderer, player_walk2_suface);

    player_jump_suface = IMG_Load("../graphic/player_jump.png");
    if (player_jump_suface == NULL)
    {
        printf("load player_jump.png failed %s\n", IMG_GetError());
        success = false;
    }
    player_walk2_texture = SDL_CreateTextureFromSurface(grenderer, player_walk2_suface);
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
            player = player_stand_texture;
            int quit = 0;
            while (!quit){
                int player_status = 0;
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
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
                            player = player_walk1_texture;

                            player_position.x += 10;
                    }
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a){
                            player = player_walk1_texture;
                            player_position.x -= 10;
                    }
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w){
                            player = player_jump_texture;
                            player_position.y += 20;
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
                    SDL_RenderCopy(grenderer, player, NULL, &player_position);
                    player = player_stand_texture;
                    if (player_position.x > 1600){
                        player_position.x = 100;
                    }

                }
                SDL_RenderPresent(grenderer);
            }

        }
    }
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
