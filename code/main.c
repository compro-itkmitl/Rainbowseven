#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL_mixer.h>


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
SDL_Surface* bl_surface;
SDL_Texture* bl_texture;
SDL_Surface* zombie_die_surface;
SDL_Texture* zombie_die_texture;
SDL_Surface* airdrop_surface;
SDL_Texture* airdrop_texture;
SDL_Surface* boss_surface;
SDL_Texture* boss_texture;
SDL_Surface* santagun_surface;
SDL_Texture* santagun_texture;
SDL_Texture* player;
SDL_Renderer* grenderer;
SDL_Surface* santabar_surface;
SDL_Texture* santabar_texture;
SDL_Surface* zombi_surface;
SDL_Texture* zombi_texture;
SDL_Surface* gameover_surface;
SDL_Texture* gameover_texture;
SDL_Surface* gamewinner_surface;
SDL_Texture* gamewinner_texture;
SDL_Surface* healtsanta1_surface;
SDL_Texture* healtsanta1_texture;
SDL_Surface* healtsanta2_surface;
SDL_Texture* healtsanta2_texture;
SDL_Surface* healtsanta3_surface;
SDL_Texture* healtsanta3_texture;
SDL_Surface* healtsanta4_surface;
SDL_Texture* healtsanta4_texture;
SDL_Surface* healtsanta5_surface;
SDL_Texture* healtsanta5_texture;
SDL_Surface* healtsanta6_surface;
SDL_Texture* healtsanta6_texture;

SDL_Surface* healtzombi1_surface;
SDL_Texture* healtzombi1_texture;
SDL_Surface* healtzombi2_surface;
SDL_Texture* healtzombi2_texture;
SDL_Surface* healtzombi3_surface;
SDL_Texture* healtzombi3_texture;
SDL_Surface* healtzombi4_surface;
SDL_Texture* healtzombi4_texture;
SDL_Surface* healtzombi5_surface;
SDL_Texture* healtzombi5_texture;
SDL_Surface* healtzombi6_surface;
SDL_Texture* healtzombi6_texture;

SDL_Window* window = NULL;
SDL_Surface* screensurface = NULL;
SDL_Rect healtsanta1_position = {390, 150,400, 40};
SDL_Rect healtsanta2_position = {390, 150,400, 40};
SDL_Rect healtsanta3_position = {390, 150,400, 40};
SDL_Rect healtsanta4_position = {390, 150,400, 40};
SDL_Rect healtsanta5_position = {390, 150,400, 40};
SDL_Rect healtsanta6_position = {390, 150,400, 40};

SDL_Surface* bl_boss_surface;
SDL_Texture* bl_boss_texture;

SDL_Rect healtzombi1_position = {1110, 150, 400, 40};
SDL_Rect healtzombi2_position = {1110, 150, 400, 40};
SDL_Rect healtzombi3_position = {1110, 150, 400, 40};
SDL_Rect healtzombi4_position = {1110, 150, 400, 40};
SDL_Rect healtzombi5_position = {1110, 150, 400, 40};
SDL_Rect healtzombi6_position = {1110, 150, 400, 40};
SDL_Rect santabar_position = {210,130, 300, 300};
SDL_Rect zombi_position = {1510, 105, 300, 300};
SDL_Rect start_position = {1920/2-200/2, 1080/2-100/2, 200, 100};
SDL_Rect boss_position = {1350, 165, 370, 550};
SDL_Rect player_position = {200, 570, 90, 140};
SDL_Rect zombie_position = {1300, 570, 90, 140};
SDL_Rect zombie_position1 = {1900, 570, 90, 140};
SDL_Rect zombie_position2 = {1200, 570, 90, 140};
SDL_Rect zombie_position3 = {2150, 570, 90, 140};
SDL_Rect zombie_position4 = {2500, 570, 90, 140};
SDL_Rect zombie_test = {1300, 570, 110, 140};
SDL_Rect player1_position = {200, 510, 150, 190};
SDL_Rect box1 = {720, 380, 200, 100};
SDL_Rect box2 = {930, 260, 300, 100};
SDL_Rect airdrop = {1000,300, 130, 80};
SDL_Rect box3 = {1080, 120, 310, 100};
SDL_Rect bl_animation[2];
SDL_Rect bl_boss_animation[2];
SDL_Rect gun_animation[15];
SDL_Rect player_animation[13];
SDL_Rect boss_animation[15];
SDL_Rect zombie_animation[13];
SDL_Rect zombie_die[20];
SDL_Rect zombie_attack_animation[9];
SDL_Texture* zombie;
SDL_Rect bl_position = {99999, 500, 30, 30};
SDL_Rect bl_position1 = {99999, 500, 30, 30};
SDL_Rect bl_position2 = {99999, 500, 30, 30};
SDL_Rect bl_position3 = {99999, 500, 30, 30};
SDL_Rect bl_position4 = {99999, 500, 30, 30};
SDL_Rect bl_boss1 = {1200, 330, 50, 50};
SDL_Rect bl_boss2 = {1000, 450, 50, 50};
SDL_Rect bl_boss3 = {1000, 500, 50, 50};
SDL_Rect bl_boss4 = {1000, 500, 50, 50};
SDL_Rect bl_boss5 = {1000, 500, 30, 30};
int animation_zombie_attack[5] = {0,0,0,0,0};
SDL_Texture* display;
SDL_Texture* player;
Mix_Music *music = NULL;
Mix_Chunk *shoot_sound = NULL;
Mix_Chunk *walk = NULL;
Mix_Chunk *hit = NULL;
int shoot = 0;
int counthealt = 0;
int counthealt2 = 0;
bool game_menu = true;
bool ingame = false;
bool alive[5] = {true,true,true,true,true};
int check_bullet[5] = {0,0,0,0,0};
int animation_zombie_die[5] = {0,0,0,0,0};
bool gameover = false;


