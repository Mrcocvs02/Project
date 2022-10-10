#include "Flock.hpp"

Flock::Flock(float d_, float s_, float a_, float c_, int n_)
    : d{d_},
      s{s_},
      a{a_},
      c{c_},
      n{n_},
      Predator{{(static_cast<float>(rand() % 30000 + 45000)) / 100,
                (static_cast<float>(rand() % 15000 + 20000)) / 100},
               {static_cast<float>(rand() % 20 + 5),
                static_cast<float>(rand() % 20 + 5)}}{
                  
  for (int i = 0; i < n; i++) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 random_generator(seed);
    std::uniform_real_distribution<float> position_x(425, 575);
    std::uniform_real_distribution<float> position_y(300, 450);
    float p_x = position_x(random_generator);
    float p_y = position_y(random_generator);
    vettore p_{p_x, p_y};

    std::normal_distribution<float> velocity(110., 60.);
    std::uniform_int_distribution<int> sign_x(0, 1);
    float v_x = velocity(random_generator) *
                (static_cast<float>(sign_x(random_generator)) - 0.5);
    float v_y = velocity(random_generator) *
                (static_cast<float>(sign_x(random_generator)) - 0.5);
    vettore v_{v_x, v_y};
    Boid boid_n(p_, v_);
    Flock_.push_back(boid_n);
  }
  while(Obstacles.size()<20){
    Obstacles.push_back({(static_cast<float>(rand() % 120000)) / 100,
                         (static_cast<float>(rand() % 65000)) / 100});
  }
}

vettore Flock::Medium_Velocity() {
  vettore temp{0, 0};
  for (int i = 0; i < Flock_.size(); i++) {
    temp = temp + Flock_[i].Get_Velocity();
  };
  return (temp / Flock_.size());
}
float Flock::Sdv_Medium_Velocity() {
  float res = 0;
  for (int i = 0; i < Flock_.size(); i++) {
    res += (Flock_[i].Get_Velocity().norm() - Medium_Velocity().norm()) *
           (Flock_[i].Get_Velocity().norm() - Medium_Velocity().norm());
  };
  return (sqrt(res / Flock_.size()));
}
vettore Flock::Center_Of_Mass() {
  vettore temp{0, 0};
  for (int i = 0; i < Flock_.size(); i++) {
    temp = temp + Flock_[i].Get_Position();
  };
  return (temp / Flock_.size());
}
float Flock::Sdv_Center_Of_Mass() {
  float res = 0;
  for (int i = 0; i < Flock_.size(); i++) {
    res += (Flock_[i].Get_Position().norm() - Center_Of_Mass().norm()) *
           (Flock_[i].Get_Position().norm() - Center_Of_Mass().norm());
  };
  return (sqrt(res / Flock_.size()));
}

vettore Flock::V_Separation_i(int i) {
  vettore v{0, 0};
  for (auto it : Flock_) {
    if ((it.Get_Position() - Flock_[i].Get_Position()).norm() <= d) {
      v = v - ((it.Get_Position() - Flock_[i].Get_Position()) * s);
    }
  }
  return v;
}
vettore Flock::V_Allignement1_i(int i) {
  return ((Medium_Velocity() - Flock_[i].Get_Velocity()) * a);
}
vettore Flock::V_Cohesion_i(int i) {
  return ((Center_Of_Mass() - Flock_[i].Get_Position()) * c);
}
vettore Flock::Predator_Repulsion(int i) {
  vettore res{0, 0};
  vettore Distance =
      (Predator.Get_Position() - Flock_[i].Get_Position());
  if (Distance.norm() < 40) {
    res = Distance * 80 / (-Distance.norm());
  }
  return res;
}
vettore Flock::Obstacles_Repulsion(int i){
  vettore res{0, 0};
  vettore Distance{0, 0};
  for (int j = 0; j < Obstacles.size(); j++) {
    Distance = (Obstacles[j] - Flock_[i].Get_Position());
    if (Distance.norm() < 40) {
      res = res + Distance * 25 / (-Distance.norm());
    }
  }
  return res;
}

// std::vector<int> Flock::Boids_Seen(int i) {
//   std::vector<int> b_seen;
//   for (int j = 0; j < Flock_.size(); j++) {
//     vettore distance = Flock_[i].Get_Position() - Flock_[j].Get_Position();
//     if ((angle(distance, Flock_[i].Get_Velocity()) > 0) &&
//         (angle(distance, Flock_[i].Get_Velocity()) < (M_PI / 2)) &&
//         (distance.norm() <= d) && (i != j)) {
//       b_seen.push_back(j);
//     } else {
//       b_seen.push_back(-1);
//     }
//   }
//   return b_seen;
// }
void Flock::Set_Velocity(int i) {
  if (Flock_[i].Get_Velocity().norm() <= 30) {
    Flock_[i].Set_Velocity(vettore(Flock_[i].Get_Velocity() * 1.8));
  }
  if (Flock_[i].Get_Velocity().norm() >= 70) {
    Flock_[i].Set_Velocity(Flock_[i].Get_Velocity() * 0.8);
  }
}
void Flock::Rules(int i) {
  vettore v_i = Flock_[i].Get_Velocity() + V_Allignement1_i(i) +
                V_Cohesion_i(i) + V_Separation_i(i) + Predator_Repulsion(i)+ Obstacles_Repulsion(i);
  Flock_[i].Set_Position(Flock_[i].Get_Position()+(Flock_[i].Get_Velocity() / 30));
  Flock_[i].Set_Velocity(v_i);
}

void Flock::Predator_Simulation() {
  vettore v_temp = Predator.Get_Velocity() +
                   ((Center_Of_Mass() - Predator.Get_Position()) * 5 * c);
  if (Predator.Get_Velocity().norm() > 35) {
    v_temp = v_temp * 0.8;
  }
  Predator.Set_Position(Predator.Get_Position() + Predator.Get_Velocity() / 30);
  Predator.Set_Velocity(v_temp);
}
void Flock::Simulation(bool p_check) {
  for (int i = 0; i < Flock_.size(); i++) {
    Rules(i);
    Flock_[i].Wall_Hit();
    Set_Velocity(i);

    
  }
  if (p_check) {
    Predator_Simulation();
  }
};



