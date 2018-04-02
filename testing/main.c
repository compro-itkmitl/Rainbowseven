//Game project with SDL library
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// all global variable declaration here
const int screen_width = 1024;
const int screen_height = 720;
SDL_Window* gwindow = NULL;
SDL_Renderer* grenderer = NULL;

// for random number
void random_setup()
{
    time_t t;
    srand((unsigned) time(&t));
}
float random_num(int range)
{
    float result;
    int num;
    num = rand() % range;
    result = num;
    return result;
}
// for random number

//all number declaration here
float pi = 3.14159;
float angle = 45;// angle for shooting
float player1_angle = 45;// angle for player1 gun
float player2_angle = 45;// angle for player2 gun
float sy = -999999;// speed in y axis
float ay = 0.1;// gravity force
float sx = 0;// speed in x axis
float xlup = 0;// speed in x+y with angle
float wind = 0;// negative wind is left positive wind is right
float save_wind = 0;// save amount of wind in this for some use
float player1hp = 250;
float player2hp = 250;
float player1_hp_color_g = 0;// variable for changing color of hp
float player2_hp_color_r = 0;// variable for changing color of hp
float player2_hp_color_g = 0;// variable for changing color of hp
float player1_hp_color_r = 0;// variable for changing color of hp
float speedpower = 10;// charging speed
float split_bullet_sx[3] = {0, 0, 0};// speed in x axis for skill split
float split_bullet_sy[3] = {0, 0, 0};// speed in y axis for skill split
float split_bullet_ay[3] = {0.1, 0.1, 0.1};// gravity for skill split
float player1_shield_gen_hp = 100;
float player2_shield_gen_hp = 100;
float player1_shield_hp_color_g = 0;// variable for changing color of hp
float player2_shield_hp_color_r = 0;// variable for changing color of hp
float player2_shield_hp_color_g = 0;// variable for changing color of hp
float player1_shield_hp_color_r = 0;// variable for changing color of hp
float alpha = 255;// variable to set opacity used for fading
bool fire = false;// for checking that player fire or not
bool charge = false;// check that player is charging
bool hit = false;// check that bullet is hit or not
bool nextturn = false;// check that player turn is over
bool gameend = false;// check that game is end
bool ingame = false;// check that game is playing
bool select_hero = false;// check that game is in select hero screen
bool skillwind = false;// check skill wind activation
bool skillblock = false;// check skill block activation
bool skillblock_hit = false;// check skill block is hit
bool skilldouble = false;// check skill double activation
bool doublehit = false;// check for skill double
bool skillpoison = false;// check skill poison activation
bool skillpoison_hit = false;// check skill poison is hit
int skillpoison_target = 0;// keep target of poison
int poisonturn = 0;// count turn of poison
bool skillsplit = false;// check skill split activation
bool skillorb = false;// check skill orb activation
bool skillshield = false;// check skill shield activation
bool shield_hit = false;// check for bullet hit skill shield
bool split_start = false;// boolean for start bullet split
bool split_bullet_1_hit = false;// check split bullet hit
bool split_bullet_2_hit = false;// check split bullet hit
bool split_bullet_3_hit = false;// check split bullet hit
bool split_bullet_1_damage = false;// check split bullet damage
bool split_bullet_2_damage = false;// check split bullet damage
bool split_bullet_3_damage = false;// check split bullet damage
bool overcharge = false;// check if charge to max yet?
bool ready = false;// for player to press enter before start their turn
bool afterhit = false;// check for bullet hit to start animation after bullet hit
bool start_explode = false;// check for bullet to start explode animation
bool save_once = false;// use to save wind once in skill double
bool orbhit = false;
int c_turn = 0;// count turn for skill wind
int orb_turn = 0;// count turn for skill orb
int skillwind_target = -99;// keep target for skill wind
int skillblock_target = -99;// keep target for skill block
int player1_hero = -1;// keep which hero player1 is
int player2_hero = -1;// keep which hero player2 is
int current_player = 1;// 1 for player 1 or left player, -1 for player 2 or right player
int confirm_hero = 0;// count for choosing hero
int hero_choose = -1;// temporary keep for choosing hero
int player1_bullet_animate_speed = 0;// animation speed for player1 bullet
int player2_bullet_animate_speed = 0;// animation speed for player2 bullet
int num_map = 0;// number for random map
int player1_atk = 0;
int player2_atk = 0;
int player1_skill1_cooldown = 0;
int player2_skill1_cooldown = 0;
int player1_skill1_max_cooldown = 0;
int player2_skill1_max_cooldown = 0;
int player1_skill2_cooldown = 0;
int player2_skill2_cooldown = 0;
int player1_skill2_max_cooldown = 0;
int player2_skill2_max_cooldown = 0;
int shield_gen_move = 1;
int orb1_sx = 0;
int orb1_sy = 0;
int orb2_sx = 0;
int orb2_sy = 0;
int orb3_sx = 0;
int orb3_sy = 0;
int orb4_sx = 0;
int orb4_sy = 0;
int orb_top = 0;
int orb_bottom = 0;
int orb_left = 0;
int orb_right = 0;
int shield_turn = 0;
int timeout = 0;
int escape = 0;
//all number declaration here

//all position and size here
SDL_Rect bar = {10,5,0,20};// charging power bar for shooting
SDL_Rect charge_bar = {2, 0, 1020, 30};
SDL_Rect bulletsize = {120,450,50,50};

SDL_Rect player1size = {50, 365, 120, 210};// location and size for player1
SDL_Rect player2size = {854, 365, 120, 210};// location and size for player2

// collider for each player
SDL_Rect player1_upper_size = {63, 380, 95, 50};
SDL_Rect player1_middle_size = {50, 430, 120, 40};
SDL_Rect player1_lower_size = {68, 450, 83, 130};
SDL_Rect player2_upper_size = {867, 380, 95, 50};
SDL_Rect player2_middle_size = {855, 430, 120, 40};
SDL_Rect player2_lower_size = {873, 450, 83, 130};
// collider for each player

SDL_Rect player1_gun_size = {120, 450, 120, 60};
SDL_Rect player2_gun_size = {790, 450, 120, 60};
SDL_Rect windsize = {420, 118, 50, 24};
SDL_Rect wind_bar_size = {418, 115, 150, 30};
SDL_Rect winddirectionsize = {470, 80, 50, 20};
SDL_Rect player1hpsize = {55, 680, 50, 21};
SDL_Rect player2hpsize = {680, 680, 50, 21};
SDL_Rect player1hp_bar_size = {50,675, 300, 30};
SDL_Rect player2hp_bar_size = {675,675, 300, 30};
SDL_Rect hero1_pic_size = {150, 300, 150, 150};// hero1
SDL_Rect hero2_pic_size = {340, 300, 150, 150};// hero2
SDL_Rect hero3_pic_size = {520, 300, 150, 150};// hero3
SDL_Rect hero4_pic_size = {700, 300, 150, 150};// hero4
SDL_Rect confirm_pic_size = {430, 200, 150, 150};
SDL_Rect player1_skill1_size = {50, 580, 50, 50};
SDL_Rect player2_skill1_size = {870, 580, 50, 50};
SDL_Rect player1_skill2_size = {105, 580, 50, 50};
SDL_Rect player2_skill2_size = {925, 580, 50, 50};
SDL_Rect split_bullet_1_size = {-50, 0, 30, 30};
SDL_Rect split_bullet_2_size = {-50, 0, 30, 30};
SDL_Rect split_bullet_3_size = {-50, 0, 30, 30};
SDL_Rect player1_shield_gen_size = {0, 50, 100, 100};
SDL_Rect player2_shield_gen_size = {924, 50, 100, 100};
SDL_Rect player1_shield_gen_hp_size = {55, 640, 50, 20};
SDL_Rect player2_shield_gen_hp_size = {680, 640, 50, 20};
SDL_Rect player1_shield_gen_hp_bar_size = {50, 635, 300, 30};
SDL_Rect player2_shield_gen_hp_bar_size = {675, 635, 300, 30};
SDL_Rect player1_barrier_size = {220, 360, 20, 215};
SDL_Rect player2_barrier_size = {784, 360, 20, 215};
SDL_Rect shield_size = {0, 0, 100, 100};
SDL_Rect potion_size = {0, 0, 50, 50};
SDL_Rect orb_size[4];
SDL_Rect poison_icon_1 = {366, 678, 25, 25};
SDL_Rect poison_icon_2 = {637, 678, 25, 25};
SDL_Rect shield_collider[4];
SDL_Rect space_font = {390, 550, 250, 50};
SDL_Rect arrow_font = {360, 600, 300, 50};
SDL_Rect skill_font = {390, 650, 250, 50};
SDL_Color textcolor = {0, 0, 0};

SDL_Rect collider[11];

void set_collider()
{
    collider[0].x = 0;// collider 0 is ground
    collider[0].y = 575;
    collider[0].w = 1024;
    collider[0].h = 20;
    collider[1].x = player1_upper_size.x;// collider 1 is player1 upper
    collider[1].y = player1_upper_size.y;
    collider[1].w = player1_upper_size.w;
    collider[1].h = player1_upper_size.h;
    collider[2].x = player2_upper_size.x;// collider 2 is player2 upper
    collider[2].y = player2_upper_size.y;
    collider[2].w = player2_upper_size.w;
    collider[2].h = player2_upper_size.h;
    collider[3].x = player1_shield_gen_size.x;// collider 3 is player1 shield gen
    collider[3].y = player1_shield_gen_size.y;
    collider[3].w = player1_shield_gen_size.w;
    collider[3].h = player1_shield_gen_size.h;
    collider[4].x = player2_shield_gen_size.x;// collider 4 is player2 shield gen
    collider[4].y = player2_shield_gen_size.y;
    collider[4].w = player2_shield_gen_size.w;
    collider[4].h = player2_shield_gen_size.h;
    collider[5].x = player1_barrier_size.x;// collider 5 is player1 barrier
    collider[5].y = player1_barrier_size.y;
    collider[5].w = player1_barrier_size.w;
    collider[5].h = player1_barrier_size.h;
    collider[6].x = player2_barrier_size.x;// collider 6 is player2 barrier
    collider[6].y = player2_barrier_size.y;
    collider[6].w = player2_barrier_size.w;
    collider[6].h = player2_barrier_size.h;
    collider[7].x = player1_middle_size.x;// collider 7 is player1 middle
    collider[7].y = player1_middle_size.y;
    collider[7].w = player1_middle_size.w;
    collider[7].h = player1_middle_size.h;
    collider[8].x = player2_middle_size.x;// collider 8 is player2 middle
    collider[8].y = player2_middle_size.y;
    collider[8].w = player2_middle_size.w;
    collider[8].h = player2_middle_size.h;
    collider[9].x = player1_lower_size.x;// collider 9 is player1 lower
    collider[9].y = player1_lower_size.y;
    collider[9].w = player1_lower_size.w;
    collider[9].h = player1_lower_size.h;
    collider[10].x = player2_lower_size.x;// collider 10 is player2 lower
    collider[10].y = player2_lower_size.y;
    collider[10].w = player2_lower_size.w;
    collider[10].h = player2_lower_size.h;
}

// animate things here
SDL_Rect mainbackground_animate[4];
SDL_Rect star_animate[5];
SDL_Rect hero1_pic_animate[2];
SDL_Rect hero2_pic_animate[2];
SDL_Rect hero3_pic_animate[2];
SDL_Rect hero4_pic_animate[2];
SDL_Rect bullet_animate[10];
SDL_Rect player1_bullet_animate[10];
SDL_Rect player2_bullet_animate[10];
SDL_Rect bomb_animate[8];
SDL_Rect wind_arrow_animate[2];
SDL_Rect dynamite_animate[8];
SDL_Rect rock_animate[6];
SDL_Rect potion_animate[4];
SDL_Rect shield_gen_animate[4];
int mainbg_frame = 0;
int star_frame = 0;
int hero1_pic_frame = 0;
int hero2_pic_frame = 0;
int hero3_pic_frame = 0;
int hero4_pic_frame = 0;
int bullet_frame = 0;
int bullet_max_frame = 0;// variable for loop, it's a max frame for bullet, set it to how many frame for that type of bullet
int player1_bullet_max_frame = 0;
int player2_bullet_max_frame = 0;
int wind_arrow_frame = 0;
int bullet_animate_speed = 0;
int potion_frame = 0;
int shield_gen_frame = 0;

void setanimation()
{
    mainbackground_animate[0].x = 0;
    mainbackground_animate[0].y = 0;
    mainbackground_animate[0].w = 1024;
    mainbackground_animate[0].h = 720;
    mainbackground_animate[1].x = 1024;
    mainbackground_animate[1].y = 0;
    mainbackground_animate[1].w = 1024;
    mainbackground_animate[1].h = 720;
    mainbackground_animate[2].x = 2048;
    mainbackground_animate[2].y = 0;
    mainbackground_animate[2].w = 1024;
    mainbackground_animate[2].h = 720;
    mainbackground_animate[3].x = 3072;
    mainbackground_animate[3].y = 0;
    mainbackground_animate[3].w = 1024;
    mainbackground_animate[3].h = 720;
    star_animate[0].x = 0;
    star_animate[0].y = 0;
    star_animate[0].w = 100;
    star_animate[0].h = 100;
    star_animate[1].x = 100;
    star_animate[1].y = 0;
    star_animate[1].w = 100;
    star_animate[1].h = 100;
    star_animate[2].x = 200;
    star_animate[2].y = 0;
    star_animate[2].w = 100;
    star_animate[2].h = 100;
    star_animate[3].x = 300;
    star_animate[3].y = 0;
    star_animate[3].w = 100;
    star_animate[3].h = 100;
    star_animate[4].x = 400;
    star_animate[4].y = 0;
    star_animate[4].w = 100;
    star_animate[4].h = 100;
    hero1_pic_animate[0].x = 0;
    hero1_pic_animate[0].y = 0;
    hero1_pic_animate[0].w = 150;
    hero1_pic_animate[0].h = 150;
    hero1_pic_animate[1].x = 150;
    hero1_pic_animate[1].y = 0;
    hero1_pic_animate[1].w = 150;
    hero1_pic_animate[1].h = 150;
    hero2_pic_animate[0].x = 0;
    hero2_pic_animate[0].y = 0;
    hero2_pic_animate[0].w = 150;
    hero2_pic_animate[0].h = 150;
    hero2_pic_animate[1].x = 150;
    hero2_pic_animate[1].y = 0;
    hero2_pic_animate[1].w = 150;
    hero2_pic_animate[1].h = 150;
    hero3_pic_animate[0].x = 0;
    hero3_pic_animate[0].y = 0;
    hero3_pic_animate[0].w = 150;
    hero3_pic_animate[0].h = 150;
    hero3_pic_animate[1].x = 150;
    hero3_pic_animate[1].y = 0;
    hero3_pic_animate[1].w = 150;
    hero3_pic_animate[1].h = 150;
    hero4_pic_animate[0].x = 0;
    hero4_pic_animate[0].y = 0;
    hero4_pic_animate[0].w = 150;
    hero4_pic_animate[0].h = 150;
    hero4_pic_animate[1].x = 150;
    hero4_pic_animate[1].y = 0;
    hero4_pic_animate[1].w = 150;
    hero4_pic_animate[1].h = 150;
    bomb_animate[0].x = 0;
    bomb_animate[0].y = 0;
    bomb_animate[0].w = 100;
    bomb_animate[0].h = 100;
    bomb_animate[1].x = 100;
    bomb_animate[1].y = 0;
    bomb_animate[1].w = 100;
    bomb_animate[1].h = 100;
    bomb_animate[2].x = 200;
    bomb_animate[2].y = 0;
    bomb_animate[2].w = 100;
    bomb_animate[2].h = 100;
    bomb_animate[3].x = 300;
    bomb_animate[3].y = 0;
    bomb_animate[3].w = 100;
    bomb_animate[3].h = 100;
    bomb_animate[4].x = 400;
    bomb_animate[4].y = 0;
    bomb_animate[4].w = 100;
    bomb_animate[4].h = 100;
    bomb_animate[5].x = 500;
    bomb_animate[5].y = 0;
    bomb_animate[5].w = 100;
    bomb_animate[5].h = 100;
    bomb_animate[6].x = 600;
    bomb_animate[6].y = 0;
    bomb_animate[6].w = 100;
    bomb_animate[6].h = 100;
    bomb_animate[7].x = 700;
    bomb_animate[7].y = 0;
    bomb_animate[7].w = 100;
    bomb_animate[7].h = 100;
    wind_arrow_animate[0].x = 0;
    wind_arrow_animate[0].y = 0;
    wind_arrow_animate[0].w = 199;
    wind_arrow_animate[0].h = 75;
    wind_arrow_animate[1].x = 199;
    wind_arrow_animate[1].y = 0;
    wind_arrow_animate[1].w = 199;
    wind_arrow_animate[1].h = 75;
    rock_animate[0].x = 0;
    rock_animate[0].y = 0;
    rock_animate[0].w = 100;
    rock_animate[0].h = 100;
    rock_animate[1].x = 100;
    rock_animate[1].y = 0;
    rock_animate[1].w = 100;
    rock_animate[1].h = 100;
    rock_animate[2].x = 200;
    rock_animate[2].y = 0;
    rock_animate[2].w = 100;
    rock_animate[2].h = 100;
    rock_animate[3].x = 300;
    rock_animate[3].y = 0;
    rock_animate[3].w = 100;
    rock_animate[3].h = 100;
    rock_animate[4].x = 400;
    rock_animate[4].y = 0;
    rock_animate[4].w = 100;
    rock_animate[4].h = 100;
    rock_animate[5].x = 500;
    rock_animate[5].y = 0;
    rock_animate[5].w = 100;
    rock_animate[5].h = 100;
    dynamite_animate[0].x = 0;
    dynamite_animate[0].y = 0;
    dynamite_animate[0].w = 100;
    dynamite_animate[0].h = 100;
    dynamite_animate[1].x = 100;
    dynamite_animate[1].y = 0;
    dynamite_animate[1].w = 100;
    dynamite_animate[1].h = 100;
    dynamite_animate[2].x = 200;
    dynamite_animate[2].y = 0;
    dynamite_animate[2].w = 100;
    dynamite_animate[2].h = 100;
    dynamite_animate[3].x = 300;
    dynamite_animate[3].y = 0;
    dynamite_animate[3].w = 100;
    dynamite_animate[3].h = 100;
    dynamite_animate[4].x = 400;
    dynamite_animate[4].y = 0;
    dynamite_animate[4].w = 100;
    dynamite_animate[4].h = 100;
    dynamite_animate[5].x = 500;
    dynamite_animate[5].y = 0;
    dynamite_animate[5].w = 100;
    dynamite_animate[5].h = 100;
    dynamite_animate[6].x = 600;
    dynamite_animate[6].y = 0;
    dynamite_animate[6].w = 100;
    dynamite_animate[6].h = 100;
    dynamite_animate[7].x = 700;
    dynamite_animate[7].y = 0;
    dynamite_animate[7].w = 100;
    dynamite_animate[7].h = 100;
    potion_animate[0].x = 0;
    potion_animate[0].y = 0;
    potion_animate[0].w = 100;
    potion_animate[0].h = 100;
    potion_animate[1].x = 100;
    potion_animate[1].y = 0;
    potion_animate[1].w = 100;
    potion_animate[1].h = 100;
    potion_animate[2].x = 200;
    potion_animate[2].y = 0;
    potion_animate[2].w = 100;
    potion_animate[2].h = 100;
    potion_animate[3].x = 300;
    potion_animate[3].y = 0;
    potion_animate[3].w = 100;
    potion_animate[3].h = 100;
    shield_gen_animate[0].x = 0;
    shield_gen_animate[0].y = 0;
    shield_gen_animate[0].w = 150;
    shield_gen_animate[0].h = 150;
    shield_gen_animate[1].x = 150;
    shield_gen_animate[1].y = 0;
    shield_gen_animate[1].w = 150;
    shield_gen_animate[1].h = 150;
    shield_gen_animate[2].x = 300;
    shield_gen_animate[2].y = 0;
    shield_gen_animate[2].w = 150;
    shield_gen_animate[2].h = 150;
    shield_gen_animate[3].x = 450;
    shield_gen_animate[3].y = 0;
    shield_gen_animate[3].w = 150;
    shield_gen_animate[3].h = 150;
}
// animate things here