bool init(){
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
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
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
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

    boss_animation[0].x = 0;
    boss_animation[0].y = 0;
    boss_animation[0].w = 420;
    boss_animation[0].h = 750;

    boss_animation[1].x = 510;
    boss_animation[1].y = 0;
    boss_animation[1].w = 420;
    boss_animation[1].h = 750;

    boss_animation[2].x = 1020;
    boss_animation[2].y = 0;
    boss_animation[2].w = 420;
    boss_animation[2].h = 750;

    boss_animation[3].x = 1530;
    boss_animation[3].y = 0;
    boss_animation[3].w = 420;
    boss_animation[3].h = 750;

    boss_animation[4].x = 2040;
    boss_animation[4].y = 0;
    boss_animation[4].w = 420;
    boss_animation[4].h = 750;

    boss_animation[5].x = 2550;
    boss_animation[5].y = 0;
    boss_animation[5].w = 420;
    boss_animation[5].h = 750;

    boss_animation[6].x = 3060;
    boss_animation[6].y = 0;
    boss_animation[6].w = 420;
    boss_animation[6].h = 750;

    boss_animation[7].x = 3550;
    boss_animation[7].y = 0;
    boss_animation[7].w = 420;
    boss_animation[7].h = 750;

    boss_animation[8].x = 4060;
    boss_animation[8].y = 0;
    boss_animation[8].w = 420;
    boss_animation[8].h = 750;

    boss_animation[9].x = 4550;
    boss_animation[9].y = 0;
    boss_animation[9].w = 420;
    boss_animation[9].h = 750;

    boss_animation[10].x = 5050;
    boss_animation[10].y = 0;
    boss_animation[10].w = 420;
    boss_animation[10].h = 750;

    boss_animation[11].x = 5550;
    boss_animation[11].y = 0;
    boss_animation[11].w = 420;
    boss_animation[11].h = 750;

    boss_animation[12].x = 6050;
    boss_animation[12].y = 0;
    boss_animation[12].w = 420;
    boss_animation[12].h = 750;

    boss_animation[13].x = 6550;
    boss_animation[13].y = 0;
    boss_animation[13].w = 420;
    boss_animation[13].h = 750;

    boss_animation[14].x = 7070;
    boss_animation[14].y = 0;
    boss_animation[14].w = 420;
    boss_animation[14].h = 750;

    gun_animation[0].x = 0;
    gun_animation[0].y = 0;
    gun_animation[0].w = 280;
    gun_animation[0].h = 320;

    gun_animation[1].x = 290;
    gun_animation[1].y = 0;
    gun_animation[1].w = 280;
    gun_animation[1].h = 320;



    gun_animation[2].x = 580;
    gun_animation[2].y = 0;
    gun_animation[2].w = 280;
    gun_animation[2].h = 320;



    gun_animation[3].x = 870;
    gun_animation[3].y = 0;
    gun_animation[3].w = 280;
    gun_animation[3].h = 320;


    gun_animation[4].x = 1160;
    gun_animation[4].y = 0;
    gun_animation[4].w = 280;
    gun_animation[4].h = 320;



    gun_animation[5].x = 1450;
    gun_animation[5].y = 0;
    gun_animation[5].w = 280;
    gun_animation[5].h = 320;


    gun_animation[6].x = 1745;
    gun_animation[6].y = 0;
    gun_animation[6].w = 280;
    gun_animation[6].h = 320;



    gun_animation[7].x = 2040;
    gun_animation[7].y = 0;
    gun_animation[7].w = 280;
    gun_animation[7].h = 320;



    gun_animation[8].x = 2330;
    gun_animation[8].y = 0;
    gun_animation[8].w = 280;
    gun_animation[8].h = 320;

    gun_animation[9].x = 2610;
    gun_animation[9].y = 0;
    gun_animation[9].w = 280;
    gun_animation[9].h = 320;

        gun_animation[10].x = 2930;
    gun_animation[10].y = 0;
    gun_animation[10].w = 280;
    gun_animation[10].h = 320;

        gun_animation[11].x = 3210;
    gun_animation[11].y = 0;
    gun_animation[11].w = 280;
    gun_animation[11].h = 320;

        gun_animation[12].x = 3500;
    gun_animation[12].y = 0;
    gun_animation[12].w = 280;
    gun_animation[12].h = 320;

        gun_animation[13].x = 3800;
    gun_animation[13].y = 0;
    gun_animation[13].w = 280;
    gun_animation[13].h = 320;

        gun_animation[14].x = 4060;
    gun_animation[14].y = 0;
    gun_animation[14].w = 280;
    gun_animation[14].h = 320;

    zombie_die[0].x = 0;
    zombie_die[0].y = 0;
    zombie_die[0].w = 290;
    zombie_die[0].h = 400;

    zombie_die[1].x = 325;
    zombie_die[1].y = 0;
    zombie_die[1].w = 290;
    zombie_die[1].h = 400;

    zombie_die[2].x = 650;
    zombie_die[2].y = 0;
    zombie_die[2].w = 290;
    zombie_die[2].h = 400;

    zombie_die[3].x = 975;
    zombie_die[3].y = 0;
    zombie_die[3].w = 290;
    zombie_die[3].h = 380;

    zombie_die[4].x = 1240;
    zombie_die[4].y = 0;
    zombie_die[4].w = 290;
    zombie_die[4].h = 380;

    zombie_die[5].x = 1500;
    zombie_die[5].y = 0;
    zombie_die[5].w = 290;
    zombie_die[5].h = 380;

    zombie_die[6].x = 1780;
    zombie_die[6].y = 0;
    zombie_die[6].w = 290;
    zombie_die[6].h = 380;

    zombie_die[7].x = 2080;
    zombie_die[7].y = 0;
    zombie_die[7].w = 300;
    zombie_die[7].h = 380;

    zombie_die[8].x = 2380;
    zombie_die[8].y = 0;
    zombie_die[8].w = 390;
    zombie_die[8].h = 380;

    zombie_die[9].x = 2785;
    zombie_die[9].y = 0;
    zombie_die[9].w = 390;
    zombie_die[9].h = 380;

    zombie_die[10].x = 3190;
    zombie_die[10].y = 0;
    zombie_die[10].w = 390;
    zombie_die[10].h = 380;

    zombie_die[11].x = 3590;
    zombie_die[11].y = 0;
    zombie_die[11].w = 390;
    zombie_die[11].h = 380;

    zombie_die[12].x = 3985;
    zombie_die[12].y = 0;
    zombie_die[12].w = 390;
    zombie_die[12].h = 380;

    bl_animation[0].x = 0;
    bl_animation[0].y = 0;
    bl_animation[0].w = 100;
    bl_animation[0].h = 100;

    bl_animation[1].x = 200;
    bl_animation[1].y = 0;
    bl_animation[1].w = 100;
    bl_animation[1].h = 100;

    bl_boss_animation[0].x = 0;
    bl_boss_animation[0].y = 0;
    bl_boss_animation[0].w = 150;
    bl_boss_animation[0].h = 100;

    bl_boss_animation[1].x = 200;
    bl_boss_animation[1].y = 0;
    bl_boss_animation[1].w = 150;
    bl_boss_animation[1].h = 100;

}
int bullet(SDL_Rect a){
    SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position);
    while (a.x < 1600){
        SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &a);
        a.x += 8;
        return a.x;
    }

}

