#include "Flock.hpp"

Flock::Flock(float d_, float s_, float a_, float c_, int n_)
    : d{d_},
      s{s_},
      a{a_},
      c{c_},
      n{n_},
      predator{{(static_cast<float>(rand() % 30000 + 45000)) / 100,
                (static_cast<float>(rand() % 15000 + 20000)) / 100},
               {static_cast<float>(rand() % 20 + 5),
                static_cast<float>(rand() % 20 + 5)}} {
  for (int i = 0; i < n; i++) {
    Boid boid_n({(static_cast<float>(rand() % 30000 + 45000)) / 100,
                 (static_cast<float>(rand() % 15000 + 20000)) / 100},
                {static_cast<float>(rand() % 20 + 5),
                 static_cast<float>(rand() % 20 + 5)});
    flock_.push_back(boid_n);
  }
}

vettore Flock::medium_velocity() {
  vettore temp{0, 0};
  for (int i = 0; i < flock_.size(); i++) {
    temp = temp + flock_[i].Get_Velocity();
  };
  return (temp / flock_.size());
}
float Flock::sdv_medium_velocity() {
  float res = 0;
  for (int i = 0; i < flock_.size(); i++) {
    res += (flock_[i].Get_Velocity().norm() - medium_velocity().norm()) *
           (flock_[i].Get_Velocity().norm() - medium_velocity().norm());
  };
  return (sqrt(res / flock_.size()));
}
vettore Flock::center_of_mass() {
  vettore temp{0, 0};
  for (int i = 0; i < flock_.size(); i++) {
    temp = temp + flock_[i].Get_Position();
  };
  return (temp / flock_.size());
}
float Flock::sdv_center_of_mass() {
  float res = 0;
  for (int i = 0; i < flock_.size(); i++) {
    res += (flock_[i].Get_Position().norm() - center_of_mass().norm()) *
           (flock_[i].Get_Position().norm() - center_of_mass().norm());
  };
  return (sqrt(res / flock_.size()));
}

vettore Flock::v_separation_i(int j) {
  vettore v{0, 0};
  for (auto it : flock_) {
    if ((it.Get_Position() - flock_[j].Get_Position()).norm() <= d) {
      v = v - ((it.Get_Position() - flock_[j].Get_Position()) * s);
    }
  }
  return v;
}
vettore Flock::v_allignement1_i(int j) {
  return ((medium_velocity() - flock_[j].Get_Velocity()) * a);
}
vettore Flock::v_cohesion_i(int j) {
  return ((center_of_mass() - flock_[j].Get_Position()) * c);
}
vettore Flock::predator_repulsion(int j) {
  vettore res{0, 0};
  vettore distance_ =
      (get_predator().Get_Position() - flock_[j].Get_Position());
  if (distance_.norm() < 40) {
    res = distance_ * 80 / (-distance_.norm());
  }
  return res;
}

std::vector<int> Flock::boids_seen(int j) {
  std::vector<int> b_seen;
  for (int i = 0; i < flock_.size(); i++) {
    vettore distance = flock_[i].Get_Position() - flock_[j].Get_Position();
    if ((angle(distance, flock_[j].Get_Velocity()) > 0) &&
        (angle(distance, flock_[j].Get_Velocity()) < (M_PI / 2)) &&
        (distance.norm() <= d) && (i != j)) {
      b_seen.push_back(i);
    } else {
      b_seen.push_back(-1);
    }
  }
  return b_seen;
}
void Flock::set_velocities(int j) {
  if (flock_[j].Get_Velocity().norm() <= 30) {
    flock_[j].Set_Velocity(vettore(flock_[j].Get_Velocity() * 1.8));
  }
  if (flock_[j].Get_Velocity().norm() >= 75.0) {
    flock_[j].Set_Velocity(flock_[j].Get_Velocity() * 0.8);
  }
}
void Flock::rules(int j) {
  vettore v_j = flock_[j].Get_Velocity() + v_allignement1_i(j) +
                v_cohesion_i(j) + v_separation_i(j) + predator_repulsion(j);
  flock_[j].Set_Position(flock_[j].Get_Velocity() / 30);
  flock_[j].Set_Velocity(v_j);
}

void Flock::predator_simulation() {
  vettore v_temp = predator.Get_Velocity() +
                   ((center_of_mass() - predator.Get_Position()) * 5 * c);
  if (predator.Get_Velocity().norm() > 35) {
    v_temp = v_temp * 0.8;
  }
  predator.Set_Position(predator.Get_Position() + predator.Get_Velocity() / 30);
  predator.Set_Velocity(v_temp);
}
void Flock::simulation(bool p_check) {
  for (int j = 0; j < flock_.size(); j++) {
    rules(j);
    flock_[j].Wall_Hit();
    set_velocities(j);
  }
  if (p_check) {
    predator_simulation();
  }
};