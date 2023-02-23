#ifndef SWARM_H_
#define SWARM_H_
#include "Particle.h"
namespace code{
    class Swarm{
        public:
            const static int NPARTICLES = 5000;
        private:
        Particle * m_pParticle;
        public:
            Swarm();
            virtual ~Swarm();
            void update();
            const Particle * const getParticles(){ return m_pParticle;};
    };
}/*namespace code*/

#endif