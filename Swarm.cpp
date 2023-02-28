#include "Swarm.h"

namespace code{
    Swarm::Swarm() : lastTime(0){
        m_pParticle = new Particle[NPARTICLES];
    }

    Swarm::~Swarm(){
        delete [] m_pParticle;
    }

    void Swarm::update(int elapsed){
        int interval = elasped -lastTime;
        for(int i = 0; i < Swarm::NPARTICLES; i++){
            m_pParticle[i].update();
        }
        lastTime = elasped;
    }
}
