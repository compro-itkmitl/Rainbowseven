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
SDL_Surface* player_animation_surface;
SDL_Texture* player_animation_texture;
SDL_Surface* box1_surface;
SDL_Texture* box1_texture;
SDL_Surface* zombieattack_surface;
SDL_Texture* zombieattack_texture;
SDL_Surface* zombie_surface;
SDL_Texture* zombie_texture;
SDL_Texture* player;
SDL_Renderer* grenderer;
SDL_Window* window = NULL;
SDL_Surface* screensurface = NULL;
SDL_Rect start_position = {1920/2-200/2, 1080/2-100/2, 200, 100};
SDL_Rect player_position = {670, 370, 90, 140};
SDL_Rect zombie_position = {1300, 570, 90, 140};
SDL_Rect zombie_position1 = {1900, 570, 90, 140};
SDL_Rect zombie_position2 = {1200, 570, 90, 140};
SDL_Rect zombie_position3 = {2150, 570, 90, 140};
SDL_Rect zombie_position4 = {2500, 570, 90, 140};
SDL_Rect box1 = {720, 380, 200, 100};
SDL_Rect box2 = {930, 260, 300, 100};
SDL_Rect box3 = {1080, 120, 310, 100};
SDL_Rect player_animation[13];
SDL_Rect zombie_animation[13];
SDL_Rect zombie_attack_animation[9];
SDL_Texture* zombie;
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
        window = SDL_CreateWindow( "rb7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

void setanimation(){
    player_animation[0].x = 0;
    player_animation[0].y = 0;
    player_animation[0].w = 160;
    player_animation[0].h = 250;
    player_animation[1].x = 161;
    player_animation[1].y = 0;
    player_animation[1].w = 160;
    player_animation[1].h = 250;
    player_animation[2].x = 321;
    player_animation[2].y = 0;
    player_animation[2].w = 160;
    player_animation[2].h = 250;
    player_animation[3].x = 480;
    player_animation[3].y = 0;
    player_animation[3].w = 160;
    player_animation[3].h = 250;
    player_animation[4].x = 641;
    player_animation[4].y = 0;
    player_animation[4].w = 160;
    player_animation[4].h = 250;

    player_animation[5].x = 801;
    player_animation[5].y = 0;
    player_animation[5].w = 160;
    player_animation[5].h = 250;
    player_animation[6].x = 961;
    player_animation[6].y = 0;
    player_animation[6].w = 160;
    player_animation[6].h = 250;
    player_animation[7].x = 1121;
    player_animation[7].y = 0;
    player_animation[7].w = 160;
    player_animation[7].h = 250;
    player_animation[8].x = 1281;
    player_animation[8].y = 0;
    player_animation[8].w = 160;
    player_animation[8].h = 250;
    player_animation[9].x = 1441;
    player_animation[9].y = 0;
    player_animation[9].w = 160;
    player_animation[9].h = 250;
    player_animation[10].x = 1601;
    player_animation[10].y = 0;
    player_animation[10].w = 160;
    player_animation[10].h = 250;
    player_animation[11].x = 1761;
    player_animation[11].y = 0;
    player_animation[11].w = 160;
    player_animation[11].h = 250;
    player_animation[12].x = 1961;
    player_animation[12].y = 0;
    player_animation[12].w = 160;
    player_animation[12].h = 250;


    zombie_animation[0].x = 0;
    zombie_animation[0].y = 0;
    zombie_animation[0].w = 220;
    zombie_animation[0].h = 350;

    zombie_animation[1].x = 257;
    zombie_animation[1].y = 0;
    zombie_animation[1].w = 220;
    zombie_animation[1].h = 350;

    zombie_animation[2].x = 550;
    zombie_animation[2].y = 0;
    zombie_animation[2].w = 220;
    zombie_animation[2].h = 350;

    zombie_animation[3].x = 845;
    zombie_animation[3].y = 0;
    zombie_animation[3].w = 220;
    zombie_animation[3].h = 350;

    zombie_animation[4].x = 1130;
    zombie_animation[4].y = 0;
    zombie_animation[4].w = 220;
    zombie_animation[4].h = 350;

    zombie_animation[5].x = 1415;
    zombie_animation[5].y = 0;
    zombie_animation[5].w = 220;
    zombie_animation[5].h = 350;

    zombie_animation[6].x = 1700;
    zombie_animation[6].y = 0;
    zombie_animation[6].w = 220;
    zombie_animation[6].h = 350;

    zombie_animation[7].x = 1935;
    zombie_animation[7].y = 0;
    zombie_animation[7].w = 220;
    zombie_animation[7].h = 350;

    zombie_animation[8].x = 2470;
    zombie_animation[8].y = 0;
    zombie_animation[8].w = 220;
    zombie_animation[8].h = 350;

    zombie_animation[9].x = 2555;
    zombie_animation[9].y = 0;
    zombie_animation[9].w = 220;
    zombie_animation[9].h = 350;

    zombie_attack_animation[0].x = 0;
    zombie_attack_animation[0].y = 0;
    zombie_attack_animation[0].w = 220;
    zombie_attack_animation[0].h = 350;

    zombie_attack_animation[1].x = 257;
    zombie_attack_animation[1].y = 0;
    zombie_attack_animation[1].w = 220;
    zombie_attack_animation[1].h = 350;

    zombie_attack_animation[2].x = 550;
    zombie_attack_animation[2].y = 0;
    zombie_attack_animation[2].w = 220;
    zombie_attack_animation[2].h = 350;

        zombie_attack_animation[3].x = 835;
    zombie_attack_animation[3].y = 0;
    zombie_attack_animation[3].w = 220;
    zombie_attack_animation[3].h = 350;

        zombie_attack_animation[4].x = 1160;
    zombie_attack_animation[4].y = 0;
    zombie_attack_animation[4].w = 220;
    zombie_attack_animation[4].h = 350;

        zombie_attack_animation[5].x = 1470;
    zombie_attack_animation[5].y = 0;
    zombie_attack_animation[5].w = 220;
    zombie_attack_animation[5].h = 350;

        zombie_attack_animation[6].x = 1770;
    zombie_attack_animation[6].y = 0;
    zombie_attack_animation[6].w = 220;
    zombie_attack_animation[6].h = 350;

        zombie_attack_animation[7].x = 2050;
    zombie_attack_animation[7].y = 0;
    zombie_attack_animation[7].w = 220;
    zombie_attack_animation[7].h = 350;
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

    background_gamesurface = IMG_Load("../graphic/bg.png");
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

    player_animation_surface = IMG_Load("../graphic/santa.png");
    if (player_jump_suface == NULL)
    {
        printf("load santa.png failed %s\n", IMG_GetError());
        success = false;
    }

    player_animation_texture = SDL_CreateTextureFromSurface(grenderer, player_animation_surface);

    box1_surface = IMG_Load("../graphic/block.png");
    if (box1_surface == NULL)
    {
        printf("load block.png failed %s\n", IMG_GetError());
        success = false;
    }

    box1_texture = SDL_CreateTextureFromSurface(grenderer, box1_surface);

    zombie_surface = IMG_Load("../graphic/zombie_walk.png");
    if (zombie_surface == NULL)
    {
        printf("load zombie.png failed %s\n", IMG_GetError());
        success = false;
    }

    zombie_texture = SDL_CreateTextureFromSurface(grenderer, zombie_surface);

    zombieattack_surface = IMG_Load("../graphic/zombie_attack.png");
    if (zombieattack_surface == NULL)
    {
        printf("load zombieattack.png failed %s\n", IMG_GetError());
        success = false;
    }

    zombieattack_texture = SDL_CreateTextureFromSurface(grenderer, zombieattack_surface);
    setanimation();
    return success;
}


bool checkCollision( SDL_Rect a, SDL_Rect b ){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }
    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
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

            bool check_jump = false, zombie1 = 1;
            bool zombie_status1 = 0,zombie_status2 = 0, zombie_status3 = 0,zombie_status4 = 0, zombie_status5 = 0;
            int time,ground = 570;
            float gravity = 0.135
             ,speed;
            display = background_texture;
            int animation_player = 0, animation_zombie = 0;
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
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
                        animation_player++;
                        player_position.x+=6;
                    }

                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a){
                        animation_player++;
                        player_position.x -= 3;

                    }

                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w && check_jump == false){
                        speed = -7;
                        check_jump = true;
                    }


                }

                SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(grenderer);
                if(game_menu){
                    SDL_RenderCopy(grenderer, background_texture, NULL, NULL);
                    SDL_RenderCopy(grenderer, start_texture, NULL, &start_position);
                }
                else if(ingame){
                    time++;
                    SDL_RenderCopy(grenderer, background_gametexture, NULL, NULL);
                    SDL_RenderCopy(grenderer, player_animation_texture, &player_animation[animation_player / 3], &player_position);
                    animation_zombie++;
                    speed += gravity;
                    player_position.y += speed;

                    if (animation_player/3 > 11)
                    {
                        animation_player = 0;
                    }
                    if (zombie_status1){
                        if (animation_zombie/15 > 8){
                            animation_zombie = 0;
                        }
                    }
                    else{
                        if (animation_zombie/15 > 7){
                            animation_zombie = 0;
                        }
                    }

                    if (zombie_status2){
                        if (animation_zombie/15 > 8){
                            animation_zombie = 0;
                        }
                    }
                    else{
                        if (animation_zombie/15 > 7){
                            animation_zombie = 0;
                        }
                    }
                    if (checkCollision( box1, player_position )&& speed > 0.999996){
                            if (player_position.y > box1.y){
                                player_position.y = box1.y;
                                speed = 1;
                                check_jump = false;
                            }

                    }

                    if (checkCollision( box3, player_position )&& speed > 0.999996){
                            if (player_position.y > box3.y){
                                player_position.y = box3.y;
                                speed = 1;
                                check_jump = false;
                            }

                    }
                    if (!checkCollision( zombie_position, player_position )){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position.x -= 1.1;
                        zombie = zombie_texture;
                        zombie_status1 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/15], &zombie_position);


                    }
                    else{
                        zombie = zombieattack_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie/15], &zombie_position);
                        zombie_status1 = 0;
                    }

                    if (!checkCollision( zombie_position1, player_position )){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position1.x -= 1.5;
                        zombie = zombie_texture;
                        zombie_status2 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/17], &zombie_position1);


                    }
                    else{
                        zombie = zombieattack_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie/17], &zombie_position1);
                        zombie_status2 = 0;
                    }

                    if (!checkCollision( zombie_position2, player_position )){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position2.x -= 2.5;
                        zombie = zombie_texture;
                        zombie_status3 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/17], &zombie_position2);


                    }
                    else{
                        zombie = zombieattack_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie/17], &zombie_position2);
                        zombie_status3 = 0;
                    }

                    if (!checkCollision( zombie_position3, player_position )){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position3.x -= 4;
                        zombie = zombie_texture;
                        zombie_status3 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/19], &zombie_position3);


                    }
                    else{
                        zombie = zombieattack_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie/19], &zombie_position3);
                        zombie_status3 = 0;
                    }

                    if (!checkCollision( zombie_position4, player_position )){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position4.x -= 2.5;
                        zombie = zombie_texture;
                        zombie_status3 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/17], &zombie_position4);


                    }
                    else{
                        zombie = zombieattack_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie/17], &zombie_position4);
                        zombie_status3 = 0;
                    }






                    if (checkCollision( box2, player_position )&& speed > 0.999996){
                            if (player_position.y > box2.y){
                                player_position.y = box2.y;
                                speed = 1;
                                check_jump = false;
                            }

                    }
                    if (player_position.x > 1600){
                        player_position.x = 100;
                    }
                    if (zombie_position.x < 0){
                        zombie_position.x = 1800;
                    }

                    if (zombie_position1.x < 0){
                        zombie_position1.x = 1800;
                    }
                    if (zombie_position2.x < 0){

                        zombie_position2.x = 1800;
                    }

                    if (zombie_position3.x < 0){
                        zombie_position3.x = 1800;
                    }

                    if (zombie_position4.x < 0){
                        zombie_position4.x = 1800;
                    }
                    if (player_position.y > 570){
                        check_jump = false;
                        player_position.y = 570;
                    }
                    if (zombie1 == 1){
                        zombie_position1.x = 2500;
                        zombie_position1.y = 570;
                        SDL_RenderCopy(grenderer, zombie_texture, &zombie_animation[animation_zombie/15], &zombie_position1);
                        zombie1 = 0;
                    }
                    if (time > 90){
                        animation_player = 0;
                        time = 0;
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
