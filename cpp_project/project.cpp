#include "HeunMethod.h"
#include "Potentials.h"
#include "Printer.h"

#include <iostream>
#include <iomanip>
#include <fstream>

std::ostream& os_scientific(std::ostream &os) {
    return os << std::setprecision(8) << std::scientific;
}

int main(int argc, const char * argv[]) {
    float omega = 1;
    float gamma = 0.1;

    PeriodicPotentialFactory per(omega, gamma);
    ParabolicPotentialFactory par(omega, gamma);
    SystemState<float> initial_state{0.f,0.5f};
    float dt = 1.e-4;
    size_t iteration_size = 12400000;
    size_t skip_size = 1000;

    {
        std::ofstream fos("./heun_periodic.txt");
        fos << os_scientific;
        Printer printer1(
                SystemState<float>{0.,0.5},
                HeunSolver(per.get_phifunction(), per.get_xifunction()),
                per.get_energyfunction(),
                dt,
                iteration_size,
                skip_size,
                fos
        );
        printer1.run();
    }

    {
        std::ofstream fos("./heun_parabolic.txt");
        fos << os_scientific;
        Printer printer2(
                SystemState<float>{0.,0.5},
                HeunSolver(par.get_phifunction(), par.get_xifunction()),
                par.get_energyfunction(),
                dt,
                iteration_size,
                skip_size,
                fos
        );
        printer2.run();
    }
    return 0;
}

