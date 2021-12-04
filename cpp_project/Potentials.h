#ifndef LEAPFROG_POTENTIALS_H
#define LEAPFROG_POTENTIALS_H

#include <cmath>

template <typename T>
class PeriodicPotentialFactory {
private:
    T gamma, omega;

    class PhiFunction {
    public:
        PhiFunction() = default;

        T operator()(SystemState<T> const &s, T t) const {
            return s.xi;
        }
    };

    class XiFunction {
    private:
        T gamma, omega;
    public:
        XiFunction(T gamma, T omega): gamma(gamma), omega(omega) {};

        T operator()(SystemState<T> const &s, T t) const {
            return -(this->gamma * s.xi + this->omega * this->omega * std::sin(s.phi));
        }
    };

    class EnergyFunction final {
    private:
        T omega;
    public:
        explicit EnergyFunction(T omega): omega(omega) {};

        T operator()(SystemState<T> const &s, T t) const {
            return s.xi * s.xi / static_cast<T>(2) + this->omega * this->omega * (static_cast<T>(1) - std::cos(s.phi));
        }
    };

public:
    PeriodicPotentialFactory(T omega, T gamma): omega(omega), gamma(gamma) {};

    auto get_xifunction() const {
        return XiFunction(gamma, omega);
    }

    auto get_phifunction() const {
        return PhiFunction();
    }

    auto get_energyfunction() const {
        return EnergyFunction(omega);
    }
};

template <typename T>
class ParabolicPotentialFactory {
private:
    T gamma, omega;

    class PhiFunction {
    public:
        PhiFunction() = default;

        T operator()(SystemState<T> const &s, T t) const {
            return s.xi;
        }
    };
    class XiFunction {
    private:
        T gamma, omega;
    public:
        XiFunction(T gamma, T omega): gamma(gamma), omega(omega) {};

        T operator()(SystemState<T> const &s, T t) const {
            return -(this->gamma * s.xi + this->omega * this->omega * s.phi);
        }
    };

    class EnergyFunction final {
    private:
        T omega;
    public:
        explicit EnergyFunction(T omega): omega(omega) {};

        T operator()(SystemState<T> const &s, T t) const {
            return (s.xi * s.xi + this->omega * this->omega * s.phi * s.phi) / static_cast<T>(2);
        }
    };

public:
    ParabolicPotentialFactory(T omega, T gamma): omega(omega), gamma(gamma) {};

    auto get_xifunction() const {
        return XiFunction(gamma, omega);
    }

    auto get_phifunction() const {
        return PhiFunction();
    }

    auto get_energyfunction() const {
        return EnergyFunction(omega);
    }
};


#endif //LEAPFROG_POTENTIALS_H
