#include "Flock.hpp"

Flock::Flock(float d_, float s_, float a_, float c_, int n_):
d{d_}, s{s_}, a{a_}, c{c_}, n{n_} {
    for(int i=0;i<n;i++){
        Boid boid_n;
        flock.push_back(boid_n);
    }
}