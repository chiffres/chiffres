#pragma once
#include <random>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include "Ether.h"

enum class State { Circulation, Rest };

// Score éthique global de l’acteur/portefeuille : [-1, +1]
struct EthicsScore {
    double score = 0.0;
};

// Phase cyclique (ex: saisonnalité) dans [0,1)
struct CyclePhase {
    double phase = 0.0;
};

// Mémoire simple des comportements passés
struct Memory {
    double volatility_bias = 1.0; // >1 => plus de variance future
    double stability_bias  = 1.0; // >1 => amortit les chocs
    std::uint64_t events   = 0;   // nb de mutations/flux mémorisés
};

class Chiffres {
public:
    explicit Chiffres(double initial = 0.0);

    // --- Circulation (certitude) ---
    void spend(double amount);    // total -= amount
    void receive(double amount);  // total += amount

    double mutate(const EthicsScore& ethics, const CyclePhase& cycle);

    void set_state(const State s) noexcept { state_ = s; }
    State state() const noexcept { return state_; }
    double total() const noexcept { return total_; }
    const Memory& memory() const noexcept { return mem_; }

    // Enregistrer un flux pour nourrir la mémoire (appelé par spend/receive)
    void record_flow(double amount, bool incoming);

private:
    // Tire un facteur multiplicatif log-normal paramétré par mémoire/éthique/cycle/éther
    double draw_mutation_factor(const EthicsScore&, const CyclePhase&) const;

    State state_ = State::Circulation;
    double total_;
    Memory mem_;

    // RNG partagé
    static inline std::mt19937_64 rng{std::random_device{}()};
};
