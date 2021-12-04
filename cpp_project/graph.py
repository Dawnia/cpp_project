import numpy as np
from matplotlib import pyplot as plt


def find_null(data):
    for i in range(len(data)):
        if abs(data[i] + 1) < pow(10, -10):
            return i
    return -1


def get_data(filename, g1, g2):
    time_p, phi_p, xi_p, energy_p = np.loadtxt("cmake-build-debug/"+filename+".txt", unpack=True)

    x_border = max(abs(phi_p)) + 0.05
    y_border = max(abs(xi_p)) + 0.05
    g1.plot((-x_border, x_border), (0, 0), color="black")
    g1.plot((0, 0), (-y_border, y_border), color="black")
    g1.plot(phi_p, xi_p)
    g1.set_xlabel(r"$\varphi,\ rad$")
    g1.set_ylabel(r"$\dot\varphi,\ s^{-1}$")

    split = find_null(energy_p)
    g2.plot(time_p[:split], np.log(energy_p[:split] + 1))
    g2.set_xlabel(r"time, s")
    g2.set_ylabel(r"$\ln(E/E_0 - 1)$")

    return


def main():
    fig, ((g1, g2), (g3, g4)) = plt.subplots(2, 2)
    get_data("heun_periodic", g1, g2)
    g1.set_title("Periodic potential")
    get_data("heun_parabolic", g3, g4)
    g3.set_title("Parabolic potential")
    plt.show()
    return


main()
