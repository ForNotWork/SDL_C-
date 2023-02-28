#include <iostream>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//added manualy
#include "Screen.h"
#include "screen.cpp"
#include "Particle.h"
#include "Particle.cpp"
#include "Swarm.h"
#include "Swarm.cpp"
using namespace std;
using namespace code;
int main(int argc, char *argv[])
{
    srand(time(NULL));
    Screen screen;

    if (screen.init() == false)
    {
        cout << "ERROR intialisation SDL!!!" << endl;
    }

    Swarm swarm;

    
    while (true)
    {
        // update particles
        // Draw particles
        //screen.clear();
        

        int elapsed=SDL_GetTicks();
        swarm.update();
        
        unsigned char green=(unsigned char)((1 + sin(elapsed * 0.001))*128);
        unsigned char red=(unsigned char)((1 + sin(elapsed * 0.002))*128);
        unsigned char blue=(unsigned char)((1 + sin(elapsed * 0.003))*128);
        const Particle * const pParticle = swarm.getParticles();
        for(int i=0; i< Swarm::NPARTICLES;i++){
            Particle particle = pParticle[i];

            int x = (particle.m_x + 1)*Screen::SCREEN_WIDTH/2;
            int y = particle.m_y *Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;

            //screen.setPixel(x, y, 255, 255, 255);
            screen.setPixel(x, y, red, green, blue);
        }
        
        screen.boxBlur();
        //Draw screen
        screen.update();
        
        // Checks for messages/events
        if(screen.processEvent() == false){
            break;
        }
    }
  
    screen.close();
    return 0;
}
