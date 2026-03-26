
#include <iostream>
using namespace std;

int main()
{
    double light_speed, distance, delay, delay_min;

    light_speed = 300000.;
    distance = 54717696.;

    delay = distance / light_speed * 2;
    delay_min = delay / 60;

    cout << "Задержка при двухсторонней связи между Землёй и Марсом будет "  << delay << " секунд или " << delay_min << " минут";

    return 0;

}
