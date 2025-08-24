#pragma once
#include <algorithm>

class Ether {
public:
    static Ether &instance();

    double density() const noexcept;

    void consume(double amount) noexcept;

    void dissolve(double amount) noexcept;

private:
    // Bornes et échelle très conservatrices (à ajuster par gouvernance)
    static constexpr double min_density = 0.50;
    static constexpr double max_density = 2.00;
    static constexpr double k = 1e-6; // sensibilité
    static constexpr double cap = 1e12; // borne de normalisation
    double density_ = 1.0;
};
