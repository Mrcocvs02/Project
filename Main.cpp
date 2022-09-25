#include <iostream>
#include "Flock.hpp"
#include "Boids.hpp"

#include <sys/time.h>


int main(){
timeval start, stop;
double elapsedTime;
gettimeofday(&start, NULL);

    srand((int) time(0));
    Flock ff(5.,6.,7.,4.,500);
    std::cout << ff.get_flock()[3].Get_Position().get_x()<<'\n';

    gettimeofday(&stop, NULL);
elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0;   				// sec to ms
elapsedTime += (stop.tv_usec - start.tv_usec) / 1000.0;   			// us to ms

std::cout << "t" << " , " << elapsedTime << " ms.\n";
}