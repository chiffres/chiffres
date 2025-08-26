#include "Chiffre.h"
#include "Ether.h"

using namespace Chiffres;

/**
 * @brief Represents the mathematical constant τ (tau), which is the ratio of a circle's circumference to its radius.
 *
 * τ (tau) is approximately equal to 6.28318530717958647692. It is equivalent to 2π (two times pi) and is often used
 * in mathematical and scientific calculations involving angular measurements, trigonometry, or periodic phenomenon.
 *
 */
constexpr double TAU = 6.28318530717958647692;

double Chiffre::total() const noexcept {
    return total_;
}

const Memory &Chiffre::memory() const noexcept {
    return mem_;
}

Chiffre::Chiffre(const double initial)
    : total_(initial) {
}

State Chiffre::state() const noexcept {
    return state_;
}


void Chiffre::record_flow(const double amount, const bool incoming) {
    const double mag = std::abs(amount);

    mem_.stability_bias = std::min(3.0, mem_.stability_bias * (1.0 + 0.001 * std::min(mag, 1e6) / 1e6));
    mem_.volatility_bias = std::min(
        3.0, mem_.volatility_bias * (1.0 + 0.0005 * (incoming ? 0.5 : 1.0) * std::min(mag, 1e6) / 1e6));
}

void Chiffre::spend(const double amount) {
    if (amount < 0.0) throw std::invalid_argument("spend(amount<0)");
    total_ -= amount;
    record_flow(amount, /*incoming=*/false);
}

void Chiffre::receive(const double amount) {
    if (amount < 0.0) throw std::invalid_argument("receive(amount<0)");
    total_ += amount;
    record_flow(amount, /*incoming=*/true);
}


double Chiffre::draw_mutation_factor(const EthicsScore &ethics, const CyclePhase &cycle) const {
    double mu_log = 0.0;
    double sigma_log = 0.02;

    sigma_log *= mem_.volatility_bias;
    sigma_log /= std::max(1e-9, mem_.stability_bias);

    const double phase = std::clamp(cycle.phase, 0.0, 1.0);
    const double cycle_boost = 1.0 + 0.5 * std::sin(TAU * phase); // [-0.5..+0.5] -> [0.5..1.5]
    sigma_log *= std::clamp(cycle_boost, 0.5, 1.5);

    const double es = std::clamp(ethics.score, -1.0, 1.0);
    sigma_log *= 1.0 - 0.5 * es;
    mu_log += 0.01 * es;

    const double ether = Ether::instance().density();
    mu_log += std::log(std::clamp(1.0 / ether, 0.90, 1.10));

    std::lognormal_distribution dist(mu_log, std::max(1e-6, sigma_log));
    return dist(rng);
}

double Chiffre::mutate(const EthicsScore &ethics, const CyclePhase &cycle) {
    const double before = total_;
    const double f = draw_mutation_factor(ethics, cycle);
    total_ *= f;
    const double delta = total_ - before;
    delta > 0 ? Ether::instance().consume(delta) : Ether::instance().dissolve(-delta);
    mem_.events++;
    const double shock = std::abs(std::log(f));
    mem_.volatility_bias = std::min(3.0, mem_.volatility_bias * (1.0 + shock));
    if (ethics.score > 0) {
        mem_.stability_bias = std::min(3.0, mem_.stability_bias * (1.0 + 0.5 * ethics.score));
    }
    return delta;
}

void Chiffre::set_state(const State state) noexcept {
    state_ = state;
}