//all position all size here

//all surface and texture here?
SDL_Texture* display_texture = NULL;//display texture is what's going to be a background of game
SDL_Surface* startmenu_surface = NULL;
SDL_Texture* startmenu_texture = NULL;
SDL_Surface* how2play_surface = NULL;
SDL_Texture* how2play_texture = NULL;
SDL_Surface* background_plain_surface = NULL;
SDL_Texture* background_plain_texture = NULL;
SDL_Surface* background_snow_surface = NULL;
SDL_Texture* background_snow_texture = NULL;
SDL_Surface* background_forest_surface = NULL;
SDL_Texture* background_forest_texture = NULL;

SDL_Texture* star_texture = NULL;
SDL_Surface* star_surface = NULL;
SDL_Texture* bomb_texture = NULL;
SDL_Surface* bomb_surface = NULL;
SDL_Texture* shield_gen_texture = NULL;
SDL_Surface* shield_gen_surface = NULL;
SDL_Texture* shield_gen2_texture = NULL;
SDL_Surface* shield_gen2_surface = NULL;
SDL_Texture* shield_gen3_texture = NULL;
SDL_Surface* shield_gen3_surface = NULL;
SDL_Texture* shield_gen4_texture = NULL;
SDL_Surface* shield_gen4_surface = NULL;
SDL_Texture* player1_shield_gen_texture = NULL;
SDL_Texture* player2_shield_gen_texture = NULL;
SDL_Texture* hero1_texture = NULL;
SDL_Surface* hero1_surface = NULL;
SDL_Texture* hero2_texture = NULL;
SDL_Surface* hero2_surface = NULL;
SDL_Texture* hero3_texture = NULL;
SDL_Surface* hero3_surface = NULL;
SDL_Texture* hero4_texture = NULL;
SDL_Surface* hero4_surface = NULL;
SDL_Texture* wind_texture = NULL;
SDL_Surface* wind_surface = NULL;
SDL_Texture* wind_bar_texture = NULL;
SDL_Surface* wind_bar_surface = NULL;
SDL_Texture* arrow_texture = NULL;
SDL_Surface* arrow_surface = NULL;
SDL_Texture* hero1_gun_texture = NULL;
SDL_Surface* hero1_gun_surface = NULL;
SDL_Texture* hero2_gun_texture = NULL;
SDL_Surface* hero2_gun_surface = NULL;
SDL_Texture* hero3_gun_texture = NULL;
SDL_Surface* hero3_gun_surface = NULL;
SDL_Texture* hero4_gun_texture = NULL;
SDL_Surface* hero4_gun_surface = NULL;
SDL_Texture* hp_texture = NULL;
SDL_Surface* hp_surface = NULL;
SDL_Texture* gameend_texture = NULL;
SDL_Surface* gameend_surface = NULL;
SDL_Texture* gameend2_texture = NULL;
SDL_Surface* gameend2_surface = NULL;
SDL_Texture* bg_select_hero_texture = NULL;
SDL_Surface* bg_select_hero_surface = NULL;
SDL_Texture* bg_select_hero2_texture = NULL;
SDL_Surface* bg_select_hero2_surface = NULL;
SDL_Texture* hero1_pic_texture = NULL;
SDL_Surface* hero1_pic_surface = NULL;
SDL_Texture* hero2_pic_texture = NULL;
SDL_Surface* hero2_pic_surface = NULL;
SDL_Texture* hero3_pic_texture = NULL;
SDL_Surface* hero3_pic_surface = NULL;
SDL_Texture* hero4_pic_texture = NULL;
SDL_Surface* hero4_pic_surface = NULL;
SDL_Texture* bullet_texture = NULL;
SDL_Surface* bullet_surface = NULL;
SDL_Texture* choosehero1_texture = NULL;
SDL_Surface* choosehero1_surface = NULL;
SDL_Texture* choosehero2_texture = NULL;
SDL_Surface* choosehero2_surface = NULL;
SDL_Texture* choosehero3_texture = NULL;
SDL_Surface* choosehero3_surface = NULL;
SDL_Texture* choosehero4_texture = NULL;
SDL_Surface* choosehero4_surface = NULL;
SDL_Texture* player1_texture = NULL;
SDL_Texture* player2_texture = NULL;
SDL_Texture* player1_bullet_texture = NULL;
SDL_Texture* player2_bullet_texture = NULL;
SDL_Texture* wind_left_texture = NULL;
SDL_Surface* wind_left_surface = NULL;
SDL_Texture* wind_right_texture = NULL;
SDL_Surface* wind_right_surface = NULL;
SDL_Texture* wind_none_texture = NULL;
SDL_Surface* wind_none_surface = NULL;
SDL_Texture* skill_wind_texture = NULL;
SDL_Surface* skill_wind_surface = NULL;
SDL_Texture* skill_double_texture = NULL;
SDL_Surface* skill_double_surface = NULL;
SDL_Texture* skill_heal_texture = NULL;
SDL_Surface* skill_heal_surface = NULL;
SDL_Texture* skill_split_texture = NULL;
SDL_Surface* skill_split_surface = NULL;
SDL_Surface* skill_block_surface = NULL;
SDL_Texture* skill_block_texture = NULL;
SDL_Surface* skill_orb_surface = NULL;
SDL_Texture* skill_orb_texture = NULL;
SDL_Surface* skill_poison_surface = NULL;
SDL_Texture* skill_poison_texture = NULL;
SDL_Surface* skill_shield_surface = NULL;
SDL_Texture* skill_shield_texture = NULL;
SDL_Texture* player1_skill1_texture = NULL;
SDL_Texture* player2_skill1_texture = NULL;
SDL_Texture* player1_skill2_texture = NULL;
SDL_Texture* player2_skill2_texture = NULL;
SDL_Surface* bar_surface = NULL;
SDL_Texture* bar_texture = NULL;
SDL_Surface* barrier_surface = NULL;
SDL_Texture* barrier_texture = NULL;
SDL_Surface* orb_surface = NULL;
SDL_Texture* orb_texture = NULL;
SDL_Texture* cooldown_11_texture = NULL;
SDL_Texture* cooldown_12_texture = NULL;
SDL_Texture* cooldown_21_texture = NULL;
SDL_Texture* cooldown_22_texture = NULL;
SDL_Surface* num1_surface = NULL;
SDL_Texture* num1_texture = NULL;
SDL_Surface* num2_surface = NULL;
SDL_Texture* num2_texture = NULL;
SDL_Surface* num3_surface = NULL;
SDL_Texture* num3_texture = NULL;
SDL_Surface* numx_surface = NULL;
SDL_Texture* numx_texture = NULL;
SDL_Surface* shield_surface = NULL;
SDL_Texture* shield_texture = NULL;
SDL_Surface* dynamite_surface = NULL;
SDL_Texture* dynamite_texture = NULL;
SDL_Surface* rock_surface = NULL;
SDL_Texture* rock_texture = NULL;
SDL_Surface* potion_surface = NULL;
SDL_Texture* potion_texture = NULL;
SDL_Surface* poison_surface = NULL;
SDL_Texture* poison_texture = NULL;
SDL_Surface* hp_bar_surface = NULL;
SDL_Texture* hp_bar_texture = NULL;
SDL_Surface* shield_bar_surface = NULL;
SDL_Texture* shield_bar_texture = NULL;
SDL_Surface* charge_bar_surface = NULL;
SDL_Texture* charge_bar_texture = NULL;
SDL_Surface* ready_surface = NULL;
SDL_Texture* ready_texture = NULL;
SDL_Surface* ready2_surface = NULL;
SDL_Texture* ready2_texture = NULL;
SDL_Surface* explode_surface = NULL;
SDL_Texture* explode_texture = NULL;
SDL_Surface* poisonbreak_surface = NULL;
SDL_Texture* poisonbreak_texture = NULL;
SDL_Texture* player1_gun_texture = NULL;
SDL_Texture* player2_gun_texture = NULL;
SDL_Surface* small_dynamite_surface = NULL;
SDL_Texture* small_dynamite_texture = NULL;
SDL_Surface* text_surface = NULL;
SDL_Texture* text_texture = NULL;

TTF_Font *gfont = NULL;

// all sound here
Mix_Music* music = NULL;
Mix_Chunk* shootsound = NULL;
Mix_Chunk* player1_hitsound = NULL;
Mix_Chunk* player2_hitsound = NULL;
Mix_Chunk* hero1_hit_sound = NULL;
Mix_Chunk* hero2_hit_sound = NULL;
Mix_Chunk* hero3_hit_sound = NULL;
Mix_Chunk* hero4_hit_sound = NULL;
Mix_Chunk* heal_sound = NULL;
Mix_Chunk* potion_break_sound = NULL;
Mix_Chunk* skillwind_sound = NULL;
// all sound here

//all surface and texture here?

bool game_in_menu = true;// boolean to check that in start menu or not

// all global variable declaration here

//function to start sdl and set something up
bool init()
{
    bool success = true;
    // check if sdl start is error or not
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL init error : %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // do everything that need to start here?
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

        // create window and check if that error or not
        gwindow = SDL_CreateWindow( "Little War", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (gwindow == NULL)
        {
            printf("Window create error : %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // create vsync renderer and check if that error or not
            grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (grenderer == NULL)
            {
                printf("Renderer create error : %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // set start renderer color
                SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);

                // start sdl_ttf or sdl text
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf start error : %s\n", SDL_GetError());
                    success = false;
                }

                // start png loading
                int imgflags = IMG_INIT_PNG;
                if (!( IMG_Init( imgflags ) & imgflags))
                {
                    printf("sdl_image png start error : %s\n", SDL_GetError());
                    success = false;
                }
                // if need to use jpg tiff webp start here

                 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                SDL_SetWindowFullscreen(gwindow, SDL_WINDOW_FULLSCREEN);
            }
        }
    }
    return success;
}

