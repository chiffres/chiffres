#include "Ether.h"

using namespace Chiffre;

Ether &Ether::instance() {
    static Ether instance;
    return instance;
}

double Ether::density() const noexcept {
    return density_;
}

void Ether::consume(const double amount) noexcept {
    const double step = k * std::clamp(amount, 0.0, cap);
    density_ = std::clamp(density_ * (1.0 - step), min_density, max_density);
}

void Ether::dissolve(const double amount) noexcept {
    const double step = k * std::clamp(amount, 0.0, cap);
    density_ = std::clamp(density_ * (1.0 + step), min_density, max_density);
}
