#include "Particle.h"
#include <math.h>
#include <stdlib.h>
namespace code{
    Particle::Particle() : m_x(0), m_y(0) {
        //m_x = (( 2.0 * rand())/RAND_MAX) - 1;
        //m_y = (( 2.0 * rand())/RAND_MAX) - 1;

        // m_xspeed = 0.001 * (((2.0 * rand())/RAND_MAX) - 1);
        // m_yspeed = 0.001 * (((2.0 * rand())/RAND_MAX) - 1);
        init();
            }
    Particle::~Particle(){
        m_x=0;
        m_y=0;
        m_direction = (2* M_PI *rand())/RAND_MAX;
        m_speed = (0.001 * rand())/RAND_MAX;
        m_speed *= m_speed;
    }
    void Particle::update(int interval){
        // m_x += m_xspeed;
        // m_y += m_yspeed;
        
        m_direction += interval * 0.0004;
        double xspeed = m_speed * cos(m_direction);
        double yspeed = m_speed * sin(m_direction);

        m_x += xspeed * interval;
        m_y += yspeed * interval;
        
        if(m_x <= -1.0 || m_x >= 1.0){
             init();
        }
        if(m_y <= -1.0 || m_y >= 1.0){
            init();
        }
        if(rand()<RAND_MAX/100){
            init();
        }
    }
    
}