bool loadmedia(){
    bool success = true;

    background_surface = IMG_Load("../graphic/menu.png");
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


    player_animation_surface = IMG_Load("../graphic/santa.png");
    if (player_animation_surface == NULL)
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

    airdrop_surface = IMG_Load("../graphic/box.png");
    if (airdrop_surface == NULL)
    {
        printf("load box.png failed %s\n", IMG_GetError());
        success = false;
    }

    airdrop_texture = SDL_CreateTextureFromSurface(grenderer, airdrop_surface);

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


    boss_surface = IMG_Load("../graphic/boss.png");
    if (boss_surface == NULL)
    {
        printf("load boss.png failed %s\n", IMG_GetError());
        success = false;
    }
    boss_texture = SDL_CreateTextureFromSurface(grenderer, boss_surface);

    santagun_surface = IMG_Load("../graphic/santa_walk_gun.png");
    if (santagun_surface == NULL)
    {
        printf("load santa_walk_gun.png failed %s\n", IMG_GetError());
        success = false;
    }
    santagun_texture = SDL_CreateTextureFromSurface(grenderer, santagun_surface);

    bl_surface = IMG_Load("../graphic/bl.png");
    if (bl_surface == NULL)
    {
        printf("load bl.png failed %s\n", IMG_GetError());
        success = false;
    }
    bl_texture = SDL_CreateTextureFromSurface(grenderer, bl_surface);

    zombie_die_surface = IMG_Load("../graphic/zombie_die.png");
    if (zombie_die_surface == NULL)
    {
        printf("load zombie_die.png failed %s\n", IMG_GetError());
        success = false;
    }
    zombie_die_texture = SDL_CreateTextureFromSurface(grenderer, zombie_die_surface);

    santabar_surface = IMG_Load("../graphic/santa_bar.png");
    if (santabar_surface == NULL)
    {
        printf("load santa_bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    santabar_texture = SDL_CreateTextureFromSurface(grenderer, santabar_surface);

    zombi_surface = IMG_Load("../graphic/zombi_bar.png");
    if (zombi_surface == NULL)
    {
        printf("load zombi_bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    zombi_texture = SDL_CreateTextureFromSurface(grenderer, zombi_surface);

    healtsanta1_surface = IMG_Load("../graphic/healt_bar1.png");
    if (healtsanta1_surface == NULL)
    {
        printf("load healt_bar1.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtsanta1_texture = SDL_CreateTextureFromSurface(grenderer, healtsanta1_surface);

    healtsanta2_surface = IMG_Load("../graphic/healt_bar2.png");
    if (healtsanta2_surface == NULL)
    {
        printf("load healt_bar2.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtsanta2_texture = SDL_CreateTextureFromSurface(grenderer, healtsanta2_surface);

    healtsanta3_surface = IMG_Load("../graphic/healt_bar3.png");
    if (healtsanta3_surface == NULL)
    {
        printf("load healt_bar3.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtsanta3_texture = SDL_CreateTextureFromSurface(grenderer, healtsanta3_surface);

    healtsanta4_surface = IMG_Load("../graphic/healt_bar4.png");
    if (healtsanta4_surface == NULL)
    {
        printf("load healt_bar4.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtsanta4_texture = SDL_CreateTextureFromSurface(grenderer, healtsanta4_surface);

    healtsanta5_surface = IMG_Load("../graphic/healt_bar5.png");
    if (healtsanta5_surface == NULL)
    {
        printf("load healt_bar5.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtsanta5_texture = SDL_CreateTextureFromSurface(grenderer, healtsanta5_surface);

    healtsanta6_surface = IMG_Load("../graphic/healt_bar6.png");
    if (healtsanta6_surface == NULL)
    {
        printf("load healt_bar6.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtsanta6_texture = SDL_CreateTextureFromSurface(grenderer, healtsanta6_surface);


    healtzombi1_surface = IMG_Load("../graphic/healtzombi_bar1.png");
    if (healtzombi1_surface == NULL)
    {
        printf("load healtzombi_bar1.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtzombi1_texture = SDL_CreateTextureFromSurface(grenderer, healtzombi1_surface);

    healtzombi2_surface = IMG_Load("../graphic/healtzombi_bar2.png");
    if (healtzombi2_surface == NULL)
    {
        printf("load healtzombi_bar2.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtzombi2_texture = SDL_CreateTextureFromSurface(grenderer, healtzombi2_surface);

    healtzombi3_surface = IMG_Load("../graphic/healtzombi_bar3.png");
    if (healtzombi3_surface == NULL)
    {
        printf("load healtzombi_bar3.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtzombi3_texture = SDL_CreateTextureFromSurface(grenderer, healtzombi3_surface);

    healtzombi4_surface = IMG_Load("../graphic/healtzombi_bar4.png");
    if (healtzombi4_surface == NULL)
    {
        printf("load healtzombi_bar4.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtzombi4_texture = SDL_CreateTextureFromSurface(grenderer, healtzombi4_surface);

    healtzombi5_surface = IMG_Load("../graphic/healtzombi_bar5.png");
    if (healtzombi5_surface == NULL)
    {
        printf("load healtzombi_bar5.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtzombi5_texture = SDL_CreateTextureFromSurface(grenderer, healtzombi5_surface);

    healtzombi6_surface = IMG_Load("../graphic/healtzombi_bar6.png");
    if (healtzombi6_surface == NULL)
    {
        printf("load healtzombi_bar6.png failed %s\n", IMG_GetError());
        success = false;
    }
    healtzombi6_texture = SDL_CreateTextureFromSurface(grenderer, healtzombi6_surface);

    bl_boss_surface = IMG_Load("../graphic/bl2.png");
    if (bl_boss_surface == NULL)
    {
        printf("load healtzombi_bar6.png failed %s\n", IMG_GetError());
        success = false;
    }
    bl_boss_texture = SDL_CreateTextureFromSurface(grenderer, bl_boss_surface);

    gameover_surface = IMG_Load("../graphic/gamewinner.png");
    if (gameover_surface == NULL)
    {
        printf("load gamewinner.png failed %s\n", IMG_GetError());
        success = false;
    }
    gameover_texture = SDL_CreateTextureFromSurface(grenderer, gameover_surface);

    gamewinner_surface = IMG_Load("../graphic/gameover.png");
    if (gamewinner_surface == NULL)
    {
        printf("load gamewinner.png failed %s\n", IMG_GetError());
        success = false;
    }
    gamewinner_texture = SDL_CreateTextureFromSurface(grenderer, gamewinner_surface);


    music = Mix_LoadMUS("bgm.mp3");
    if (music == NULL)
    {
        //printf("load music error");
        success = false;
    }
    shoot_sound = Mix_LoadWAV("shoot.wav");
    if (shoot_sound == NULL)
    {

        success = false;
    }

    walk = Mix_LoadWAV("walk.wav");
    if (walk == NULL)
    {

        success = false;
    }

    hit = Mix_LoadWAV("hit.wav");
    if (hit == NULL)
    {

        success = false;
    }
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
    topA = a.y+50;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y+50;
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

            player = player_animation_texture;

            bool check_jump = false, zombie1 = 1, zombie_alive1 = true, zombie_alive2 = true;
            bool status_player = 0;
            bool zombie_status1 = 0,zombie_status2 = 0, zombie_status3 = 0,zombie_status4 = 0, zombie_status5 = 0;
            int time,ground = 570,pad = 0, count_zombie = 0, count_zombie1 = 0;
            float gravity = 0.125
             ,speed,speedair,gravity_air = 0.01;
            display = background_texture;
            int animation_player = 0, animation_zombie = 0, animation_boss = 0;
            int quit = 0;
            while (!quit){
                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT){
                        quit = 1;
                    }
                    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
                        //display = background_gametexture;
                        game_menu = false;
                        ingame = true;
                    }
                    else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
                        animation_player++;
                        player_position.x+=10;
                        player1_position.x += 6;
                        bl_position.x += 8;

                    }

                    else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a){
                        animation_player++;
                        player_position.x -= 10;
                        player1_position.x -= 3;
                        bl_position.x -= 5;



                    }

                    else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w && check_jump == false){
                        speed = -6.5;
                        check_jump = true;
                    }
                    else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_k){
                        Mix_PlayChannel(-1, shoot_sound, 0);
                        if (shoot == 0 && check_jump == false){
                           shoot = 1;
                           bl_position.x = player_position.x + 130;

                        }
                        else if (shoot == 1 && check_jump == false){

                            shoot = 2;
                            bl_position1.x = player_position.x + 130;
                        }
                        else if (shoot == 2 && check_jump == false){

                            shoot = 3;
                            bl_position2.x = player_position.x + 130;
                        }
                        else if (shoot == 3 && check_jump == false){

                            shoot = 4;
                            bl_position3.x = player_position.x + 130;
                        }
                        else if (shoot == 4 && check_jump == false){

                            shoot = 5;
                            bl_position4.x = player_position.x + 130;
                        }
                    }
                    else if(event.type == SDL_KEYUP){
                        animation_player = 0;
                    }



                }

                SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(grenderer);
                if(game_menu){
                    SDL_RenderCopy(grenderer, background_texture, NULL, NULL);

                }
                else if (!ingame && gameover){
                    SDL_RenderCopy(grenderer, gamewinner_texture, NULL, NULL);
                }
                else if (!ingame & !gameover){
                    SDL_RenderCopy(grenderer, gameover_texture, NULL, NULL);
                }
                else if(ingame){
                    if (!Mix_PlayingMusic()){
                        Mix_PlayMusic(music,-1);
                    }
                    time++;
                    speed += gravity;
                    speedair += gravity_air;
                    //airdrop.y += speedair;
                    player_position.y += speed;
                    SDL_RenderCopy(grenderer, background_gametexture, NULL, NULL);
                    SDL_RenderCopy(grenderer, airdrop_texture, NULL, &airdrop);
                    //SDL_RenderCopy(grenderer, zombie_die_texture, &zombie_die[animation_zombie_die / 15], &zombie_test);
                    SDL_RenderCopy(grenderer, boss_texture, &boss_animation[animation_boss / 9], &boss_position);
                    bl_boss1.x -= 10;
                    bl_boss2.x -= 10;
                    SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position1);
                    SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position2);
                    SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position3);
                    SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position4);

                    SDL_RenderCopy(grenderer, bl_boss_texture, &bl_boss_animation[1], &bl_boss1);
                    SDL_RenderCopy(grenderer, bl_boss_texture, &bl_boss_animation[1], &bl_boss2);


                    SDL_RenderCopy(grenderer, santabar_texture, NULL, &santabar_position);
                    SDL_RenderCopy(grenderer, zombi_texture, NULL, &zombi_position);
                    animation_zombie++;
                    animation_boss++;
                    if (bl_boss1.x < 0 ){
                        bl_boss1.x = 1200;
                    }
                    if (bl_boss2.x < 0){
                        bl_boss2.x = 1200;
                    }
                     if (checkCollision(player_position, bl_boss2)){
                        SDL_RenderCopy(grenderer, bl_boss_texture, &bl_boss_animation[0], &bl_boss2);
                        bl_boss2.x = 1200;
                        counthealt += 10;
                        Mix_PlayChannel(-1, hit, 0);
                    }
                    if (checkCollision(player_position, bl_boss1)){
                        SDL_RenderCopy(grenderer, bl_boss_texture, &bl_boss_animation[0], &bl_boss1);
                        bl_boss1.x = 1200;
                        counthealt += 10;
                        Mix_PlayChannel(-1, hit, 0);
                    }
                    if (checkCollision(player_position, airdrop)){
                        player = santagun_texture;

                        player_position.w += 60;
                        player_position.h += 35;
                        airdrop.x += 5000;
                        box1.y -= 45;
                        box2.y -= 45;
                        box3.y -= 40;
                        box1.x += 30;
                        box2.x += 30;
                        box3.x += 30;
                        box1.w -= 50;
                        box2.w -= 50;
                        box3.w -= 50;




                    }
                    if (player == santagun_texture){
                            SDL_RenderCopy(grenderer, player, &gun_animation[animation_player / 2], &player_position);
                            if (player_position.y > 530){
                                check_jump = false;
                                player_position.y = 530;
                                speed = 1;
                                bl_position.y = 625;
                                bl_position1.y = 625;
                                bl_position2.y = 625;
                                bl_position3.y = 625;
                                bl_position4.y = 625;
                            }
                        }
                        else{
                            SDL_RenderCopy(grenderer, player, &player_animation[animation_player / 2], &player_position);
                            if (player_position.y > 570){
                                check_jump = false;
                                player_position.y = 570;
                                speed = 1;
                                printf("test");
                            }
                        }

                    if (shoot == 1 || shoot == 2 || shoot == 3 || shoot == 4 || shoot == 5 || shoot == 0) {
                        bl_position.x += 8;
                        bl_position1.x += 8;
                        bl_position2.x += 8;
                        bl_position3.x += 8;
                        bl_position4.x += 8;
                    }
                    if (shoot == 5){
                        shoot = 0;
                    }
                    if (animation_zombie_die[0] / 15 > 7){
                        zombie_position.w =140;

                    }
                    if (animation_zombie_die[0] / 15 > 11){
                        animation_zombie_die[0] = 0;
                        zombie_position.x = 2000;
                        alive[0] = true;
                        zombie_position.w = 90;

                    }
                    if (animation_zombie_die[1] / 15 > 7){
                        zombie_position1.w =140;

                    }
                    if (animation_zombie_die[1] / 15 > 11){
                        animation_zombie_die[1] = 0;
                        zombie_position1.x = 2190;
                        alive[1] = true;
                        zombie_position1.w = 90;

                    }
                    if (animation_zombie_die[2] / 15 > 7){
                        zombie_position3.w =140;

                    }
                    if (animation_zombie_die[2] / 15 > 11){
                        animation_zombie_die[2] = 0;
                        zombie_position3.x = 2500;
                        alive[2] = true;
                        zombie_position3.w = 90;

                    }
                    if (animation_zombie_die[3] / 15 > 7){
                        zombie_position4.w =140;

                    }
                    if (animation_zombie_die[3] / 15 > 11){
                        animation_zombie_die[3] = 0;
                        zombie_position4.x = 3000;
                        alive[3] = true;
                        zombie_position4.w = 90;

                    }

                    if (animation_player/2 > 11)
                    {
                        animation_player = 0;
                    }
                    if (animation_boss/9 > 14){
                        animation_boss = 0;
                    }

                    if (zombie_status1){
                        if (animation_zombie/15 > 8){
                            animation_zombie = 0;
                        }
                    }
                    if (animation_zombie_attack[0]/15 > 7){
                        animation_zombie_attack[0] = 0;
                        counthealt++;
                    }
                    if (animation_zombie_attack[1]/15 > 7){
                        animation_zombie_attack[1] = 0;
                        counthealt++;
                    }
                    if (animation_zombie_attack[2]/15 > 7){
                        animation_zombie_attack[2] = 0;
                        counthealt++;
                    }
                    if (animation_zombie_attack[3]/15 > 7){
                        animation_zombie_attack[3] = 0;
                        counthealt++;
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


                    SDL_RenderCopy(grenderer, airdrop_texture, NULL, &airdrop);
                     if (checkCollision( box1, player_position )&& speed > 0.999996){ // check jump pad player
                            if (player_position.y > box1.y){
                                player_position.y = box1.y;
                                bl_position.y = 430;
                                bl_position1.y = 430;
                                bl_position2.y = 430;
                                bl_position3.y = 430;

                                bl_position4.y = 430;
                                speed = 1;
                                check_jump = false;
                                pad = 0;
                            }

                    }

                    if (checkCollision( box3, player_position )&& speed > 0.999996){ // check jump pad player
                            if (player_position.y > box3.y){
                                player_position.y = box3.y;
                                bl_position1.y = 175;
                                bl_position2.y = 175;
                                bl_position4.y = 175;
                                bl_position3.y = 175;
                                speed = 1;
                                check_jump = false;
                                bl_position.y = 175;

                            }
                    }
                    if (checkCollision( box2, player_position )&& speed > 0.999996){ // check jump pad player
                            if (player_position.y > box2.y){
                                player_position.y = box2.y;
                                bl_position.y = 310;
                                bl_position3.y = 310;
                                bl_position2.y = 310;
                                bl_position4.y = 310;
                                speed = 1;
                                bl_position1.y = 310;
                                check_jump = false;
                                pad = 1;
                            }

                    }


                    if (!checkCollision( zombie_position, player_position ) && alive[0]){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position.x -= 1.1;
                        zombie = zombie_texture;
                        zombie_status1 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/15], &zombie_position);

                    }
                    /*if (checkCollision(bl_position, zombie_position) || checkCollision(bl_position, zombie_position1) || checkCollision(bl_position, zombie_position3)){
                        if (checkCollision(bl_position, zombie_position) && alive[0]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position);
                            bl_position.x = 9999;
                            count_zombie++;
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position);
                        }
                        if (checkCollision(bl_position, zombie_position1) && alive[1]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position);
                            bl_position.x = 9999;
                            check_bullet[0]++;

                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position);
                        }
                        if (checkCollision(bl_position, zombie_position3)&& alive[2]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position);
                            bl_position.x = 9999;
                            check_bullet[1]++;

                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position);
                        }


                    }*/
                    if (checkCollision(bl_position1, zombie_position) || checkCollision(bl_position1, zombie_position1) || checkCollision(bl_position1, zombie_position3) || checkCollision(bl_position1, zombie_position4) || checkCollision(bl_position1,boss_position)){
                        if (checkCollision(bl_position1, zombie_position) && alive[0]){

                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position1);
                            bl_position1.x = 9999;
                            count_zombie++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position1);
                        }
                        if (checkCollision(bl_position1, zombie_position1) && alive[1]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position1);
                            bl_position1.x = 9999;
                            check_bullet[0]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position1);
                        }
                        if (checkCollision(bl_position1, zombie_position3) && alive[2]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position1);
                            bl_position1.x = 9999;
                            check_bullet[1]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position1);
                        }
                        if (checkCollision(bl_position1, zombie_position4) && alive[3]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position1);
                            bl_position1.x = 9999;
                            check_bullet[2]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position1);
                        }
                        if (checkCollision(bl_position1, boss_position) && alive[4]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position1);
                            bl_position1.x = 9999;
                            check_bullet[3]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position1);
                        }
                    }

                    if (checkCollision(bl_position2, zombie_position) || checkCollision(bl_position2, zombie_position1)|| checkCollision(bl_position2, zombie_position3)|| checkCollision(bl_position2, zombie_position4)|| checkCollision(bl_position2,boss_position)){
                        if (checkCollision(bl_position2, zombie_position) && alive[0]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position2);
                            bl_position2.x = 9999;
                            count_zombie++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position2);
                        }
                        if (checkCollision(bl_position2, zombie_position1) && alive[1]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position2);
                            bl_position2.x = 9999;
                            check_bullet[0]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position2);
                        }
                         if (checkCollision(bl_position2, zombie_position3) && alive[2]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position2);
                            bl_position2.x = 9999;
                            check_bullet[1]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position2);
                        }
                          if (checkCollision(bl_position2, zombie_position4) && alive[3]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position2);
                            bl_position2.x = 9999;
                            check_bullet[2]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position2);
                        }
                        if (checkCollision(bl_position2, boss_position) && alive[4]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position2);
                            bl_position2.x = 9999;
                            check_bullet[3]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position2);
                        }
                    }

                    if (checkCollision(bl_position3, zombie_position) || checkCollision(bl_position3, zombie_position1) || checkCollision(bl_position3, zombie_position3)|| checkCollision(bl_position3, zombie_position4)|| checkCollision(bl_position3,boss_position)){
                        if (checkCollision(bl_position3, zombie_position)&& alive[0]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position3);
                            bl_position3.x = 9999;
                            count_zombie++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position3);
                        }
                        if (checkCollision(bl_position3, zombie_position1) && alive[1]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position3);
                            bl_position3.x = 9999;
                            check_bullet[0]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position3);
                        }
                         if (checkCollision(bl_position3, zombie_position3) && alive[2]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position3);
                            bl_position3.x = 9999;
                            check_bullet[1]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position3);
                        }
                        if (checkCollision(bl_position3, zombie_position4) && alive[3]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position3);
                            bl_position3.x = 9999;
                            check_bullet[2]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position3);
                        }
                        if (checkCollision(bl_position3, boss_position) && alive[4]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position3);
                            bl_position3.x = 9999;
                            check_bullet[3]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position3);
                        }
                    }
                    if (checkCollision(bl_position4, zombie_position)|| checkCollision(bl_position4, zombie_position1) || checkCollision(bl_position4, zombie_position3)|| checkCollision(bl_position4, zombie_position4) || checkCollision(bl_position4, boss_position)){

                        if (checkCollision(bl_position4, zombie_position) && alive[0]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position4);
                            bl_position4.x = 9999;
                            count_zombie++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position4);
                        }
                        if (checkCollision(bl_position4, zombie_position1) && alive[1]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position4);
                            bl_position4.x = 9999;
                            check_bullet[0]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position4);
                        }
                        if (checkCollision(bl_position4, zombie_position3) && alive[2]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position4);
                            bl_position4.x = 9999;
                            check_bullet[1]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position4);
                        }
                        if (checkCollision(bl_position4, zombie_position4) && alive[3]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position4);
                            bl_position4.x = 9999;
                            check_bullet[2]++;
                            Mix_PlayChannel(-1, hit, 0);
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position4);
                        }
                        if (checkCollision(bl_position4, boss_position) && alive[4]){
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[1], &bl_position4);
                            bl_position4.x = 9999;
                            check_bullet[3]++;
                        }
                        else{
                            SDL_RenderCopy(grenderer, bl_texture, &bl_animation[0], &bl_position4);
                        }
                    }
                    if (count_zombie == 5){
                        zombie_position.w = 110;
                        alive[0] = false;
                        count_zombie = 0;
                    }
                    if (check_bullet[0] == 5){
                        zombie_position1.w = 110;
                        alive[1] = false;
                        check_bullet[0] = 0;
                    }
                    if (check_bullet[1] == 5){
                        zombie_position3.w = 110;
                        alive[2] = false;
                        check_bullet[1] = 0;
                    }
                    if (check_bullet[2] == 5){
                        zombie_position4.w = 110;
                        alive[3] = false;
                        check_bullet[2] = 0;
                    }

                    if (alive[0] && checkCollision( zombie_position, player_position)){
                        zombie = zombieattack_texture;
                        animation_zombie_attack[0]++;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie_attack[0]/15], &zombie_position);
                        zombie_status1 = 0;

                    }
                    else if (!alive[0]){
                        animation_zombie_die[0]++;
                        zombie = zombie_die_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_die[animation_zombie_die[0]/15], &zombie_position);//
                    }


                    if (!checkCollision(zombie_position1, player_position) && alive[1]){
                        zombie_position1.x -= 4;
                        zombie = zombie_texture;
                        zombie_status3 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/15], &zombie_position1);
                    }
                    else if (checkCollision(zombie_position1, player_position) && alive[1]){
                        zombie = zombieattack_texture;
                        animation_zombie_attack[1]++;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie_attack[1]/15], &zombie_position1);
                        zombie_status3 = 0;

                    }
                    else if (!alive[1]){
                        animation_zombie_die[1]++;
                        zombie = zombie_die_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_die[animation_zombie_die[1]/15], &zombie_position1);//
                    }



                    if (!checkCollision( zombie_position3, player_position) && alive[2] ){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position3.x -= 4;
                        zombie = zombie_texture;
                        zombie_status3 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/19], &zombie_position3);
                    }

                    else if (checkCollision(zombie_position3, player_position) && alive[2]){
                        zombie = zombieattack_texture;
                        animation_zombie_attack[2]++;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie_attack[2]/15], &zombie_position3);
                        zombie_status3 = 0;

                    }
                    else if (!alive[2]){
                        animation_zombie_die[2]++;
                        zombie = zombie_die_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_die[animation_zombie_die[2]/15], &zombie_position3);//
                    }


                    if (!checkCollision( zombie_position4, player_position) && alive[3] ){ //zombie operation check attack if zombie crash player they will do attack animation
                        zombie_position4.x -= 2.5;
                        zombie = zombie_texture;
                        zombie_status3 = 1;
                        SDL_RenderCopy(grenderer, zombie, &zombie_animation[animation_zombie/17], &zombie_position4);
                    }
                    else if (checkCollision(zombie_position4, player_position) && alive[3]){
                        zombie = zombieattack_texture;
                        animation_zombie_attack[3]++;
                        SDL_RenderCopy(grenderer, zombie, &zombie_attack_animation[animation_zombie_attack[3]/15], &zombie_position4);
                        zombie_status3 = 0;

                    }
                    else if (!alive[3]){
                        animation_zombie_die[3]++;
                        zombie = zombie_die_texture;
                        SDL_RenderCopy(grenderer, zombie, &zombie_die[animation_zombie_die[3]/15], &zombie_position4);//
                    }
                    if(counthealt==0){
                        SDL_RenderCopy(grenderer, healtsanta1_texture, NULL, &healtsanta1_position);
                    }
                    if(counthealt>0 && counthealt<10){
                        SDL_RenderCopy(grenderer, healtsanta2_texture, NULL, &healtsanta1_position);
                    }
                    if(counthealt>=10 && counthealt<20){
                        SDL_RenderCopy(grenderer, healtsanta3_texture, NULL, &healtsanta1_position);
                    }
                    if(counthealt>=20&& counthealt<30){
                        SDL_RenderCopy(grenderer, healtsanta4_texture, NULL, &healtsanta1_position);
                    }
                    if(counthealt>=30 && counthealt<40){
                        SDL_RenderCopy(grenderer, healtsanta5_texture, NULL, &healtsanta1_position);
                    }
                    if(counthealt>=40){
                        SDL_RenderCopy(grenderer, healtsanta6_texture, NULL, &healtsanta1_position);
                        SDL_RenderCopy(grenderer, gamewinner_texture, NULL, NULL);
                        ingame = false;
                        gameover = true;
                    }

                    if(check_bullet[3] >= 00 && check_bullet[3] < 10){
                        SDL_RenderCopy(grenderer, healtzombi1_texture, NULL, &healtzombi1_position);
                    }
                    if(check_bullet[3] >= 10 && check_bullet[3] < 20){
                        SDL_RenderCopy(grenderer, healtzombi2_texture, NULL, &healtzombi1_position);
                    }
                    if(check_bullet[3] >= 20 && check_bullet[3] < 30){
                        SDL_RenderCopy(grenderer, healtzombi3_texture, NULL, &healtzombi1_position);
                    }
                    if(check_bullet[3] >= 30 && check_bullet[3] < 40){
                        SDL_RenderCopy(grenderer, healtzombi4_texture, NULL, &healtzombi1_position);
                    }
                    if(check_bullet[3] >= 40 && check_bullet[3] < 50){
                        SDL_RenderCopy(grenderer, healtzombi5_texture, NULL, &healtzombi1_position);
                    }
                    if(check_bullet[3] >= 50 && check_bullet[3] < 60){
                        SDL_RenderCopy(grenderer, healtzombi6_texture, NULL, &healtzombi1_position);
                        gameover = false;
                        ingame = false;
                    }


                    if (airdrop.y > 320){
                        airdrop.y = 320;
                        speedair = 1;
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



                    if (zombie1 == 1){
                        zombie_position1.x = 2500;
                        zombie_position1.y = 570;
                        SDL_RenderCopy(grenderer, zombie_texture, &zombie_animation[animation_zombie/15], &zombie_position1);
                        zombie1 = 0;
                    }
                    /*if (animation_player % 2 == 0){
                        Mix_PlayChannel(-1, walk, 0);
                    }*/



                }
                SDL_RenderPresent(grenderer);
            }

        }
    }
    SDL_DestroyWindow( window );
    Mix_FreeChunk(shoot_sound);
    Mix_FreeChunk(walk);
    Mix_FreeMusic(music);
    Mix_Quit();
    SDL_Quit();
    return 0;
}
