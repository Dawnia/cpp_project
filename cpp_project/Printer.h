#ifndef LEAPFROG_PRINTER_H
#define LEAPFROG_PRINTER_H

#include "SysState.h"
#include <iostream>

template <typename Solver_t, typename EnergyFunction_t, typename T>
class Printer final {
private:
    SystemState<T> const initial_state;
    Solver_t const solver;
    EnergyFunction_t const energy_f;
    T const dt;
    size_t const iteration_size;
    size_t const skip_size;
    std::ostream &os;
public:
    Printer(SystemState<T> initial_state, Solver_t solver, EnergyFunction_t energy_f, T dt, size_t iteration_size, size_t skip_size, std::ostream &os):
            initial_state(initial_state),
            solver(std::forward<Solver_t>(solver)),
            energy_f(std::forward<EnergyFunction_t>(energy_f)),
            dt(dt), iteration_size(iteration_size), skip_size(skip_size),
            os(os) { }

    void run() const {
        SystemState<T> current_state(initial_state);
        auto t = static_cast<T>(0);
        auto const initial_energy = energy_f(initial_state, t);
        for (size_t it = 0, skip = skip_size; it != iteration_size; ++it, ++skip) {
            t = dt * it;
            current_state = solver(current_state,t,dt);
            if (skip_size == skip) {
                os << t << ' ' << current_state << ' ' << (energy_f(current_state,t) - initial_energy) / initial_energy << '\n';
                skip = 0;
            }
        }
    }
};


#endif //LEAPFROG_PRINTER_H
