#include "Boids.hpp"
#include "Vettore.hpp"
    


    Boid::Boid():
    
    Position{(static_cast <float>(rand() % 30000 + 45000))/100,(static_cast <float>(rand() % 15000 + 20000))/100},
    Velocity{static_cast <float>(rand() % 20 + 10), static_cast <float>(rand() % 20+10)} {}
    inline void Boid::Set_Position(vettore& P){Position=P;}
    vettore Boid::Get_Position(){return Position;}
    inline void Boid::Set_Velocity(vettore& V){Velocity=V;}
    inline const vettore Boid::Get_Velocity(){return Velocity;}
    inline void Boid::Set_Predator_Check(bool c){}
    inline bool Boid::Get_Predator_Check() { return Predator_Check; }
    void Boid::Wall_Hit(){
        if((Position.get_x()<=25) || (Position.get_x()>=1175)){
            Velocity.set_x(1.5*Velocity.get_x());
        }
        if((Position.get_y()<=25) || (Position.get_y()>=625)){
            Velocity.set_y(1.5*Velocity.get_y());
        }
    }