// load picture sound and every resource needed into memory in this function
bool loadmedia()
{
    bool success = true;
    //load everything here
    //load picture for startmenu
    startmenu_surface = IMG_Load("img/startmenu.png");
    if (startmenu_surface == NULL)
    {
        printf("load startmenu.png failed %s\n", IMG_GetError());
        success = false;
    }
    startmenu_texture = SDL_CreateTextureFromSurface(grenderer, startmenu_surface);
    //load picture for how to  play
    how2play_surface = IMG_Load("img/how2play.png");
    if (how2play_surface == NULL)
    {
        printf("load how2play.png failed %s\n", IMG_GetError());
        success = false;
    }
    how2play_texture = SDL_CreateTextureFromSurface(grenderer, how2play_surface);

    background_plain_surface = IMG_Load("img/bg_plain.png");
    if (background_plain_surface == NULL)
    {
        printf("load bg_plain.png failed %s\n", IMG_GetError());
        success = false;
    }
    background_plain_texture = SDL_CreateTextureFromSurface(grenderer, background_plain_surface);

    background_snow_surface = IMG_Load("img/bg_snow.png");
    if (background_snow_surface == NULL)
    {
        printf("load bg_snow.png failed %s\n", IMG_GetError());
        success = false;
    }
    background_snow_texture = SDL_CreateTextureFromSurface(grenderer, background_snow_surface);

    background_forest_surface = IMG_Load("img/bg_forest.png");
    if (background_forest_surface == NULL)
    {
        printf("load bg_forest.png failed %s\n", IMG_GetError());
        success = false;
    }
    background_forest_texture = SDL_CreateTextureFromSurface(grenderer, background_forest_surface);

    star_surface = IMG_Load("img/star.png");
    if (star_surface == NULL)
    {
        printf("load star.png failed %s\n", IMG_GetError());
        success = false;
    }
    star_texture = SDL_CreateTextureFromSurface(grenderer, star_surface);

    bomb_surface = IMG_Load("img/bomb.png");
    if (bomb_surface == NULL)
    {
        printf("load bomb.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( bomb_surface, SDL_TRUE, SDL_MapRGB( bomb_surface->format, 0, 0xFF, 0xFF ) );
    bomb_texture = SDL_CreateTextureFromSurface(grenderer, bomb_surface);

    shield_gen_surface = IMG_Load("img/shield_gen.png");
    if (shield_gen_surface == NULL)
    {
        printf("load shield_gen.png failed %s\n", IMG_GetError());
        success = false;
    }
    shield_gen_texture = SDL_CreateTextureFromSurface(grenderer, shield_gen_surface);

    shield_gen2_surface = IMG_Load("img/shield_gen2.png");
    if (shield_gen2_surface == NULL)
    {
        printf("load shield_gen2.png failed %s\n", IMG_GetError());
        success = false;
    }
    shield_gen2_texture = SDL_CreateTextureFromSurface(grenderer, shield_gen2_surface);

    shield_gen3_surface = IMG_Load("img/shield_gen3.png");
    if (shield_gen3_surface == NULL)
    {
        printf("load shield_gen3.png failed %s\n", IMG_GetError());
        success = false;
    }
    shield_gen3_texture = SDL_CreateTextureFromSurface(grenderer, shield_gen3_surface);

    shield_gen4_surface = IMG_Load("img/shield_gen4.png");
    if (shield_gen4_surface == NULL)
    {
        printf("load shield_gen4.png failed %s\n", IMG_GetError());
        success = false;
    }
    shield_gen4_texture = SDL_CreateTextureFromSurface(grenderer, shield_gen4_surface);

    hero1_surface = IMG_Load("img/hero1.png");
    if (hero1_surface == NULL)
    {
        printf("load hero1.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero1_surface, SDL_TRUE, SDL_MapRGB( hero1_surface->format, 0x80, 0xFF, 0xFF ) );
    hero1_texture = SDL_CreateTextureFromSurface(grenderer, hero1_surface);

    hero2_surface = IMG_Load("img/hero2.png");
    if (hero2_surface == NULL)
    {
        printf("load hero2.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero2_surface, SDL_TRUE, SDL_MapRGB( hero2_surface->format, 0x80, 0xFF, 0xFF ) );
    hero2_texture = SDL_CreateTextureFromSurface(grenderer, hero2_surface);

    hero3_surface = IMG_Load("img/hero3.png");
    if (hero3_surface == NULL)
    {
        printf("load hero3.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero3_surface, SDL_TRUE, SDL_MapRGB( hero3_surface->format, 0x80, 0xFF, 0xFF ) );
    hero3_texture = SDL_CreateTextureFromSurface(grenderer, hero3_surface);

    hero4_surface = IMG_Load("img/hero4.png");
    if (hero4_surface == NULL)
    {
        printf("load hero4.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero4_surface, SDL_TRUE, SDL_MapRGB( hero4_surface->format, 0x80, 0xFF, 0xFF ) );
    hero4_texture = SDL_CreateTextureFromSurface(grenderer, hero4_surface);

    wind_bar_surface = IMG_Load("img/wind_bar.png");
    if (wind_bar_surface == NULL)
    {
        printf("load wind_bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    wind_bar_texture = SDL_CreateTextureFromSurface(grenderer, wind_bar_surface);

    wind_left_surface = IMG_Load("img/wind_left.png");
    if (wind_left_surface == NULL)
    {
        printf("load wind_left.png failed %s\n", IMG_GetError());
        success = false;
    }
    wind_left_texture = SDL_CreateTextureFromSurface(grenderer, wind_left_surface);

    wind_right_surface = IMG_Load("img/wind_right.png");
    if (wind_right_surface == NULL)
    {
        printf("load wind_right.png failed %s\n", IMG_GetError());
        success = false;
    }
    wind_right_texture = SDL_CreateTextureFromSurface(grenderer, wind_right_surface);

    wind_none_surface = IMG_Load("img/wind_none.png");
    if (wind_none_surface == NULL)
    {
        printf("load wind_none.png failed %s\n", IMG_GetError());
        success = false;
    }
    wind_none_texture = SDL_CreateTextureFromSurface(grenderer, wind_none_surface);

    wind_surface = IMG_Load("img/wind.png");
    if (wind_surface == NULL)
    {
        printf("load wind.png failed %s\n", IMG_GetError());
        success = false;
    }
    wind_texture = SDL_CreateTextureFromSurface(grenderer, wind_surface);

    hp_surface = IMG_Load("img/hp.png");
    if (hp_surface == NULL)
    {
        printf("load hp.png failed %s\n", IMG_GetError());
        success = false;
    }
    hp_texture = SDL_CreateTextureFromSurface(grenderer, hp_surface);

    gameend_surface = IMG_Load("img/gameover.png");
    if (gameend_surface == NULL)
    {
        printf("load gameover.png failed %s\n", IMG_GetError());
        success = false;
    }
    gameend_texture = SDL_CreateTextureFromSurface(grenderer, gameend_surface);

    gameend2_surface = IMG_Load("img/gameover2.png");
    if (gameend2_surface == NULL)
    {
        printf("load gameover2.png failed %s\n", IMG_GetError());
        success = false;
    }
    gameend2_texture = SDL_CreateTextureFromSurface(grenderer, gameend2_surface);

    bg_select_hero_surface = IMG_Load("img/selecthero.png");
    if (bg_select_hero_surface == NULL)
    {
        printf("load selecthero.png failed %s\n", IMG_GetError());
        success = false;
    }
    bg_select_hero_texture = SDL_CreateTextureFromSurface(grenderer, bg_select_hero_surface);

    bg_select_hero2_surface = IMG_Load("img/selecthero2.png");
    if (bg_select_hero2_surface == NULL)
    {
        printf("load selecthero2.png failed %s\n", IMG_GetError());
        success = false;
    }
    bg_select_hero2_texture = SDL_CreateTextureFromSurface(grenderer, bg_select_hero2_surface);

    hero1_pic_surface = IMG_Load("img/hero1_pic.png");
    if (hero1_pic_surface == NULL)
    {
        printf("load hero1_pic.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero1_pic_surface, SDL_TRUE, SDL_MapRGB( hero1_pic_surface->format, 0x80, 0xFF, 0xFF ) );
    hero1_pic_texture = SDL_CreateTextureFromSurface(grenderer, hero1_pic_surface);

    hero3_pic_surface = IMG_Load("img/hero3_pic.png");
    if (hero3_pic_surface == NULL)
    {
        printf("load hero3_pic.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero3_pic_surface, SDL_TRUE, SDL_MapRGB( hero3_pic_surface->format, 0x80, 0xFF, 0xFF ) );
    hero3_pic_texture = SDL_CreateTextureFromSurface(grenderer, hero3_pic_surface);

    hero2_pic_surface = IMG_Load("img/hero2_pic.png");
    if (hero2_pic_surface == NULL)
    {
        printf("load hero2_pic.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero2_pic_surface, SDL_TRUE, SDL_MapRGB( hero2_pic_surface->format, 0x80, 0xFF, 0xFF ) );
    hero2_pic_texture = SDL_CreateTextureFromSurface(grenderer, hero2_pic_surface);

    hero4_pic_surface = IMG_Load("img/hero4_pic.png");
    if (hero4_pic_surface == NULL)
    {
        printf("load hero4_pic.png failed %s\n", IMG_GetError());
        success = false;
    }
    SDL_SetColorKey( hero4_pic_surface, SDL_TRUE, SDL_MapRGB( hero4_pic_surface->format, 0x80, 0xFF, 0xFF ) );
    hero4_pic_texture = SDL_CreateTextureFromSurface(grenderer, hero4_pic_surface);

    choosehero1_surface = IMG_Load("img/choosehero1.png");
    if (choosehero1_surface == NULL)
    {
        printf("load choosehero1.png failed %s\n", IMG_GetError());
        success = false;
    }
    choosehero1_texture = SDL_CreateTextureFromSurface(grenderer, choosehero1_surface);

    choosehero2_surface = IMG_Load("img/choosehero2.png");
    if (choosehero2_surface == NULL)
    {
        printf("load choosehero2.png failed %s\n", IMG_GetError());
        success = false;
    }
    choosehero2_texture = SDL_CreateTextureFromSurface(grenderer, choosehero2_surface);

    choosehero3_surface = IMG_Load("img/choosehero3.png");
    if (choosehero3_surface == NULL)
    {
        printf("load choosehero3.png failed %s\n", IMG_GetError());
        success = false;
    }
    choosehero3_texture = SDL_CreateTextureFromSurface(grenderer, choosehero3_surface);

    choosehero4_surface = IMG_Load("img/choosehero4.png");
    if (choosehero4_surface == NULL)
    {
        printf("load choosehero4.png failed %s\n", IMG_GetError());
        success = false;
    }
    choosehero4_texture = SDL_CreateTextureFromSurface(grenderer, choosehero4_surface);

    skill_wind_surface = IMG_Load("img/skill_wind.png");
    if (skill_wind_surface == NULL)
    {
        printf("load skill_wind.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_wind_texture = SDL_CreateTextureFromSurface(grenderer, skill_wind_surface);

    skill_heal_surface = IMG_Load("img/skill_heal.png");
    if (skill_heal_surface == NULL)
    {
        printf("load skill_heal.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_heal_texture = SDL_CreateTextureFromSurface(grenderer, skill_heal_surface);

    skill_double_surface = IMG_Load("img/skill_double.png");
    if (skill_double_surface == NULL)
    {
        printf("load skill_double.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_double_texture = SDL_CreateTextureFromSurface(grenderer, skill_double_surface);

    skill_block_surface = IMG_Load("img/skill_block.png");
    if (skill_block_surface == NULL)
    {
        printf("load skill_block.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_block_texture = SDL_CreateTextureFromSurface(grenderer, skill_block_surface);

    skill_poison_surface = IMG_Load("img/skill_poison.png");
    if (skill_poison_surface == NULL)
    {
        printf("load skill_poison.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_poison_texture = SDL_CreateTextureFromSurface(grenderer, skill_poison_surface);

    skill_shield_surface = IMG_Load("img/skill_shield.png");
    if (skill_shield_surface == NULL)
    {
        printf("load skill_shield.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_shield_texture = SDL_CreateTextureFromSurface(grenderer, skill_shield_surface);

    skill_orb_surface = IMG_Load("img/skill_orb.png");
    if (skill_orb_surface == NULL)
    {
        printf("load skill_orb.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_orb_texture = SDL_CreateTextureFromSurface(grenderer, skill_orb_surface);

    skill_split_surface = IMG_Load("img/skill_split.png");
    if (skill_split_surface == NULL)
    {
        printf("load skill_split.png failed %s\n", IMG_GetError());
        success = false;
    }
    skill_split_texture = SDL_CreateTextureFromSurface(grenderer, skill_split_surface);

    bar_surface = IMG_Load("img/bar.png");
    if (bar_surface == NULL)
    {
        printf("load bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    bar_texture = SDL_CreateTextureFromSurface(grenderer, bar_surface);

    barrier_surface = IMG_Load("img/barrier.png");
    if (barrier_surface == NULL)
    {
        printf("load barrier.png failed %s\n", IMG_GetError());
        success = false;
    }
    barrier_texture = SDL_CreateTextureFromSurface(grenderer, barrier_surface);

    orb_surface = IMG_Load("img/orb.png");
    if (barrier_surface == NULL)
    {
        printf("load orb.png failed %s\n", IMG_GetError());
        success = false;
    }
    orb_texture = SDL_CreateTextureFromSurface(grenderer, orb_surface);

    num1_surface = IMG_Load("img/num1.png");
    if (num1_surface == NULL)
    {
        printf("load num1.png failed %s\n", IMG_GetError());
        success = false;
    }
    num1_texture = SDL_CreateTextureFromSurface(grenderer, num1_surface);

    num2_surface = IMG_Load("img/num2.png");
    if (num2_surface == NULL)
    {
        printf("load num2.png failed %s\n", IMG_GetError());
        success = false;
    }
    num2_texture = SDL_CreateTextureFromSurface(grenderer, num2_surface);

    num3_surface = IMG_Load("img/num3.png");
    if (num3_surface == NULL)
    {
        printf("load num3.png failed %s\n", IMG_GetError());
        success = false;
    }
    num3_texture = SDL_CreateTextureFromSurface(grenderer, num3_surface);

    numx_surface = IMG_Load("img/numx.png");
    if (numx_surface == NULL)
    {
        printf("load numx.png failed %s\n", IMG_GetError());
        success = false;
    }
    numx_texture = SDL_CreateTextureFromSurface(grenderer, numx_surface);

    shield_surface = IMG_Load("img/shield.png");
    if (shield_surface == NULL)
    {
        printf("load shield.png failed %s\n", IMG_GetError());
        success = false;
    }
    shield_texture = SDL_CreateTextureFromSurface(grenderer, shield_surface);

    dynamite_surface = IMG_Load("img/dynamite.png");
    if (dynamite_surface == NULL)
    {
        printf("load dynamite.png failed %s\n", IMG_GetError());
        success = false;
    }
    dynamite_texture = SDL_CreateTextureFromSurface(grenderer, dynamite_surface);

    rock_surface = IMG_Load("img/rock.png");
    if (rock_surface == NULL)
    {
        printf("load rock.png failed %s\n", IMG_GetError());
        success = false;
    }
    rock_texture = SDL_CreateTextureFromSurface(grenderer, rock_surface);

    potion_surface = IMG_Load("img/potion.png");
    if (potion_surface == NULL)
    {
        printf("load potion.png failed %s\n", IMG_GetError());
        success = false;
    }
    potion_texture = SDL_CreateTextureFromSurface(grenderer, potion_surface);

    poison_surface = IMG_Load("img/poison.png");
    if (poison_surface == NULL)
    {
        printf("load poison.png failed %s\n", IMG_GetError());
        success = false;
    }
    poison_texture = SDL_CreateTextureFromSurface(grenderer, poison_surface);

    poisonbreak_surface = IMG_Load("img/poison_break.png");
    if (poisonbreak_surface == NULL)
    {
        printf("load poison_break.png failed %s\n", IMG_GetError());
        success = false;
    }
    poisonbreak_texture = SDL_CreateTextureFromSurface(grenderer, poisonbreak_surface);

    hp_bar_surface = IMG_Load("img/hp_bar.png");
    if (hp_bar_surface == NULL)
    {
        printf("load hp_bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    hp_bar_texture = SDL_CreateTextureFromSurface(grenderer, hp_bar_surface);

    shield_bar_surface = IMG_Load("img/shield_bar.png");
    if (shield_bar_surface == NULL)
    {
        printf("load shield_bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    shield_bar_texture = SDL_CreateTextureFromSurface(grenderer, shield_bar_surface);

    charge_bar_surface = IMG_Load("img/charge_bar.png");
    if (charge_bar_surface == NULL)
    {
        printf("load charge_bar.png failed %s\n", IMG_GetError());
        success = false;
    }
    charge_bar_texture = SDL_CreateTextureFromSurface(grenderer, charge_bar_surface);

    ready_surface = IMG_Load("img/ready.png");
    if (ready_surface == NULL)
    {
        printf("load ready.png failed %s\n", IMG_GetError());
        success = false;
    }
    ready_texture = SDL_CreateTextureFromSurface(grenderer, ready_surface);

    ready2_surface = IMG_Load("img/ready2.png");
    if (ready2_surface == NULL)
    {
        printf("load ready2.png failed %s\n", IMG_GetError());
        success = false;
    }
    ready2_texture = SDL_CreateTextureFromSurface(grenderer, ready2_surface);

    explode_surface = IMG_Load("img/explode.png");
    if (explode_surface == NULL)
    {
        printf("load explode.png failed %s\n", IMG_GetError());
        success = false;
    }
    explode_texture = SDL_CreateTextureFromSurface(grenderer, explode_surface);

    hero1_gun_surface = IMG_Load("img/hero1_gun.png");
    if (hero1_gun_surface == NULL)
    {
        printf("load hero1_gun.png failed %s\n", IMG_GetError());
        success = false;
    }
    hero1_gun_texture = SDL_CreateTextureFromSurface(grenderer, hero1_gun_surface);

    hero2_gun_surface = IMG_Load("img/hero2_gun.png");
    if (hero2_gun_surface == NULL)
    {
        printf("load hero2_gun.png failed %s\n", IMG_GetError());
        success = false;
    }
    hero2_gun_texture = SDL_CreateTextureFromSurface(grenderer, hero2_gun_surface);

    hero3_gun_surface = IMG_Load("img/hero3_gun.png");
    if (hero1_gun_surface == NULL)
    {
        printf("load hero3_gun.png failed %s\n", IMG_GetError());
        success = false;
    }
    hero3_gun_texture = SDL_CreateTextureFromSurface(grenderer, hero3_gun_surface);

    hero4_gun_surface = IMG_Load("img/hero4_gun.png");
    if (hero1_gun_surface == NULL)
    {
        printf("load hero4_gun.png failed %s\n", IMG_GetError());
        success = false;
    }
    hero4_gun_texture = SDL_CreateTextureFromSurface(grenderer, hero4_gun_surface);

    small_dynamite_surface = IMG_Load("img/small_dynamite.png");
    if (small_dynamite_surface == NULL)
    {
        printf("load small_dynamite.png failed %s\n", IMG_GetError());
        success = false;
    }
    small_dynamite_texture = SDL_CreateTextureFromSurface(grenderer, small_dynamite_surface);

    // load picture

    gfont = TTF_OpenFont( "font.TTF", 28 );
    if( gfont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    //set collider
    set_collider();

    shootsound = Mix_LoadWAV( "sound/019.wav" );
    if( shootsound == NULL )
    {
        printf( "load 019.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    hero1_hit_sound = Mix_LoadWAV( "sound/023.wav" );
    if( hero1_hit_sound == NULL )
    {
        printf( "load 023.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    hero2_hit_sound = Mix_LoadWAV( "sound/020.wav" );
    if( hero2_hit_sound == NULL )
    {
        printf( "load 020.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    hero3_hit_sound = Mix_LoadWAV( "sound/089.wav" );
    if( hero3_hit_sound == NULL )
    {
        printf( "load 089.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    hero4_hit_sound = Mix_LoadWAV( "sound/explosion4.ogg" );
    if( hero4_hit_sound == NULL )
    {
        printf( "load explosion4.ogg failed %s\n", Mix_GetError() );
        success = false;
    }

    heal_sound = Mix_LoadWAV( "sound/049.wav" );
    if( heal_sound == NULL )
    {
        printf( "load 049.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    potion_break_sound = Mix_LoadWAV( "sound/065.wav" );
    if( potion_break_sound == NULL )
    {
        printf( "load 065.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    skillwind_sound = Mix_LoadWAV( "sound/wind8.ogg" );
    if( skillwind_sound == NULL )
    {
        printf( "load wind8.wav failed %s\n", Mix_GetError() );
        success = false;
    }

    music = Mix_LoadMUS("sound/airship.mid");
    if (music == NULL)
    {
        printf(" load airship.mid failed %s\n", Mix_GetError());
        success = false;
    }

    setanimation();
    return success;

}

// close, quit and free all memory
void close()
{
    // free all memory and loaded media here
    SDL_FreeSurface(startmenu_surface);
    SDL_DestroyTexture(startmenu_texture);
    SDL_FreeSurface(how2play_surface);
    SDL_DestroyTexture(how2play_texture);
    SDL_DestroyTexture(display_texture);
    SDL_DestroyRenderer(grenderer);
    SDL_DestroyWindow(gwindow);
    SDL_FreeSurface(background_plain_surface);
    SDL_DestroyTexture(background_plain_texture);
    SDL_FreeSurface(background_snow_surface);
    SDL_DestroyTexture(background_snow_texture);

    SDL_FreeSurface(choosehero1_surface);
    SDL_DestroyTexture(choosehero1_texture);
    SDL_FreeSurface(choosehero2_surface);
    SDL_DestroyTexture(choosehero2_texture);
    SDL_FreeSurface(choosehero3_surface);
    SDL_DestroyTexture(choosehero3_texture);
    SDL_FreeSurface(choosehero4_surface);
    SDL_DestroyTexture(choosehero4_texture);
    SDL_FreeSurface(star_surface);
    SDL_DestroyTexture(star_texture);
    SDL_FreeSurface(hero1_surface);
    SDL_DestroyTexture(hero1_texture);
    SDL_FreeSurface(hero2_surface);
    SDL_DestroyTexture(hero2_texture);
    SDL_FreeSurface(hero3_surface);
    SDL_DestroyTexture(hero3_texture);
    SDL_FreeSurface(hero4_surface);
    SDL_DestroyTexture(hero4_texture);
    SDL_FreeSurface(shield_gen_surface);
    SDL_DestroyTexture(shield_gen_texture);
    SDL_FreeSurface(wind_surface);
    SDL_DestroyTexture(wind_texture);
    SDL_FreeSurface(arrow_surface);
    SDL_DestroyTexture(arrow_texture);
    SDL_FreeSurface(hp_surface);
    SDL_DestroyTexture(hp_texture);
    SDL_FreeSurface(hero2_pic_surface);
    SDL_DestroyTexture(hero2_pic_texture);
    SDL_FreeSurface(hero3_pic_surface);
    SDL_DestroyTexture(hero3_pic_texture);
    SDL_FreeSurface(hero1_pic_surface);
    SDL_DestroyTexture(hero1_pic_texture);
    SDL_FreeSurface(hero4_pic_surface);
    SDL_DestroyTexture(hero4_pic_texture);
    SDL_FreeSurface(bg_select_hero_surface);
    SDL_DestroyTexture(bg_select_hero_texture);
    SDL_FreeSurface(gameend_surface);
    SDL_DestroyTexture(gameend_texture);
    SDL_FreeSurface(gameend2_surface);
    SDL_DestroyTexture(gameend2_texture);
    SDL_FreeSurface(bullet_surface);
    SDL_DestroyTexture(bullet_texture);
    SDL_DestroyTexture(player1_texture);
    SDL_DestroyTexture(player2_texture);
    SDL_DestroyTexture(player1_bullet_texture);
    SDL_DestroyTexture(player2_bullet_texture);
    SDL_FreeSurface(skill_wind_surface);
    SDL_DestroyTexture(skill_wind_texture);
    SDL_FreeSurface(skill_heal_surface);
    SDL_DestroyTexture(skill_heal_texture);
    SDL_FreeSurface(skill_double_surface);
    SDL_DestroyTexture(skill_double_texture);
    SDL_FreeSurface(skill_split_surface);
    SDL_DestroyTexture(skill_split_texture);
    SDL_DestroyTexture(player1_skill1_texture);
    SDL_DestroyTexture(player2_skill1_texture);
    SDL_DestroyTexture(player1_skill2_texture);
    SDL_DestroyTexture(player2_skill2_texture);
    SDL_FreeSurface(bar_surface);
    SDL_DestroyTexture(bar_texture);
    SDL_FreeSurface(barrier_surface);
    SDL_DestroyTexture(barrier_texture);
    SDL_FreeSurface(skill_block_surface);
    SDL_DestroyTexture(skill_block_texture);
    SDL_FreeSurface(skill_orb_surface);
    SDL_DestroyTexture(skill_orb_texture);
    SDL_FreeSurface(num1_surface);
    SDL_DestroyTexture(num1_texture);
    SDL_FreeSurface(num2_surface);
    SDL_DestroyTexture(num2_texture);
    SDL_FreeSurface(num3_surface);
    SDL_DestroyTexture(num3_texture);
    SDL_FreeSurface(numx_surface);
    SDL_DestroyTexture(numx_texture);
    SDL_DestroyTexture(cooldown_11_texture);
    SDL_DestroyTexture(cooldown_12_texture);
    SDL_DestroyTexture(cooldown_21_texture);
    SDL_DestroyTexture(cooldown_22_texture);
    SDL_FreeSurface(shield_surface);
    SDL_DestroyTexture(shield_texture);
    SDL_FreeSurface(dynamite_surface);
    SDL_DestroyTexture(dynamite_texture);
    SDL_FreeSurface(rock_surface);
    SDL_DestroyTexture(rock_texture);
    SDL_FreeSurface(potion_surface);
    SDL_DestroyTexture(potion_texture);
    SDL_FreeSurface(poison_surface);
    SDL_DestroyTexture(poison_texture);
    SDL_FreeSurface(hp_bar_surface);
    SDL_DestroyTexture(hp_bar_texture);
    SDL_FreeSurface(shield_bar_surface);
    SDL_DestroyTexture(shield_bar_texture);
    SDL_FreeSurface(charge_bar_surface);
    SDL_DestroyTexture(charge_bar_texture);
    SDL_FreeSurface(ready_surface);
    SDL_DestroyTexture(ready_texture);
    SDL_FreeSurface(ready2_surface);
    SDL_DestroyTexture(ready2_texture);
    SDL_FreeSurface(wind_bar_surface);
    SDL_DestroyTexture(wind_bar_texture);
    SDL_FreeSurface(explode_surface);
    SDL_DestroyTexture(explode_texture);
    SDL_FreeSurface(poisonbreak_surface);
    SDL_DestroyTexture(poisonbreak_texture);
    SDL_FreeSurface(hero1_gun_surface);
    SDL_DestroyTexture(hero1_gun_texture);
    SDL_FreeSurface(hero2_gun_surface);
    SDL_DestroyTexture(hero2_gun_texture);
    SDL_FreeSurface(hero3_gun_surface);
    SDL_DestroyTexture(hero3_gun_texture);
    SDL_FreeSurface(hero4_gun_surface);
    SDL_DestroyTexture(hero4_gun_texture);
    SDL_DestroyTexture(player1_gun_texture);
    SDL_DestroyTexture(player2_gun_texture);
    SDL_DestroyTexture(player1_shield_gen_texture);
    SDL_DestroyTexture(player2_shield_gen_texture);
    SDL_FreeSurface(shield_gen2_surface);
    SDL_DestroyTexture(shield_gen2_texture);
    SDL_FreeSurface(shield_gen3_surface);
    SDL_DestroyTexture(shield_gen3_texture);
    SDL_FreeSurface(shield_gen4_surface);
    SDL_DestroyTexture(shield_gen4_texture);
    SDL_FreeSurface(small_dynamite_surface);
    SDL_DestroyTexture(small_dynamite_texture);

    Mix_FreeChunk(shootsound);
    shootsound = NULL;
    Mix_FreeChunk(player1_hitsound);
    player1_hitsound = NULL;
    Mix_FreeChunk(player2_hitsound);
    player2_hitsound = NULL;
    Mix_FreeChunk(hero1_hit_sound);
    hero1_hit_sound = NULL;
    Mix_FreeChunk(hero2_hit_sound);
    hero2_hit_sound = NULL;
    Mix_FreeChunk(hero3_hit_sound);
    hero3_hit_sound = NULL;
    Mix_FreeChunk(hero4_hit_sound);
    hero4_hit_sound = NULL;
    Mix_FreeChunk(heal_sound);
    heal_sound = NULL;
    Mix_FreeChunk(potion_break_sound);
    potion_break_sound = NULL;
    Mix_FreeChunk(skillwind_sound);
    skillwind_sound = NULL;
    Mix_FreeMusic(music);
    music = NULL;

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    gfont = NULL;

    gwindow = NULL;
    grenderer = NULL;

    //quit all subsystems
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

void skill_wind(SDL_Event e)
{
   if (e.key.keysym.sym == SDLK_q && !skillwind)
    {
        if (current_player == 1 && player1_skill1_cooldown <= 0)
        {
            skillwind_target = -1;
            player1_skill1_cooldown = player1_skill1_max_cooldown;
            skillwind = true;
            Mix_PlayChannel(-1, skillwind_sound, 0);
        }
        else if (current_player == -1 && player2_skill1_cooldown <= 0)
        {
            skillwind_target = 1;
            player2_skill1_cooldown = player2_skill1_max_cooldown;
            skillwind = true;
            Mix_PlayChannel(-1, skillwind_sound, 0);
        }
    }
}

void skill_double(SDL_Event e)
{
    if (e.key.keysym.sym == SDLK_q && !skilldouble)
    {
        if (current_player == 1 && player1_skill1_cooldown <= 0)
        {
            skilldouble = true;
            player1_skill1_cooldown = player1_skill1_max_cooldown;
        }
        else if (current_player == -1 && player2_skill1_cooldown <= 0)
        {
            skilldouble = true;
            player2_skill1_cooldown = player2_skill1_max_cooldown;
        }
    }
}

void skill_heal(SDL_Event e)
{
    if (current_player == 1 && player1_skill1_cooldown <= 0 && e.key.keysym.sym == SDLK_q)
    {
        player1_skill1_cooldown = player1_skill1_max_cooldown;
        player1hp += 20;
        if (player1hp > 250)
        {
            player1hp = 250;
        }
        Mix_PlayChannel(-1, heal_sound, 0);
    }
    if (current_player == -1 && player2_skill1_cooldown <= 0 && e.key.keysym.sym == SDLK_q)
    {
        player2_skill1_cooldown = player2_skill1_max_cooldown;
        player2hp += 20;
        if (player2hp > 250)
        {
            player2hp = 250;
        }
        Mix_PlayChannel(-1, heal_sound, 0);
    }
}

void skill_split(SDL_Event e)
{
    if (current_player == 1 && player1_skill1_cooldown <= 0 && e.key.keysym.sym == SDLK_q)
    {
        skillsplit = true;
        split_start = true;
        player1_skill1_cooldown = player1_skill1_max_cooldown;
    }
    if (current_player == -1 && player2_skill1_cooldown <= 0 && e.key.keysym.sym == SDLK_q)
    {
        skillsplit = true;
        split_start = true;
        player2_skill1_cooldown = player2_skill1_max_cooldown;
    }
}

void skill_block(SDL_Event e)
{
    if (current_player == 1 && player1_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillblock_target = -1;
        player1_atk *= 1.5;
        player1_skill2_cooldown = player1_skill2_max_cooldown;
        skillblock = true;
    }
    else if (current_player == -1 && player2_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillblock_target = 1;
        player2_atk *= 1.5;
        player2_skill2_cooldown = player2_skill2_max_cooldown;
        skillblock = true;
    }
}

void skill_poison(SDL_Event e)
{
    if (current_player == 1 && player1_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillpoison_target = -1;
        player1_atk *= 0.5;
        player1_skill2_cooldown = player1_skill2_max_cooldown;
        bullet_texture = poison_texture;
        bullet_max_frame = 8;
        player1_hitsound = potion_break_sound;
        for (int i=0; i < bullet_max_frame; ++i)
        {
            bullet_animate[i].x = bomb_animate[i].x;
            bullet_animate[i].y = bomb_animate[i].y;
            bullet_animate[i].w = bomb_animate[i].w;
            bullet_animate[i].h = bomb_animate[i].h;
        }
        skillpoison = true;
    }
    else if (current_player == -1 && player2_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillpoison_target = 1;
        player2_atk *= 0.5;
        player2_skill2_cooldown = player2_skill2_max_cooldown;
        bullet_texture = poison_texture;
        bullet_max_frame = 8;
        player2_hitsound = potion_break_sound;
        for (int i=0; i < bullet_max_frame; ++i)
        {
            bullet_animate[i].x = bomb_animate[i].x;
            bullet_animate[i].y = bomb_animate[i].y;
            bullet_animate[i].w = bomb_animate[i].w;
            bullet_animate[i].h = bomb_animate[i].h;
        }
        skillpoison = true;
    }
}

void skill_orb(SDL_Event e)
{
    if (current_player == 1 && player1_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillorb = true;
        orb_size[0].x = 0;
        orb_size[0].y = 300;
        orb_size[0].w = 20;
        orb_size[0].h = 20;
        orb1_sx = 7;
        orb1_sy = 0;
        orb_size[1].x = 200;
        orb_size[1].y = 300;
        orb_size[1].w = 20;
        orb_size[1].h = 20;
        orb2_sx = 0;
        orb2_sy = 7;
        orb_size[2].x = 0;
        orb_size[2].y = 555;
        orb_size[2].w = 20;
        orb_size[2].h = 20;
        orb3_sx = 0;
        orb3_sy = -7;
        orb_size[3].x = 200;
        orb_size[3].y = 555;
        orb_size[3].w = 20;
        orb_size[3].h = 20;
        orb4_sx = -7;
        orb4_sy = 0;
        orb_top = 300;
        orb_bottom = 555;
        orb_left = 0;
        orb_right = 200;
        player1_skill2_cooldown = player1_skill2_max_cooldown;
    }
    else if (current_player == -1 && player2_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillorb = true;
        orb_size[0].x = 800;
        orb_size[0].y = 300;
        orb_size[0].w = 20;
        orb_size[0].h = 20;
        orb1_sx = 4;
        orb1_sy = 0;
        orb_size[1].x = 1004;
        orb_size[1].y = 300;
        orb_size[1].w = 20;
        orb_size[1].h = 20;
        orb2_sx = 0;
        orb2_sy = 4;
        orb_size[2].x = 800;
        orb_size[2].y = 555;
        orb_size[2].w = 20;
        orb_size[2].h = 20;
        orb3_sx = 0;
        orb3_sy = -4;
        orb_size[3].x = 1004;
        orb_size[3].y = 555;
        orb_size[3].w = 20;
        orb_size[3].h = 20;
        orb4_sx = -4;
        orb4_sy = 0;
        orb_top = 300;
        orb_bottom = 555;
        orb_left = 800;
        orb_right = 1004;
        player2_skill2_cooldown = player2_skill2_max_cooldown;
    }
}

void move_orb()
{
    if (orb_size[0].x <= orb_left && orb_size[0].y >= orb_bottom)
    {
        orb1_sx = 0;
        orb1_sy = -7;
    }
    else if (orb_size[0].x >= orb_right && orb_size[0].y <= orb_top)
    {
        orb1_sx = 0;
        orb1_sy = 7;
    }
    else if (orb_size[0].y >= orb_bottom && orb_size[0].x >= orb_right)
    {
        orb1_sx = -7;
        orb1_sy = 0;
    }
    else if (orb_size[0].y <= orb_top && orb_size[0].x <= orb_left)
    {
        orb1_sx = 7;
        orb1_sy = 0;
    }
    if (orb_size[1].x <= orb_left && orb_size[1].y >= orb_bottom)
    {
        orb2_sx = 0;
        orb2_sy = -7;
    }
    else if (orb_size[1].x >= orb_right && orb_size[1].y <= orb_top)
    {
        orb2_sx = 0;
        orb2_sy = 7;
    }
    else if (orb_size[1].y >= orb_bottom && orb_size[1].x >= orb_right)
    {
        orb2_sx = -7;
        orb2_sy = 0;
    }
    else if (orb_size[1].y <= orb_top && orb_size[1].x <= orb_left)
    {
        orb2_sx = 7;
        orb2_sy = 0;
    }
    if (orb_size[2].x <= orb_left && orb_size[2].y >= orb_bottom)
    {
        orb3_sx = 0;
        orb3_sy = -7;
    }
    else if (orb_size[2].x >= orb_right && orb_size[2].y <= orb_top)
    {
        orb3_sx = 0;
        orb3_sy = 7;
    }
    else if (orb_size[2].y >= orb_bottom && orb_size[2].x >= orb_right)
    {
        orb3_sx = -7;
        orb3_sy = 0;
    }
    else if (orb_size[2].y <= orb_top && orb_size[2].x <= orb_left)
    {
        orb3_sx = 7;
        orb3_sy = 0;
    }
    if (orb_size[3].x <= orb_left && orb_size[3].y >= orb_bottom)
    {
        orb4_sx = 0;
        orb4_sy = -7;
    }
    else if (orb_size[3].x >= orb_right && orb_size[3].y <= orb_top)
    {
        orb4_sx = 0;
        orb4_sy = 7;
    }
    else if (orb_size[3].y >= orb_bottom && orb_size[3].x >= orb_right)
    {
        orb4_sx = -7;
        orb4_sy = 0;
    }
    else if (orb_size[3].y <= orb_top && orb_size[3].x <= orb_left)
    {
        orb4_sx = 7;
        orb4_sy = 0;
    }
}

void skill_shield(SDL_Event e)
{
    if (current_player == 1 && player1_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillshield = true;
        shield_size.x = 0;
        shield_size.y = 300;
        shield_size.w = 220;
        shield_size.h = 275;
        shield_collider[0].x = 200;// 0 is shield's critical point
        shield_collider[0].y = 420;
        shield_collider[0].w = 20;
        shield_collider[0].h = 35;
        shield_collider[1].x = 200;// 1 is shield upper front point
        shield_collider[1].y = 300;
        shield_collider[1].w = 20;
        shield_collider[1].h = 120;
        shield_collider[2].x = 200;// 2 is shield's lower front point
        shield_collider[2].y = 455;
        shield_collider[2].w = 20;
        shield_collider[2].h = 120;
        shield_collider[3].x = 0;// 3 is shield's bottom point
        shield_collider[3].y = 300;
        shield_collider[3].w = 200;
        shield_collider[3].h = 275;
        player1_skill2_cooldown = player1_skill2_max_cooldown;
    }
    if (current_player == -1 && player2_skill2_cooldown <= 0 && e.key.keysym.sym == SDLK_w)
    {
        skillshield = true;
        shield_size.x = 804;
        shield_size.y = 300;
        shield_size.w = 220;
        shield_size.h = 275;
        shield_collider[0].x = 804;// 0 is shield's critical point
        shield_collider[0].y = 420;
        shield_collider[0].w = 20;
        shield_collider[0].h = 35;
        shield_collider[1].x = 804;// 1 is shield upper front point
        shield_collider[1].y = 300;
        shield_collider[1].w = 20;
        shield_collider[1].h = 120;
        shield_collider[2].x = 804;// 2 is shield's lower front point
        shield_collider[2].y = 455;
        shield_collider[2].w = 20;
        shield_collider[2].h = 120;
        shield_collider[3].x = 824;// 3 is shield's bottom point
        shield_collider[3].y = 300;
        shield_collider[3].w = 200;
        shield_collider[3].h = 275;
        player2_skill2_cooldown = player2_skill2_max_cooldown;
    }
}

void heroskill(SDL_Event e)
{
    if (current_player == 1)
    {
        if (player1_hero == 1)
        {
            skill_wind(e);
            skill_block(e);
        }
        else if (player1_hero == 2)
        {
            skill_double(e);
            skill_orb(e);
        }
        else if (player1_hero == 3)
        {
            skill_split(e);
            skill_poison(e);
        }
        else if (player1_hero == 4)
        {
            skill_heal(e);
            skill_shield(e);
        }
    }
    else if(current_player == -1)
    {
        if (player2_hero == 1)
        {
            skill_wind(e);
            skill_block(e);
        }
        else if (player2_hero == 2)
        {
            skill_double(e);
            skill_orb(e);
        }
        else if (player2_hero == 3)
        {
            skill_split(e);
            skill_poison(e);
        }
        else if (player2_hero == 4)
        {
            skill_heal(e);
            skill_shield(e);
        }
    }
}

// this function handle input when game is start
int getinput(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
        escape += 1;
    }
    else if (e.type == SDL_KEYUP)
    {
        escape = 0;
    }
    if (!ready)
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
        {
            ready = true;
        }
    }
    else if (e.type == SDL_KEYDOWN && !fire && ready)// if press button and not fire yet
    {
        switch (e.key.keysym.sym)
            {
                case SDLK_SPACE:// if button pressed is space, charge power for shooting
                    xlup += 0.2;// charging power
                    bar.w += speedpower;// increase a bar width that represent a charging power
                    charge = true;// start showing a bullet maybe change this later
                    if (xlup > 20)
                    {
                        overcharge = true;
                    }
                    if (bar.w >= 1000)
                    {
                        bar.w = 1000;
                    }
                    break;
                case SDLK_UP:// if button pressed is arrow up increase angle by 1
                    angle += 1;
                    if (angle > 90)
                    {
                        angle -= 1;
                    }
                    break;
                case SDLK_DOWN:// if button pressed is arrow down decrease angle by 1
                    angle -= 1;
                    if (angle < -45)
                    {
                        angle += 1;
                    }
                    break;
            }
    }
    heroskill(e);
    if ((e.type == SDL_KEYUP && xlup != 0) || overcharge)// if power is charged and release a charge button,set a speed of bullet
    {
        fire = true;
        if (sy == -999999)// if sy is at start point to set start speed only once
        {
            sy = (xlup*sin(angle*pi/180)*-1);
            sx = xlup*cos(angle*pi/180);
            Mix_PlayChannel(-1, shootsound, 0);
        }
    }
    return 0;
}

bool checkcollision( SDL_Rect a, SDL_Rect b )
{
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

    if (rightA < -50 || leftA > 1100 || bottomA > 720)
    {
        afterhit = true;
        if ((!save_once && skilldouble))
        {
            doublehit = true;
        }
        if (skillpoison_hit)
        {
            return false;
        }
        return true;
    }
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
    afterhit= true;
    if ((!save_once && skilldouble))
    {
        doublehit = true;
    }
    if (current_player == 1)
    {
        Mix_PlayChannel(-1, player1_hitsound,0);
    }
    else if (current_player == -1)
    {
        Mix_PlayChannel(-1, player2_hitsound, 0);
    }
    return true;
}

void setpotion()
{
    int location = 0;
    while (location <= 240)
    {
        location = random_num(734);
    }
    potion_size.x = location;
    potion_size.y = 525;
}

// set bullet picture and animation each turn for player
void setcurrentbullet(SDL_Texture* temp_bullet_texture, SDL_Rect temp_bullet_animate[], int temp_bullet_max_frame, int temp_bullet_animate_speed)
{
    bullet_texture = temp_bullet_texture;
    bullet_max_frame = temp_bullet_max_frame;
    bullet_animate_speed = temp_bullet_animate_speed;
    SDL_SetTextureAlphaMod(bullet_texture, 255);
    for (int i=0; i < temp_bullet_max_frame; ++i)
    {
        bullet_animate[i].x = temp_bullet_animate[i].x;
        bullet_animate[i].y = temp_bullet_animate[i].y;
        bullet_animate[i].w = temp_bullet_animate[i].w;
        bullet_animate[i].h = temp_bullet_animate[i].h;
    }
}

// everything about bullet moving, hit or damage
int bullet_calculate()
{
    if (!game_in_menu && fire)// if ingame and player is shoot
    {
        if (bulletsize.x < -50 || bulletsize.x > 1100 || bulletsize.y > 720)
        {
            afterhit = false;
            nextturn = true;
            skillsplit = false;
            skilldouble = false;
            skillblock = false;
            skillpoison = false;
            return 0;
        }
        sx += wind*current_player;
        bulletsize.x += sx*current_player;
        bulletsize.y += sy;// moving a bullet in y axis
        sy += ay;// applying a gravity
        if (skillorb)
        {
            for(int j=0; j < 4; ++j)
            {
                if (current_player == 1 && player1_hero == 2)break;
                else if (current_player == -1 && player2_hero == 2)break;
                hit = checkcollision(bulletsize, orb_size[j]);
                if (hit)
                {
                    sx = 0;
                    sy = 0;
                    ay = 0;
                    orbhit = true;
                    break;
                }
            }
        }
        if (skillpoison_hit)// if player is poisoned check collision for potion
        {
            hit = checkcollision(bulletsize, potion_size);
            if (hit && current_player == skillpoison_target)
            {
                sx = 0;
                sy = 0;
                ay = 0;
                potion_size.x = -100;
                potion_size.y = -100;
                poisonturn = 4;
            }
            hit = true;
        }
        if (skillshield)
        {
            for(int j=0; j < 4; ++j)
            {
                if (current_player == 1 && player1_hero == 4)break;
                else if (current_player == -1 && player2_hero == 4)break;
                if (doublehit)
                {
                    afterhit = true;
                    break;
                }
                shield_hit = checkcollision(bulletsize, shield_collider[j]);
                if (shield_hit)
                {
                    sx = 0;
                    sy = 0;
                    ay = 0;
                    if (j == 0)
                    {
                        if (current_player == 1)
                        {
                            player2hp -= player1_atk*2;
                        }
                        else if (current_player == -1)
                        {
                            player1hp -= player2_atk*2;
                        }
                    }
                    else
                    {
                        if (current_player == 1)
                        {
                            player2hp -= player1_atk/4;
                        }
                        else if (current_player == -1)
                        {
                            player1hp -= player2_atk/4;
                        }
                    }
                    break;
                }
            }
        }
        // normal collision check (without skill)
        for (int i=0; i < 11; ++i)
        {
            if (doublehit)
            {
                afterhit = true;
                break;
            }
            if (current_player == 1)
            {
                if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9)
                {
                    continue;
                }
            }
            else if (current_player == -1)
            {
                if (i == 2 || i == 4 || i == 6 || i == 8 || i == 10)
                {
                    continue;
                }
            }
            hit = checkcollision(bulletsize, collider[i]);
            if (hit)
            {
                sx = 0;
                sy = 0;
                ay = 0;
                if (skillpoison && current_player == 1)
                {
                    player1_hitsound = hero3_hit_sound;
                }
                else if (skillpoison && current_player == -1)
                {
                    player2_hitsound = hero3_hit_sound;
                }
                switch(i)
                {
                    case 1:
                        player1hp -= player2_atk*1.2;
                        if(skillblock)
                        {
                            skillblock_hit = true;
                        }
                        if(skillpoison)
                        {
                            skillpoison_hit = true;
                            setpotion();
                            player2_hitsound = hero3_hit_sound;
                        }
                        break;
                    case 2:
                        player2hp -= player1_atk*1.2;
                        if(skillblock)
                        {
                            skillblock_hit = true;
                        }
                        if(skillpoison)
                        {
                            skillpoison_hit = true;
                            setpotion();
                            player1_hitsound = hero3_hit_sound;
                        }
                        break;
                    case 3:
                        player1_shield_gen_hp -= player2_atk;
                        break;
                    case 4:
                        player2_shield_gen_hp -= player1_atk;
                        break;
                    case 7:
                        player1hp -= player2_atk*1.3;
                        if(skillblock)
                        {
                            skillblock_hit = true;
                        }
                        if(skillpoison)
                        {
                            skillpoison_hit = true;
                            setpotion();
                            player2_hitsound = hero3_hit_sound;
                        }
                        break;
                    case 8:
                        player2hp -= player1_atk*1.3;
                        if(skillblock)
                        {
                            skillblock_hit = true;
                        }
                        if(skillpoison)
                        {
                            skillpoison_hit = true;
                            setpotion();
                            player2_hitsound = hero3_hit_sound;
                        }
                        break;
                    case 9:
                        player1hp -= player2_atk*1.4;
                        if(skillblock)
                        {
                            skillblock_hit = true;
                        }
                        if(skillpoison)
                        {
                            skillpoison_hit = true;
                            setpotion();
                            player2_hitsound = hero3_hit_sound;
                        }
                        break;
                    case 10:
                        player2hp -= player1_atk*1.4;
                        if(skillblock)
                        {
                            skillblock_hit = true;
                        }
                        if(skillpoison)
                        {
                            skillpoison_hit = true;
                            setpotion();
                            player2_hitsound = hero3_hit_sound;
                        }
                        break;
                }
                break;
            }
        }
        if (skilldouble && (hit || shield_hit))
        {
            if (doublehit)
            {
                if (!save_once)
                {
                    save_once = true;
                    save_wind = wind;
                    wind = 0;
                }
                if (alpha > 0)
                {
                    SDL_SetTextureAlphaMod(bullet_texture, alpha);
                    alpha -= 5;
                }
                else
                {
                    doublehit = false;
                    alpha = 255;
                }
            }
            if (!doublehit)
            {
                setcurrentbullet(rock_texture, rock_animate, 6, 5);
                if (current_player == 1)
                {
                    bulletsize.x = 120;
                    bulletsize.y = 450;
                }
                else if (current_player == -1)
                {
                    bulletsize.x = 860;
                    bulletsize.y = 450;
                }
                sy = (xlup*sin(angle*pi/180)*-1);
                sx = xlup*cos(angle*pi/180);
                ay = 0.1;
                wind = save_wind;
                start_explode = false;
                afterhit = false;
                skilldouble = false;
                nextturn = false;
                save_once = false;
                Mix_PlayChannel(-1, shootsound, 0);
                timeout = 0;
                bullet_calculate();
            }
        }
        if (!split_start)
        {
            hit = true;
        }
        if (skillsplit && (hit || shield_hit || orbhit))
        {
            if (split_start)
            {
                split_bullet_1_size.x = bulletsize.x;
                split_bullet_1_size.y = bulletsize.y-5;
                split_bullet_2_size.x = bulletsize.x;
                split_bullet_2_size.y = bulletsize.y-5;
                split_bullet_3_size.x = bulletsize.x;
                split_bullet_3_size.y = bulletsize.y-5;
                split_bullet_sx[0] = 3*cos(135*pi/180);
                split_bullet_sy[0] = (3*sin(135*pi/180)*-1);
                split_bullet_sx[1] = 3*cos(90*pi/180);
                split_bullet_sy[1] = (3*sin(90*pi/180)*-1);
                split_bullet_sx[2] = 3*cos(45*pi/180);
                split_bullet_sy[2] = (3*sin(45*pi/180)*-1);
                split_bullet_ay[0] = 0.1;
                split_bullet_ay[1] = 0.1;
                split_bullet_ay[2] = 0.1;
                bulletsize.x = -50;
                bulletsize.y = -50;
                sx = 0;
                sy = 0;
                ay = 0;
                split_start = false;
                setcurrentbullet(small_dynamite_texture, dynamite_animate, 8, 5);// change this to small dynamite
            }
            split_bullet_sx[0] += wind*current_player;
            split_bullet_sy[0] += split_bullet_ay[0];
            split_bullet_sx[1] += wind*current_player;
            split_bullet_sy[1] += split_bullet_ay[1];
            split_bullet_sx[2] += wind*current_player;
            split_bullet_sy[2] += split_bullet_ay[2];
            split_bullet_1_size.x += split_bullet_sx[0];
            split_bullet_1_size.y += split_bullet_sy[0];
            split_bullet_2_size.x += split_bullet_sx[1];
            split_bullet_2_size.y += split_bullet_sy[1];
            split_bullet_3_size.x += split_bullet_sx[2];
            split_bullet_3_size.y += split_bullet_sy[2];
            if (split_bullet_1_size.x < -50 || split_bullet_1_size.x > 1100 || split_bullet_1_size.y > 720)
            {
                split_bullet_1_damage = true;
            }
            if (split_bullet_2_size.x < -50 || split_bullet_2_size.x > 1100 || split_bullet_2_size.y > 720)
            {
                split_bullet_2_damage = true;
            }
            if (split_bullet_3_size.x < -50 || split_bullet_3_size.x > 1100 || split_bullet_3_size.y > 720)
            {
                split_bullet_3_damage = true;
            }
            if (split_bullet_1_damage && split_bullet_2_damage && split_bullet_3_damage)
            {
                skillsplit = false;
                return 0;
            }
            for (int j=0; j < 11;++j)
            {
                if (current_player == 1)
                {
                    if (j == 1 || j == 3 || j == 5 || j == 7 || j == 9)
                    {
                        continue;
                    }
                }
                else if (current_player == -1)
                {
                    if (j == 2 || j == 4 || j == 6 || j == 9 || j == 10)
                    {
                        continue;
                    }
                }
                if (!split_bullet_1_damage)
                split_bullet_1_hit = checkcollision(split_bullet_1_size, collider[j]);
                if (!split_bullet_2_damage)
                split_bullet_2_hit = checkcollision(split_bullet_2_size, collider[j]);
                if (!split_bullet_3_damage)
                split_bullet_3_hit = checkcollision(split_bullet_3_size, collider[j]);
                if (split_bullet_1_hit)
                {
                    split_bullet_sx[0] = 0;
                    split_bullet_sy[0] = 0;
                    split_bullet_ay[0] = 0;
                    if (!split_bullet_1_damage)
                    {
                        switch(j)
                        {
                            case 1:
                                player1hp -= (player2_atk*1.2)/3;
                                break;
                            case 2:
                                player2hp -= (player1_atk*1.2)/3;
                                break;
                            case 3:
                                player1_shield_gen_hp -= player2_atk/3;
                                break;
                            case 4:
                                player2_shield_gen_hp -= player1_atk/3;
                                break;
                            case 7:
                                player1hp -= (player2_atk*1.3)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 8:
                                player2hp -= (player1_atk*1.3)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 9:
                                player1hp -= (player2_atk*1.4)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 10:
                                player2hp -= (player1_atk*1.4)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                        }
                        split_bullet_1_damage = true;
                    }
                }
                if (split_bullet_2_hit)
                {
                    split_bullet_sx[1] = 0;
                    split_bullet_sy[1] = 0;
                    split_bullet_ay[1] = 0;
                    if (!split_bullet_2_damage)
                    {
                        switch(j)
                        {
                            case 1:
                                player1hp -= (player2_atk*1.2)/3;
                                break;
                            case 2:
                                player2hp -= (player1_atk*1.2)/3;
                                break;
                            case 3:
                                player1_shield_gen_hp -= player2_atk/3;
                                break;
                            case 4:
                                player2_shield_gen_hp -= player1_atk/3;
                                break;
                            case 7:
                                player1hp -= (player2_atk*1.3)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 8:
                                player2hp -= (player1_atk*1.3)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 9:
                                player1hp -= (player2_atk*1.4)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 10:
                                player2hp -= (player1_atk*1.4)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                        }
                        split_bullet_2_damage = true;
                    }
                }
                if (split_bullet_3_hit)
                {
                    split_bullet_sx[2] = 0;
                    split_bullet_sy[2] = 0;
                    split_bullet_ay[2] = 0;
                    if (!split_bullet_3_damage)
                    {
                        switch(j)
                        {
                            case 1:
                                player1hp -= (player2_atk*1.2)/3;
                                break;
                            case 2:
                                player2hp -= (player1_atk*1.2)/3;
                                break;
                            case 3:
                                player1_shield_gen_hp -= player2_atk/3;
                                break;
                            case 4:
                                player2_shield_gen_hp -= player1_atk/3;
                                break;
                            case 7:
                                player1hp -= (player2_atk*1.3)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 8:
                                player2hp -= (player1_atk*1.3)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 9:
                                player1hp -= (player2_atk*1.4)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                            case 10:
                                player2hp -= (player1_atk*1.4)/3;
                                if(skillblock)
                                {
                                    skillblock_hit = true;
                                }
                                if(skillpoison)
                                {
                                    skillpoison_hit = true;
                                    setpotion();
                                    player2_hitsound = hero3_hit_sound;
                                }
                                break;
                        }
                        split_bullet_3_damage = true;
                    }
                }
            }
            for(int j=0; j < 4; ++j)
            {
                if (!split_bullet_1_damage)
                split_bullet_1_hit = checkcollision(split_bullet_1_size, shield_collider[j]);
                if (!split_bullet_2_damage)
                split_bullet_2_hit = checkcollision(split_bullet_2_size, shield_collider[j]);
                if (!split_bullet_3_damage)
                split_bullet_3_hit = checkcollision(split_bullet_3_size, shield_collider[j]);
                if (split_bullet_1_hit)
                {
                    split_bullet_sx[0] = 0;
                    split_bullet_sy[0] = 0;
                    split_bullet_ay[0] = 0;
                    if (!split_bullet_1_damage)
                    {
                        if (j == 0)
                        {
                            if (current_player == 1)
                            {
                                player2hp -= (player1_atk/3)*2;
                            }
                            else if (current_player == -1)
                            {
                                player1hp -= (player2_atk/3)*2;
                            }
                        }
                        else
                        {
                            if (current_player == 1)
                            {
                                player2hp -= (player1_atk/3)/4;
                            }
                            else if (current_player == -1)
                            {
                                player1hp -= (player2_atk/3)/4;
                            }
                        }
                        split_bullet_1_damage = true;
                    }
                }
                if (split_bullet_2_hit)
                {
                    split_bullet_sx[1] = 0;
                    split_bullet_sy[1] = 0;
                    split_bullet_ay[1] = 0;
                    if (!split_bullet_2_damage)
                    {
                        if (j == 0)
                        {
                            if (current_player == 1)
                            {
                                player2hp -= (player1_atk/3)*2;
                            }
                            else if (current_player == -1)
                            {
                                player1hp -= (player2_atk/3)*2;
                            }
                        }
                        else
                        {
                            if (current_player == 1)
                            {
                                player2hp -= (player1_atk/3)/4;
                            }
                            else if (current_player == -1)
                            {
                                player1hp -= (player2_atk/3)/4;
                            }
                        }
                        split_bullet_2_damage = true;
                    }
                }
                if (split_bullet_3_hit)
                {
                    split_bullet_sx[2] = 0;
                    split_bullet_sy[2] = 0;
                    split_bullet_ay[2] = 0;
                    if (!split_bullet_3_damage)
                    {
                        if (j == 0)
                        {
                            if (current_player == 1)
                            {
                                player2hp -= (player1_atk/3)*2;
                            }
                            else if (current_player == -1)
                            {
                                player1hp -= (player2_atk/3)*2;
                            }
                        }
                        else
                        {
                            if (current_player == 1)
                            {
                                player2hp -= (player1_atk/3)/4;
                            }
                            else if (current_player == -1)
                            {
                                player1hp -= (player2_atk/3)/4;
                            }
                        }
                        split_bullet_3_damage = true;
                    }
                }
            }
            if (skillorb)
            {
                for(int j=0; j < 4; ++j)
                {
                    if (!split_bullet_1_damage)
                    split_bullet_1_hit = checkcollision(split_bullet_1_size, orb_size[j]);
                    if (!split_bullet_2_damage)
                    split_bullet_2_hit = checkcollision(split_bullet_2_size, orb_size[j]);
                    if (!split_bullet_3_damage)
                    split_bullet_3_hit = checkcollision(split_bullet_3_size, orb_size[j]);
                    if (split_bullet_1_hit)
                    {
                        split_bullet_sx[0] = 0;
                        split_bullet_sy[0] = 0;
                        split_bullet_ay[0] = 0;
                        if (!split_bullet_1_damage)
                        {
                            split_bullet_1_damage = true;
                        }
                    }
                    if (split_bullet_2_hit)
                    {
                        split_bullet_sx[1] = 0;
                        split_bullet_sy[1] = 0;
                        split_bullet_ay[1] = 0;
                        if (!split_bullet_2_damage)
                        {
                            split_bullet_2_damage = true;
                        }
                    }
                    if (split_bullet_3_hit)
                    {
                        split_bullet_sx[2] = 0;
                        split_bullet_sy[2] = 0;
                        split_bullet_ay[2] = 0;
                        if (!split_bullet_3_damage)
                        {
                            split_bullet_3_damage = true;
                        }
                    }
                }
            }
        }// not here
    }
    return 0;
}

// changing turn and reset some variable
int turn()
{
    if (player1hp <= 0 || player2hp <= 0)
    {
        gameend = true;
        ingame = false;
    }
    if (skillsplit)
    {
        return 0;
    }
    if (afterhit)
    {
        if (skillpoison && ((current_player == 1 && player1_hero == 3) || (current_player == -1 && player2_hero == 3)))
        {
            if (!start_explode)
            {
                bullet_frame = 0;
                start_explode = true;
            }
            // set texture for explosion here
            setcurrentbullet(poisonbreak_texture, dynamite_animate, 3, 15);
            bullet_frame += 1;
            if (bullet_frame/15 >= 3)
            {
                nextturn = true;
                afterhit = false;
            }
        }
        else if ((current_player == 1 && (player1_hero == 1 || player1_hero == 2)) || (current_player == -1 && (player2_hero == 1 || player2_hero == 2)))
        {
            if (alpha > 0)
            {
                SDL_SetTextureAlphaMod(bullet_texture, alpha);
                alpha -= 5;
            }
            else
            {
                nextturn = true;
                afterhit = false;
            }
        }
        else if ((current_player == 1 && (player1_hero == 3 || player1_hero == 4)) || (current_player == -1 && (player2_hero == 3 || player2_hero == 4)))
        {
            if (!start_explode)
            {
                bullet_frame = 0;
                start_explode = true;
            }
            setcurrentbullet(explode_texture, dynamite_animate, 3, 15);
            bullet_frame += 1;
            if (bullet_frame/15 >= 3)
            {
                nextturn = true;
                afterhit = false;
            }
        }
    }
    else if (current_player == 1)
    {
        if (nextturn)
        {
            wind = random_num(11)/1000;
            if (random_num(2) == 0)
            {
                wind *= -1;
            }
            angle = 45;
            xlup = 0;
            sy = -999999;
            sx = 0;
            bar.w = 0;
            ay = 0.1;
            charge = false;
            current_player = -1;
            fire = false;
            timeout = 0;
            nextturn = false;
            bulletsize.x = 860;
            bulletsize.y = 450;
            if(skillpoison_hit)
            {
                if(skillpoison_target == 1)
                {
                    if(poisonturn >= 2)
                    {
                        if (poisonturn < 3)
                        {
                            player1hp -= 20;
                        }
                        poisonturn = 0;
                        skillpoison_hit = false;
                    }
                    else
                    {
                        poisonturn += 1;
                        player1hp -= 20;
                    }
                }
            }
            if (skillpoison)
            {
                player1_hitsound = hero3_hit_sound;
            }
            skillpoison = false;
            if (skillwind){
                c_turn += 1;
            }
            if (c_turn >= 2)
            {
                c_turn = 0;
                skillwind = false;
            }
            if (skillorb){
                orb_turn += 1;
            }
            if (orb_turn >= 2)
            {
                orb_turn = 0;
                skillorb = false;
            }
            if (skillshield){
                shield_turn += 1;
            }
            if (shield_turn >= 2)
            {
                shield_turn = 0;
                skillshield = false;
            }
            if(skillblock_hit)
            {
                bar.w = 1000;
                skillblock_hit = false;
            }
            skillblock = false;
            player1_atk = 30;
            player2_atk = 30;
            player1_skill1_cooldown -= 1;
            if (player1_skill1_cooldown <= 0)
            {
                player1_skill1_cooldown = 0;
            }
            player1_skill2_cooldown -= 1;
            if (player1_skill2_cooldown <= 0)
            {
                player1_skill2_cooldown = 0;
            }
            if((skillpoison_hit&&skillpoison_target==-1)|| (skillorb&&player1_hero == 2) || (skillshield&&player1_hero == 4))
            {
                player1_skill2_cooldown = 3;
            }
            split_start = true;
            split_bullet_1_hit = false;
            split_bullet_2_hit = false;
            split_bullet_3_hit = false;
            split_bullet_1_damage = false;
            split_bullet_2_damage = false;
            split_bullet_3_damage = false;
            split_bullet_1_size.x = -50;
            split_bullet_2_size.x = -50;
            split_bullet_3_size.x = -50;
            overcharge = false;
            alpha = 255;
            start_explode = false;
            setcurrentbullet(player2_bullet_texture, player2_bullet_animate, player2_bullet_max_frame, player2_bullet_animate_speed);
            ready = false;
            afterhit = false;
            doublehit = false;
            shield_hit = false;
            if (player2_hitsound == potion_break_sound)
            {
                player2_hitsound = hero3_hit_sound;
            }
            //SDL_Delay(2000);
        }
    }
    else if (current_player == -1)
    {
        if (nextturn)
        {
            wind = random_num(11)/1000;
            if (random_num(2) == 0)
            {
                wind *= -1;
            }
            angle = 45;
            xlup = 0;
            sy = -999999;
            sx = 0;
            bar.w = 0;
            ay = 0.1;
            charge = false;
            current_player = 1;
            fire = false;
            timeout = 0;
            nextturn = false;
            bulletsize.x = 120;
            bulletsize.y = 450;
            if(skillpoison_hit)
            {
                if(skillpoison_target == -1)
                {
                    if(poisonturn >= 2)
                    {
                        if(poisonturn < 3)
                        {
                            player2hp -= 20;
                        }
                        poisonturn = 0;
                        skillpoison_hit = false;
                    }
                    else
                    {
                        poisonturn += 1;
                        player2hp -= 20;
                    }
                }
            }
            if (skillpoison)
            {
                player2_hitsound = hero3_hit_sound;
            }
            skillpoison = false;
            if (skillwind){
                c_turn += 1;
            }
            if (c_turn >= 2)
            {
                c_turn = 0;
                skillwind = false;
            }
            if (skillorb){
                orb_turn += 1;
            }
            if (orb_turn >= 2)
            {
                orb_turn = 0;
                skillorb = false;
            }
            if (skillshield){
                shield_turn += 1;
            }
            if (shield_turn >= 2)
            {
                shield_turn = 0;
                skillshield = false;
            }
            if(skillblock_hit)
            {
                bar.w = 1000;
                skillblock_hit = false;
            }
            skillblock = false;
            player1_atk = 30;
            player2_atk = 30;
            player2_skill1_cooldown -= 1;
            if (player2_skill1_cooldown <= 0)
            {
                player2_skill1_cooldown = 0;
            }
            player2_skill2_cooldown -= 1;
            if (player2_skill2_cooldown <= 0)
            {
                player2_skill2_cooldown = 0;
            }
            if((skillpoison_hit&&skillpoison_target==1)|| (skillorb&&player2_hero == 2) || (skillshield&&player2_hero == 4))
            {
                player2_skill2_cooldown = 3;
            }
            split_start = true;
            split_bullet_1_hit = false;
            split_bullet_2_hit = false;
            split_bullet_3_hit = false;
            split_bullet_1_damage = false;
            split_bullet_2_damage = false;
            split_bullet_3_damage = false;
            split_bullet_1_size.x = -50;
            split_bullet_2_size.x = -50;
            split_bullet_3_size.x = -50;
            overcharge = false;
            alpha = 255;
            start_explode = false;
            setcurrentbullet(player1_bullet_texture, player1_bullet_animate, player1_bullet_max_frame, player1_bullet_animate_speed);
            ready = false;
            afterhit = false;
            doublehit = false;
            shield_hit = false;
            if (player1_hitsound == potion_break_sound)
            {
                player1_hitsound = hero3_hit_sound;
            }
            //SDL_Delay(2000);
        }
    }
    return 0;
}

// set picture and animation for player according to their hero
void sethero()
{
    if (player1_hero == 1)
    {
        player1_bullet_texture = star_texture;
        player1_texture = hero1_texture;
        player1_bullet_max_frame = 5;
        player1_bullet_animate_speed = 2.5;
        player1_skill1_texture = skill_wind_texture;
        player1_skill2_texture = skill_block_texture;
        player1_skill1_max_cooldown = 3;
        player1_skill2_max_cooldown = 3;
        player1_gun_texture = hero1_gun_texture;
        player1_hitsound = hero1_hit_sound;
        player1_shield_gen_texture = shield_gen_texture;
        for (int i=0; i < player1_bullet_max_frame; ++i)
        {
            player1_bullet_animate[i].x = star_animate[i].x;
            player1_bullet_animate[i].y = star_animate[i].y;
            player1_bullet_animate[i].w = star_animate[i].w;
            player1_bullet_animate[i].h = star_animate[i].h;
        }
    }
    else if (player1_hero == 2)
    {
        player1_bullet_texture = rock_texture;
        player1_texture = hero2_texture;
        player1_bullet_max_frame = 6;
        player1_bullet_animate_speed = 5;
        player1_skill1_texture = skill_double_texture;
        player1_skill2_texture = skill_orb_texture;
        player1_skill1_max_cooldown = 3;
        player1_skill2_max_cooldown = 3;
        player1_gun_texture = hero2_gun_texture;
        player1_hitsound = hero2_hit_sound;
        player1_shield_gen_texture = shield_gen2_texture;
        for (int i=0; i < player1_bullet_max_frame; ++i)
        {
            player1_bullet_animate[i].x = rock_animate[i].x;
            player1_bullet_animate[i].y = rock_animate[i].y;
            player1_bullet_animate[i].w = rock_animate[i].w;
            player1_bullet_animate[i].h = rock_animate[i].h;
        }
    }
    else if (player1_hero == 3)
    {
        player1_bullet_texture = dynamite_texture;
        player1_texture = hero3_texture;
        player1_bullet_max_frame = 8;
        player1_bullet_animate_speed = 4;
        player1_skill1_texture = skill_split_texture;
        player1_skill2_texture = skill_poison_texture;
        player1_skill1_max_cooldown = 3;
        player1_skill2_max_cooldown = 3;
        player1_gun_texture = hero3_gun_texture;
        player1_hitsound = hero3_hit_sound;
        player1_shield_gen_texture = shield_gen3_texture;
        for (int i=0; i < player1_bullet_max_frame; ++i)
        {
            player1_bullet_animate[i].x = bomb_animate[i].x;
            player1_bullet_animate[i].y = bomb_animate[i].y;
            player1_bullet_animate[i].w = bomb_animate[i].w;
            player1_bullet_animate[i].h = bomb_animate[i].h;
        }
    }
    else if (player1_hero == 4)
    {
        player1_bullet_texture = bomb_texture;
        player1_texture = hero4_texture;
        player1_bullet_max_frame = 8;
        player1_bullet_animate_speed = 4;
        player1_skill1_texture = skill_heal_texture;
        player1_skill2_texture = skill_shield_texture;
        player1_skill1_max_cooldown = 3;
        player1_skill2_max_cooldown = 3;
        player1_gun_texture = hero4_gun_texture;
        player1_hitsound = hero4_hit_sound;
        player1_shield_gen_texture = shield_gen4_texture;
        for (int i=0; i < player1_bullet_max_frame; ++i)
        {
            player1_bullet_animate[i].x = bomb_animate[i].x;
            player1_bullet_animate[i].y = bomb_animate[i].y;
            player1_bullet_animate[i].w = bomb_animate[i].w;
            player1_bullet_animate[i].h = bomb_animate[i].h;
        }
    }
    if (player2_hero == 1)
    {
        player2_bullet_texture = star_texture;
        player2_texture = hero1_texture;
        player2_bullet_max_frame = 5;
        player2_bullet_animate_speed = 2.5;
        player2_skill1_texture = skill_wind_texture;
        player2_skill2_texture = skill_block_texture;
        player2_skill1_max_cooldown = 3;
        player2_skill2_max_cooldown = 3;
        player2_gun_texture = hero1_gun_texture;
        player2_hitsound = hero1_hit_sound;
        player2_shield_gen_texture = shield_gen_texture;
        for (int i=0; i < player2_bullet_max_frame; ++i)
        {
            player2_bullet_animate[i].x = star_animate[i].x;
            player2_bullet_animate[i].y = star_animate[i].y;
            player2_bullet_animate[i].w = star_animate[i].w;
            player2_bullet_animate[i].h = star_animate[i].h;
        }
    }
    else if (player2_hero == 2)
    {
        player2_bullet_texture = rock_texture;
        player2_texture = hero2_texture;
        player2_bullet_max_frame = 6;
        player2_bullet_animate_speed = 4;
        player2_skill1_texture = skill_double_texture;
        player2_skill2_texture = skill_orb_texture;
        player2_skill1_max_cooldown = 3;
        player2_skill2_max_cooldown = 3;
        player2_gun_texture = hero2_gun_texture;
        player2_hitsound = hero2_hit_sound;
        player2_shield_gen_texture = shield_gen2_texture;
        for (int i=0; i < player2_bullet_max_frame; ++i)
        {
            player2_bullet_animate[i].x = rock_animate[i].x;
            player2_bullet_animate[i].y = rock_animate[i].y;
            player2_bullet_animate[i].w = rock_animate[i].w;
            player2_bullet_animate[i].h = rock_animate[i].h;
        }
    }
    else if (player2_hero == 3)
    {
        player2_bullet_texture = dynamite_texture;
        player2_texture = hero3_texture;
        player2_bullet_max_frame = 8;
        player2_bullet_animate_speed = 4;
        player2_skill1_texture = skill_split_texture;
        player2_skill2_texture = skill_poison_texture;
        player2_skill1_max_cooldown = 3;
        player2_skill2_max_cooldown = 3;
        player2_gun_texture = hero3_gun_texture;
        player2_hitsound = hero3_hit_sound;
        player2_shield_gen_texture = shield_gen3_texture;
        for (int i=0; i < player2_bullet_max_frame; ++i)
        {
            player2_bullet_animate[i].x = dynamite_animate[i].x;
            player2_bullet_animate[i].y = dynamite_animate[i].y;
            player2_bullet_animate[i].w = dynamite_animate[i].w;
            player2_bullet_animate[i].h = dynamite_animate[i].h;
        }
    }
    else if (player2_hero == 4)
    {
        player2_bullet_texture = bomb_texture;
        player2_texture = hero4_texture;
        player2_bullet_max_frame = 8;
        player2_bullet_animate_speed = 5;
        player2_skill1_texture = skill_heal_texture;
        player2_skill2_texture = skill_shield_texture;
        player2_skill1_max_cooldown = 3;
        player2_skill2_max_cooldown = 3;
        player2_gun_texture = hero4_gun_texture;
        player2_hitsound = hero4_hit_sound;
        player2_shield_gen_texture = shield_gen4_texture;
        for (int i=0; i < player2_bullet_max_frame; ++i)
        {
            player2_bullet_animate[i].x = bomb_animate[i].x;
            player2_bullet_animate[i].y = bomb_animate[i].y;
            player2_bullet_animate[i].w = bomb_animate[i].w;
            player2_bullet_animate[i].h = bomb_animate[i].h;
        }
    }
    player1_atk = 30;
    player2_atk = 30;
    setcurrentbullet(player1_bullet_texture, player1_bullet_animate, player1_bullet_max_frame, player1_bullet_animate_speed);
}

// display cooldown
SDL_Texture* display_cooldown(int cooldown, bool cross)
{
    if (cross)
    {
        return numx_texture;
    }
    switch(cooldown)
    {
        case 0:
            return NULL;
            break;
        case 1:
            return num1_texture;
            break;
        case 2:
            return num2_texture;
            break;
        case 3:
            return num3_texture;
            break;
    }
    return NULL;
}

// function to display everything
void render()
{
    // if game in start menu
    if (game_in_menu)
    {
        // if game is in start menu animate background
        SDL_RenderCopy(grenderer, display_texture, &mainbackground_animate[mainbg_frame/15], NULL);
        mainbg_frame += 1;
        if (mainbg_frame/15 >= 4)
        {
            mainbg_frame = 0;
        }
    }
    if (select_hero)
    {
        SDL_RenderCopy(grenderer, display_texture, &mainbackground_animate[mainbg_frame/15], NULL);
        mainbg_frame += 1;
        if (mainbg_frame/15 >= 4)
        {
            mainbg_frame = 0;
        }

        SDL_RenderCopy(grenderer, hero1_pic_texture, &hero1_pic_animate[hero1_pic_frame/60], &hero1_pic_size);
        hero1_pic_frame += 1;
        if (hero1_pic_frame/60 >= 2)
        {
            hero1_pic_frame = 0;
        }

        SDL_RenderCopy(grenderer, hero2_pic_texture, &hero2_pic_animate[hero2_pic_frame/60], &hero2_pic_size);
        hero2_pic_frame += 1;
        if (hero2_pic_frame/60 >= 2)
        {
            hero2_pic_frame = 0;
        }

        SDL_RenderCopy(grenderer, hero3_pic_texture, &hero3_pic_animate[hero3_pic_frame/60], &hero3_pic_size);
        hero3_pic_frame += 1;
        if (hero3_pic_frame/60 >= 2)
        {
            hero3_pic_frame = 0;
        }

        SDL_RenderCopy(grenderer, hero4_pic_texture, &hero4_pic_animate[hero4_pic_frame/60], &hero4_pic_size);
        hero4_pic_frame += 1;
        if (hero4_pic_frame/60 >= 2)
        {
            hero4_pic_frame = 0;
        }
        if (hero_choose == 1)
        {
            SDL_RenderCopy(grenderer, choosehero1_texture, &mainbackground_animate[mainbg_frame/15], NULL);
            SDL_RenderCopy(grenderer, hero1_pic_texture, &hero1_pic_animate[hero1_pic_frame/60], &confirm_pic_size);
        }
        else if (hero_choose == 2)
        {
            SDL_RenderCopy(grenderer, choosehero2_texture, &mainbackground_animate[mainbg_frame/15], NULL);
            SDL_RenderCopy(grenderer, hero2_pic_texture, &hero2_pic_animate[hero2_pic_frame/60], &confirm_pic_size);

        }
        else if (hero_choose == 3)
        {
            SDL_RenderCopy(grenderer, choosehero3_texture, &mainbackground_animate[mainbg_frame/15], NULL);
            SDL_RenderCopy(grenderer, hero3_pic_texture, &hero3_pic_animate[hero3_pic_frame/60], &confirm_pic_size);
        }
        else if (hero_choose == 4)
        {
            SDL_RenderCopy(grenderer, choosehero4_texture, &mainbackground_animate[mainbg_frame/15], NULL);
            SDL_RenderCopy(grenderer, hero4_pic_texture, &hero4_pic_animate[hero4_pic_frame/60], &confirm_pic_size);
        }
    }
    else if (ingame)
    {
        // render background
        SDL_RenderCopy(grenderer, display_texture, &mainbackground_animate[mainbg_frame/15], NULL);
        mainbg_frame += 1;
        if (mainbg_frame/15 >= 4)
        {
            mainbg_frame = 0;
        }

        // render charge bar
        SDL_RenderCopy(grenderer, bar_texture, NULL, &bar);
        SDL_RenderCopy(grenderer, charge_bar_texture, NULL, &charge_bar);

        // render shield gen
        if (player1_shield_gen_hp > 0)
        {
            SDL_RenderCopy(grenderer, player1_shield_gen_texture, &shield_gen_animate[shield_gen_frame/10], &player1_shield_gen_size);
            player1_shield_gen_size.y += shield_gen_move;
            collider[3].y = player1_shield_gen_size.y;
            collider[3].y += shield_gen_move;
            collider[5].x = player1_barrier_size.x;
        }
        else
        {
            collider[3].y = -500;
            collider[5].x = -500;
        }
        if (player2_shield_gen_hp > 0)
        {
            SDL_RenderCopy(grenderer, player2_shield_gen_texture, &shield_gen_animate[shield_gen_frame/10], &player2_shield_gen_size);
            player2_shield_gen_size.y += shield_gen_move;
            collider[4].y = player2_shield_gen_size.y;
            collider[4].y += shield_gen_move;
            collider[6].x = player2_barrier_size.x;
        }
        else
        {
            collider[4].y = -500;
            collider[6].x = -500;
        }
        shield_gen_frame += 1;
        if (shield_gen_frame/10 >= 4)
        {
            shield_gen_frame = 0;
        }
        if (player1_shield_gen_size.y <= 50 || player2_shield_gen_size.y <= 50)
        {
            shield_gen_move = 1;
        }
        else if (player1_shield_gen_size.y >= 200 || player2_shield_gen_size.y >= 200)
        {
            shield_gen_move = -1;
        }
        // render shield gen

        // render shield gen hp
        player1_shield_gen_hp_size.w = player1_shield_gen_hp*2.905;
        player2_shield_gen_hp_size.w = player2_shield_gen_hp*2.905;
        if (player1_shield_gen_hp < 50)
        {
            player1_shield_hp_color_r = 255;
            player1_shield_hp_color_g = 2*(player1_shield_gen_hp*2.55);
        }
        else
        {
            player1_shield_hp_color_g = 255;
            player1_shield_hp_color_r = 255-(2*((player1_shield_gen_hp-50)*2.55));
        }
        if (player2_shield_gen_hp < 50)
        {
            player2_shield_hp_color_r = 255;
            player2_shield_hp_color_g = 2*(player2_shield_gen_hp*2.55);
        }
        else
        {
            player2_shield_hp_color_g = 255;
            player2_shield_hp_color_r = 255-(2*((player2_shield_gen_hp-50)*2.55));
        }
        SDL_SetTextureColorMod(hp_texture, player1_shield_hp_color_r, player1_shield_hp_color_g, 0);
        SDL_RenderCopy(grenderer, hp_texture, NULL, &player1_shield_gen_hp_size);
        SDL_SetTextureColorMod(hp_texture, player2_shield_hp_color_r, player2_shield_hp_color_g, 0);
        SDL_RenderCopy(grenderer, hp_texture, NULL, &player2_shield_gen_hp_size);
        SDL_RenderCopy(grenderer, shield_bar_texture, NULL, &player1_shield_gen_hp_bar_size);
        SDL_RenderCopy(grenderer, shield_bar_texture, NULL, &player2_shield_gen_hp_bar_size);
        // render shield gen hp

        // render barrier
        if (player1_shield_gen_hp > 0)
        {
            SDL_RenderCopy(grenderer, barrier_texture, NULL, &player1_barrier_size);
        }
        if (player2_shield_gen_hp > 0)
        {
            SDL_RenderCopy(grenderer, barrier_texture, NULL, &player2_barrier_size);
        }
        // render barrier

        // render orb
        if (skillorb)
        {
            SDL_RenderCopy(grenderer, orb_texture, NULL, &orb_size[0]);
            SDL_RenderCopy(grenderer, orb_texture, NULL, &orb_size[1]);
            SDL_RenderCopy(grenderer, orb_texture, NULL, &orb_size[2]);
            SDL_RenderCopy(grenderer, orb_texture, NULL, &orb_size[3]);
            orb_size[0].x += orb1_sx;
            orb_size[0].y += orb1_sy;
            orb_size[1].x += orb2_sx;
            orb_size[1].y += orb2_sy;
            orb_size[2].x += orb3_sx;
            orb_size[2].y += orb3_sy;
            orb_size[3].x += orb4_sx;
            orb_size[3].y += orb4_sy;
            move_orb();
        }
        // render orb

        // render player character
        SDL_RenderCopy(grenderer, player1_texture, NULL, &player1size);
        SDL_RendererFlip player2flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(grenderer, player2_texture, NULL, &player2size, 0, NULL, player2flip);
        // render player character

        // render wind bar and wind direction arrow
        windsize.w = fabs(wind)*14900; // set wind bar size
        if (wind < 0)// set if wind is negative point arrow to left
        {
            arrow_texture = wind_left_texture;
        }
        else if (wind > 0)// set if wind is positive point arrow to right
        {
            arrow_texture = wind_right_texture;
        }
        else
        {
            arrow_texture = wind_none_texture;
        }
        if (skillwind)// if skill is pressed
        {
            if (current_player == skillwind_target)// if current player is the target player
            {
                // don't render wind
            }
            else// render things normally
            {
                SDL_RenderCopyEx(grenderer, wind_texture, NULL, &windsize, 0, NULL, SDL_FLIP_NONE);
                SDL_RenderCopy(grenderer, arrow_texture, &wind_arrow_animate[wind_arrow_frame/10], &winddirectionsize);
                wind_arrow_frame += 1;
                if (wind_arrow_frame/10 > 1 || wind == 0)
                {
                    wind_arrow_frame = 0;
                }
            }
        }
        else// render things normally
        {
            SDL_RenderCopyEx(grenderer, wind_texture, NULL, &windsize, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopy(grenderer, arrow_texture, &wind_arrow_animate[wind_arrow_frame/10], &winddirectionsize);
            wind_arrow_frame += 1;
            if (wind_arrow_frame/10 > 1 || wind == 0)
            {
                wind_arrow_frame = 0;
            }
        }
        SDL_RenderCopy(grenderer, wind_bar_texture, NULL, &wind_bar_size);
        // render wind and wind direction arrow

        // render split skill
        if (skillsplit && !split_bullet_1_damage)
        {
            SDL_RenderCopy(grenderer, bullet_texture, &bullet_animate[bullet_frame/bullet_animate_speed], &split_bullet_1_size);
            if (bullet_frame/bullet_animate_speed >= bullet_max_frame)
            {
                bullet_frame = 0;
            }
        }
        if (skillsplit && !split_bullet_2_damage)
        {
            SDL_RenderCopy(grenderer, bullet_texture, &bullet_animate[bullet_frame/bullet_animate_speed], &split_bullet_2_size);
            if (bullet_frame/bullet_animate_speed >= bullet_max_frame)
            {
                bullet_frame = 0;
            }
        }
        if (skillsplit && !split_bullet_3_damage)
        {
            SDL_RenderCopy(grenderer, bullet_texture, &bullet_animate[bullet_frame/bullet_animate_speed], &split_bullet_3_size);
            if (bullet_frame/bullet_animate_speed >= bullet_max_frame)
            {
                bullet_frame = 0;
            }
        }
        // render split skill

        // render potion here
        if (skillpoison_hit)
        {
            SDL_RenderCopy(grenderer, potion_texture, &potion_animate[potion_frame/10], &potion_size);
            potion_frame += 1;
            if (potion_frame/10 >= 4)
            {
                potion_frame = 0;
            }
            SDL_SetTextureColorMod(skill_poison_texture, 255, 255 ,255);
            if (skillpoison_target == 1)
            {
                SDL_RenderCopy(grenderer, skill_poison_texture, NULL, &poison_icon_1);
            }
            else if (skillpoison_target == -1)
            {
                SDL_RenderCopy(grenderer, skill_poison_texture, NULL, &poison_icon_2);
            }
        }
        // render potion here

        // render skill shield
        if (skillshield)
        {
            SDL_RenderCopy(grenderer, shield_texture, NULL, &shield_size);
        }
        // render skill shield

        // render bullet

        // maybe declare sdl_point to set point at the end of gun here and set bullet location to the end of gun
        // or maybe just set bullet location to the end of gun don't have to use sdl_point?

        if (charge)
        {
            SDL_RenderCopy(grenderer, bullet_texture, &bullet_animate[bullet_frame/bullet_animate_speed], &bulletsize);
            if ((fire && !afterhit) || (skillsplit || (skilldouble && !doublehit)))
            bullet_frame += 1;
            if (bullet_frame/bullet_animate_speed >= bullet_max_frame)
            {
                bullet_frame = 0;
            }
        }
        // render bullet

        // render angle arrow
        float arrowangle;
        SDL_RendererFlip player1_gun_flip;
        SDL_RendererFlip player2_gun_flip;
        SDL_Point center_arrow = {20, player1_gun_size.h/2};
        SDL_Point center_arrow2 = {100, player2_gun_size.h/2};
        if (current_player == 1)// set arrow position and everything for player1
        {
            player1_gun_flip = SDL_FLIP_NONE;
            arrowangle = angle*-1;
            player1_angle = arrowangle;
            player2_gun_flip = SDL_FLIP_HORIZONTAL;
        }
        else if (current_player == -1)// set arrow position and everything for player2
        {
            player2_gun_flip = SDL_FLIP_HORIZONTAL;
            arrowangle = angle;
            player2_angle = arrowangle;
            player1_gun_flip = SDL_FLIP_NONE;
        }
        SDL_RenderCopyEx(grenderer, player1_gun_texture, NULL, &player1_gun_size, player1_angle, &center_arrow, player1_gun_flip);
        SDL_RenderCopyEx(grenderer, player2_gun_texture, NULL, &player2_gun_size, player2_angle, &center_arrow2, player2_gun_flip);
        // render angle arrow

        // render hp
        player1hpsize.w = (player1hp*2.905)/2.5;
        player2hpsize.w = (player2hp*2.905)/2.5;
        if (player1hp < 125)
        {
            player1_hp_color_r = 255;
            player1_hp_color_g = 2*(player1hp);
        }
        else
        {
            player1_hp_color_g = 255;
            player1_hp_color_r = 255-(2*(player1hp-125));
        }
        if (player2hp < 125)
        {
            player2_hp_color_r = 255;
            player2_hp_color_g = 2*(player2hp);
        }
        else
        {
            player2_hp_color_g = 255;
            player2_hp_color_r = 255-(2*(player2hp-125));
        }
        SDL_SetTextureColorMod(hp_texture, player1_hp_color_r, player1_hp_color_g, 0);
        SDL_RenderCopy(grenderer, hp_texture, NULL, &player1hpsize);
        SDL_SetTextureColorMod(hp_texture, player2_hp_color_r, player2_hp_color_g, 0);
        SDL_RenderCopy(grenderer, hp_texture, NULL, &player2hpsize);
        SDL_RenderCopy(grenderer, hp_bar_texture, NULL, &player1hp_bar_size);
        SDL_RenderCopy(grenderer, hp_bar_texture, NULL, &player2hp_bar_size);
        // render hp

        // render skill icon
        SDL_SetTextureColorMod(player1_skill1_texture, 255-(200*(player1_skill1_cooldown > 0)), 255-(200*(player1_skill1_cooldown > 0)), 255-(200*(player1_skill1_cooldown > 0)));
        SDL_SetTextureColorMod(player2_skill1_texture, 255-(200*(player2_skill1_cooldown > 0)), 255-(200*(player2_skill1_cooldown > 0)), 255-(200*(player2_skill1_cooldown > 0)));

        SDL_RenderCopy(grenderer, player1_skill1_texture, NULL, &player1_skill1_size);
        SDL_RenderCopy(grenderer, player2_skill1_texture, NULL, &player2_skill1_size);

        SDL_SetTextureColorMod(player1_skill2_texture, 255-(200*(player1_skill2_cooldown > 0)), 255-(200*(player1_skill2_cooldown > 0)), 255-(200*(player1_skill2_cooldown > 0)));
        SDL_SetTextureColorMod(player2_skill2_texture, 255-(200*(player2_skill2_cooldown > 0)), 255-(200*(player2_skill2_cooldown > 0)), 255-(200*(player2_skill2_cooldown > 0)));

        SDL_RenderCopy(grenderer, player1_skill2_texture, NULL, &player1_skill2_size);
        SDL_RenderCopy(grenderer, player2_skill2_texture, NULL, &player2_skill2_size);
        // render skill icon

        // render number to display skill cooldown here
        cooldown_11_texture = display_cooldown(player1_skill1_cooldown, false);
        cooldown_12_texture = display_cooldown(player1_skill2_cooldown, (skillpoison_hit&&skillpoison_target==-1)|| (skillorb&&player1_hero == 2) || (skillshield&&player1_hero == 4));
        cooldown_21_texture = display_cooldown(player2_skill1_cooldown, false);
        cooldown_22_texture = display_cooldown(player2_skill2_cooldown, (skillpoison_hit&&skillpoison_target==1)||(skillorb&&player2_hero == 2) || (skillshield&&player2_hero == 4));
        SDL_RenderCopy(grenderer, cooldown_11_texture, NULL, &player1_skill1_size);
        SDL_RenderCopy(grenderer, cooldown_12_texture, NULL, &player1_skill2_size);
        SDL_RenderCopy(grenderer, cooldown_21_texture, NULL, &player2_skill1_size);
        SDL_RenderCopy(grenderer, cooldown_22_texture, NULL, &player2_skill2_size);
        // render number to display skill cooldown here

        if (!ready)
        {
            if (current_player == 1)
            {
                SDL_RenderCopy(grenderer, ready_texture, NULL, NULL);
            }
            else if (current_player == -1)
            {
                SDL_RenderCopy(grenderer, ready2_texture, NULL, NULL);
            }
            text_surface = TTF_RenderText_Solid(gfont, "Hold space to shoot", textcolor);
            text_texture = SDL_CreateTextureFromSurface(grenderer, text_surface);
            SDL_FreeSurface(text_surface);
            SDL_RenderCopy(grenderer, text_texture, NULL, &space_font);
            text_surface = TTF_RenderText_Solid(gfont, "Press arrow to change direction", textcolor);
            text_texture = SDL_CreateTextureFromSurface(grenderer, text_surface);
            SDL_FreeSurface(text_surface);
            SDL_RenderCopy(grenderer, text_texture, NULL, &arrow_font);
            text_surface = TTF_RenderText_Solid(gfont, "Press q or w to use skill", textcolor);
            text_texture = SDL_CreateTextureFromSurface(grenderer, text_surface);
            SDL_FreeSurface(text_surface);
            SDL_RenderCopy(grenderer, text_texture, NULL, &skill_font);
        }
    }
    if (gameend)
    {
        if (player2hp <= 0)// player 1 win
        {
            SDL_RenderCopy(grenderer, gameend_texture, &mainbackground_animate[mainbg_frame/10], NULL);
            mainbg_frame += 1;
            if (mainbg_frame/10 >= 4)
            {
                mainbg_frame = 0;
            }
        }
        else if (player1hp <= 0)//player 2 win
        {
            SDL_RenderCopy(grenderer, gameend2_texture, &mainbackground_animate[mainbg_frame/10], NULL);
            mainbg_frame += 1;
            if (mainbg_frame/10 >= 4)
            {
                mainbg_frame = 0;
            }
        }
    }
}

int main(int argc, char* args[])
{
    if(!init())
    {
        printf("init failed\n");
    }
    else
    {
        // call function load media
        if ( !loadmedia())
        {
            printf("Load media failed\n");
        }
        else
        {
            // main loop start here
            bool quit = false;

            random_setup();
            // set start wind
            wind = random_num(11)/1000;
            if (random_num(2) == 0)
            {
                wind *= -1;
            }

            // start background music
            Mix_PlayMusic(music, -1);
            SDL_Event e;
            // set default picture for background
            display_texture = startmenu_texture;
            // loop while application is not quit
            while (!quit)
            {
                // handle event that on queue
                turn();
                while(SDL_PollEvent(&e) != 0)
                {
                    //if user close application
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    //check if game is in menu or not
                    if (game_in_menu)
                    {
                        // check if keyboard is pressed or not
                        if (e.type == SDL_KEYDOWN){
                        //switch check which button is pressed
                            switch ( e.key.keysym.sym)//<- just how to get what button is pressed
                            {
                                case SDLK_h:// press h to see how to play press again to close it
                                    if (display_texture == startmenu_texture){
                                        display_texture = how2play_texture;// change and display how to play
                                    }
                                    break;
                                case SDLK_RETURN:// press enter to start the game
                                    game_in_menu = false;// change this to false to stop check and coming in this
                                    select_hero = true;
                                    display_texture = bg_select_hero_texture;// change background to main background in game
                                    break;
                                case SDLK_ESCAPE:
                                    if (display_texture == how2play_texture){
                                        display_texture = startmenu_texture;// change back and display menu
                                    }
                                    break;
                            }
                        }// if e.type == sdl_keydown
                    }// if game_in_menu
                    else if (select_hero)
                    {
                        if (current_player == 1)
                            display_texture = bg_select_hero_texture;
                        else if (current_player == -1)
                            display_texture = bg_select_hero2_texture;
                        if (e.type == SDL_KEYDOWN)
                        {
                            if (confirm_hero == 0)
                            {
                                switch(e.key.keysym.sym)
                                {
                                    case SDLK_1:
                                        if (current_player == 1)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 1;
                                        }
                                        else if (current_player == -1 && player1_hero != 1)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 1;
                                        }
                                        break;
                                    case SDLK_2:
                                        if (current_player == 1)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 2;
                                        }
                                        else if (current_player == -1 && player1_hero != 2)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 2;
                                        }
                                        break;
                                    case SDLK_3:
                                        if (current_player == 1)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 3;
                                        }
                                        else if (current_player == -1 && player1_hero != 3)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 3;
                                        }
                                        break;
                                    case SDLK_4:
                                        if (current_player == 1)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 4;
                                        }
                                        else if (current_player == -1 && player1_hero != 4)
                                        {
                                            confirm_hero += 1;
                                            hero_choose = 4;
                                        }
                                        break;
                                    case SDLK_ESCAPE:
                                        if (current_player == 1)
                                        {
                                            select_hero = false;
                                            game_in_menu = true;
                                            hero_choose = -1;
                                            player1_hero = -1;
                                            display_texture = startmenu_texture;
                                        }
                                        else if (current_player == -1)
                                        {
                                            current_player = 1;
                                            hero_choose = -1;
                                            confirm_hero = 0;
                                            player2_hero = -1;
                                            display_texture = bg_select_hero_texture;
                                        }
                                }
                            }
                            else if (confirm_hero == 1)
                            {
                                switch (e.key.keysym.sym)
                                {
                                    case SDLK_RETURN:
                                        confirm_hero += 1;
                                        break;
                                    case SDLK_ESCAPE:
                                        confirm_hero = 0;
                                        hero_choose = -1;
                                        break;
                                }
                            }
                            if (confirm_hero == 2)
                            {
                                if (current_player == 1)
                                {
                                    player1_hero = hero_choose;
                                    confirm_hero = 0;
                                    hero_choose = -1;
                                    current_player = -1;
                                }
                                else if (current_player == -1)
                                {
                                    player2_hero = hero_choose;
                                    confirm_hero = 0;
                                    hero_choose = -1;
                                }
                            }
                        }
                        if (player1_hero != -1 && player2_hero != -1)
                        {
                            select_hero = false;
                            current_player = 1;
                            num_map = random_num(3);
                            if (num_map == 0)
                            {
                                display_texture = background_plain_texture;
                            }
                            else if (num_map == 1)
                            {
                                display_texture = background_snow_texture;
                            }
                            else if (num_map == 2)
                            {
                                display_texture = background_forest_texture;
                            }
                            ingame = true;
                            sethero();
                        }
                    }
                    else if(ingame){
                        getinput(e);// call function shooting and pass variable e in it
                        if (escape >= 60)
                        {
                            ingame = false;
                            game_in_menu = true;
                            display_texture = startmenu_texture;
                            player1_hero = -1;
                            player2_hero = -1;
                            confirm_hero = 0;
                            hero_choose = 0;
                            player1hp = 250;
                            player2hp = 250;
                            player1_shield_gen_hp = 100;
                            player2_shield_gen_hp = 100;
                            player1_atk = 30;
                            player2_atk = 30;
                            player1_skill1_cooldown = 0;
                            player2_skill1_cooldown = 0;
                            player1_skill2_cooldown = 0;
                            player2_skill2_cooldown = 0;
                            skillwind = false;
                            skillpoison = false;
                            skilldouble = false;
                            skillsplit = false;
                            skillblock = false;
                            skillblock_hit = false;
                            skillorb = false;
                            skillpoison_hit = false;
                            skillpoison_target = 0;
                            skillshield = false;
                            doublehit = false;
                            angle = 45;
                            player1_angle = 45;
                            player2_angle = 45;
                            alpha = 255;
                            fire = false;
                            charge = false;
                            nextturn = false;
                            poisonturn = 0;
                            ready = false;
                            afterhit = false;
                            start_explode = false;
                            c_turn = 0;
                            orb_turn = 0;
                            shield_turn = 0;
                            skillwind_target = -99;
                            skillblock_target = -99;
                            timeout = 0;
                            xlup = 0;
                            bar.w = 0;
                            bulletsize.x = 120;
                            overcharge = false;
                            orbhit = false;
                            current_player = 1;
                            player1_shield_gen_size.x = 0;
                            player1_shield_gen_size.y = 50;
                            player2_shield_gen_size.x = 924;
                            player2_shield_gen_size.y = 50;
                        }
                    }
                    else if(gameend)
                    {
                        // after game end here -> reset game or quit
                        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
                        {
                            gameend = false;
                            ingame = true;
                            player1hp = 250;
                            player2hp = 250;
                            player1_shield_gen_hp = 100;
                            player2_shield_gen_hp = 100;
                            player1_atk = 30;
                            player2_atk = 30;
                            player1_skill1_cooldown = 0;
                            player2_skill1_cooldown = 0;
                            player1_skill2_cooldown = 0;
                            player2_skill2_cooldown = 0;
                            skillwind = false;
                            skillpoison = false;
                            skilldouble = false;
                            skillsplit = false;
                            skillblock = false;
                            skillblock_hit = false;
                            skillorb = false;
                            skillpoison_hit = false;
                            skillpoison_target = 0;
                            skillshield = false;
                            doublehit = false;
                            angle = 45;
                            player1_angle = 45;
                            player2_angle = 45;
                            alpha = 255;
                            fire = false;
                            charge = false;
                            nextturn = false;
                            poisonturn = 0;
                            ready = false;
                            afterhit = false;
                            start_explode = false;
                            c_turn = 0;
                            orb_turn = 0;
                            shield_turn = 0;
                            skillwind_target = -99;
                            skillblock_target = -99;
                            timeout = 0;
                            xlup = 0;
                            bar.w = 0;
                            overcharge = false;
                            orbhit = false;
                            player1_shield_gen_size.x = 0;
                            player1_shield_gen_size.y = 50;
                            player2_shield_gen_size.x = 924;
                            player2_shield_gen_size.y = 50;
                            // reset everything here
                        }
                        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            ingame = false;
                            game_in_menu = true;
                            display_texture = startmenu_texture;
                            player1_hero = -1;
                            player2_hero = -1;
                            confirm_hero = 0;
                            hero_choose = 0;
                            player1hp = 250;
                            player2hp = 250;
                            player1_shield_gen_hp = 100;
                            player2_shield_gen_hp = 100;
                            player1_atk = 30;
                            player2_atk = 30;
                            player1_skill1_cooldown = 0;
                            player2_skill1_cooldown = 0;
                            player1_skill2_cooldown = 0;
                            player2_skill2_cooldown = 0;
                            skillwind = false;
                            skillpoison = false;
                            skilldouble = false;
                            skillsplit = false;
                            skillblock = false;
                            skillblock_hit = false;
                            skillorb = false;
                            skillpoison_hit = false;
                            skillpoison_target = 0;
                            skillshield = false;
                            doublehit = false;
                            angle = 45;
                            player1_angle = 45;
                            player2_angle = 45;
                            alpha = 255;
                            fire = false;
                            charge = false;
                            nextturn = false;
                            poisonturn = 0;
                            ready = false;
                            afterhit = false;
                            start_explode = false;
                            c_turn = 0;
                            orb_turn = 0;
                            shield_turn = 0;
                            skillwind_target = -99;
                            skillblock_target = -99;
                            timeout = 0;
                            xlup = 0;
                            bar.w = 0;
                            bulletsize.x = 120;
                            //sx = 0;
                            //sy = 0;
                            overcharge = false;
                            orbhit = false;
                            current_player = 1;
                            player1_shield_gen_size.x = 0;
                            player1_shield_gen_size.y = 50;
                            player2_shield_gen_size.x = 924;
                            player2_shield_gen_size.y = 50;
                        }
                    }
                }// poll event
                if (fire)
                {
                    //printf("timeout : %d\n", timeout);
                    timeout += 1;
                }
                if (timeout >= 600)
                {
                    printf("Bullet travel time out!\n");
                    printf("Fatal error occur. Return to menu...\n");
                    ingame = false;
                    game_in_menu = true;
                    display_texture = startmenu_texture;
                    player1_hero = -1;
                    player2_hero = -1;
                    confirm_hero = 0;
                    hero_choose = 0;
                    player1hp = 250;
                    player2hp = 250;
                    player1_shield_gen_hp = 100;
                    player2_shield_gen_hp = 100;
                    player1_atk = 30;
                    player2_atk = 30;
                    player1_skill1_cooldown = 0;
                    player2_skill1_cooldown = 0;
                    player1_skill2_cooldown = 0;
                    player2_skill2_cooldown = 0;
                    skillwind = false;
                    skillpoison = false;
                    skilldouble = false;
                    skillsplit = false;
                    skillblock = false;
                    skillblock_hit = false;
                    skillorb = false;
                    skillpoison_hit = false;
                    skillpoison_target = 0;
                    skillshield = false;
                    doublehit = false;
                    angle = 45;
                    player1_angle = 45;
                    player2_angle = 45;
                    alpha = 255;
                    fire = false;
                    charge = false;
                    nextturn = false;
                    poisonturn = 0;
                    ready = false;
                    afterhit = false;
                    start_explode = false;
                    c_turn = 0;
                    orb_turn = 0;
                    shield_turn = 0;
                    skillwind_target = -99;
                    skillblock_target = -99;
                    timeout = 0;
                    xlup = 0;
                    bar.w = 0;
                    bulletsize.x = 120;
                    //sx = 0;
                    //sy = 0;
                    overcharge = false;
                    current_player = 1;
                    orbhit = false;
                    player1_shield_gen_size.x = 0;
                    player1_shield_gen_size.y = 50;
                    player2_shield_gen_size.x = 924;
                    player2_shield_gen_size.y = 50;
                }
                //clear everything out first
                SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(grenderer);

                // main processing function here
                if ((!afterhit && !nextturn) || (skillsplit || skilldouble))
                    bullet_calculate();

                // do everything else such as render things here
                //animation for main background
                render();
                SDL_RenderPresent(grenderer);
            }// main while !quit loop
        }
    }
    Mix_HaltMusic();
    close();
    return 0;
}
