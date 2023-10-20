#include <SDL2/SDL.h>
#include <algorithm>

#define SCREEN_W 1000
#define SCREEN_H 600
#define PLAYER_RECT_W 15
#define PLAYER_RECT_H 100
#define BALL_W 20

const int ball_speed = 5;
const int paddle_speed = 8;

int ball_dir_Y = -ball_speed;
int ball_dir_X = -ball_speed;

bool running = true;
SDL_Rect paddle1{30, SCREEN_H / 2 - (PLAYER_RECT_H / 2), PLAYER_RECT_W, PLAYER_RECT_H};
SDL_Rect paddle2 { SCREEN_W - (30 + PLAYER_RECT_W), SCREEN_H / 2 - (PLAYER_RECT_H / 2), PLAYER_RECT_W, PLAYER_RECT_H};
SDL_Rect ball;

void ball_draw() {
    ball = {SCREEN_W / 2 - BALL_W / 2, SCREEN_H / 2 - BALL_W / 2, BALL_W, BALL_W};
}

void events() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
        }
    }
    
}

void draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < SCREEN_H + 200; i++) {
        if (i % 2 == 0) {
            int h = i * 80;
            SDL_RenderDrawLine(renderer, SCREEN_W / 2, h, SCREEN_W / 2, h + 100);
        }
    }
    SDL_RenderFillRect(renderer, &paddle1);
    SDL_RenderFillRect(renderer, &paddle2);
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);
}

void logic() {
    ball.x += ball_dir_X;
    ball.y += ball_dir_Y;

    if (ball.y < 0 || ball.y + BALL_W > SCREEN_H) {
        ball_dir_Y = -ball_dir_Y;
    }

    if (ball.x < 0 || ball.x > SCREEN_W) {
        ball_draw();
    }

    if ((ball.x < paddle1.x + paddle1.w && ball.x > paddle1.x) && (ball.y > paddle1.y && ball.y < paddle1.y + paddle1.h)) {
        ball_dir_X = ball_speed;
    }

    if ((ball.x > paddle2.x - paddle2.w && ball.x < paddle2.x) && (ball.y > paddle2.y && ball.y < paddle2.y + paddle2.h)) {
        ball_dir_X = -ball_speed;
    }

    const uint8_t *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_W] && paddle1.y > 0)
    {
        paddle1.y -= paddle_speed;
    }

    if (state[SDL_SCANCODE_S] && paddle1.y < SCREEN_H - paddle1.h)
    {
        paddle1.y += paddle_speed;
    }

    if (state[SDL_SCANCODE_UP] && paddle2.y > 0) {
        paddle2.y -= paddle_speed;
    }

    if (state[SDL_SCANCODE_DOWN] && paddle2.y < SCREEN_H - paddle2.h) {
        paddle2.y += paddle_speed;
    }
}


int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        "Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_W,
        SCREEN_H,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, 0);
    ball_draw();
    
    while (running)
    {
        events();
        draw(renderer);
        logic();
        SDL_Delay(20);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}