#ifndef LEAPFROG_HEUNMETHOD_H
#define LEAPFROG_HEUNMETHOD_H

#include "SysState.h"

template <typename PhiFunction_t, typename XiFunction_t>
class HeunSolver {
private:
    PhiFunction_t const phi_f;
    XiFunction_t const xi_f;

public:
    HeunSolver(PhiFunction_t phi_f, XiFunction_t xi_f):
            xi_f(std::forward<XiFunction_t>(xi_f)),
            phi_f(std::forward<PhiFunction_t>(phi_f)) { }

    template <typename T>
    SystemState<T> operator()(SystemState<T> const &s, T t, T dt) const {
        auto euler_next = SystemState<T> {
                s.phi + phi_f(s,t) * dt,
                s.xi + xi_f(s,t) * dt
        };

        auto full_next = SystemState<T> {
                s.phi + phi_f(euler_next,t+dt) * dt,
                s.xi + xi_f(euler_next,t+dt) * dt
        };

        return SystemState<T> {
                (euler_next.phi + full_next.phi) / static_cast<T>(2),
                (euler_next.xi + full_next.xi) / static_cast<T>(2)
        };
    }
};

#endif //LEAPFROG_HEUNMETHOD_H
