#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 100
#define HEIGHT 100


int main()
{
  int quit=0;

  SDL_Window *win = 0;
  win = SDL_CreateWindow("Invaders", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (win == 0)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // the renderer is the core element we need to draw, each call to SDL for drawing will need the
  // renderer pointer
  SDL_Renderer *ren = 0;
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // check to see if this worked
  if (ren == 0)
  {
    printf("%s\n",SDL_GetError() );
    return EXIT_FAILURE;
  }
  // this will set the background colour to white.
  // however we will overdraw all of this so only for reference
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  int counter=0;

  int blue, green, red;

  int howmany =0;
  while(quit==0){
    howmany++;
    SDL_RenderClear(ren);
    static double ca=-0.8;
    static double cb=0.156;
    ca-=0.000001;
    cb+=0.000001;
    for(int y=0-HEIGHT/2; y<HEIGHT/2; ++y){
      for(int x=0-WIDTH/2; x<WIDTH/2; ++x){
//        int newy = y-HEIGHT/2;
//        int newx = y-WIDTH/2;
        float zx=(float)x/(WIDTH*8);
        float zy=(float)y/(HEIGHT*8);
        float tmpzx = zx;
        counter=0;

        while(zx*zx + zy*zy < 10000 && counter < 1000){
          counter++;
          tmpzx=zx;
          zx=(zx*zx)-(zy*zy)+ca;
          zy=(2*tmpzx*zy)+cb;
        }

        float result = ((float)counter/1000);

        blue=(result<0.333)?255:(result>0.666?0:(result-0.333)/0.333*255);
        green=(result<0.333)?(result/0.333*255):(result<0.666?255:(1.0-result)/0.333*255);
        red=(result<0.333)?0:(result>0.666?255:(result-0.333)/0.333*255);
        SDL_SetRenderDrawColor(ren, red, green, blue, 255);
        SDL_Rect pixel = {(x+WIDTH/2),(y+HEIGHT/2),1,1};
        SDL_RenderFillRect(ren,&pixel);
        printf("(%d)",howmany);
      }
    }
    SDL_Delay(10);
    SDL_RenderPresent(ren);
  }
  SDL_Quit();
  return 0;
}



