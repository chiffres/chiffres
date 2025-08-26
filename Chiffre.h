#pragma once

#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <random>
#include <algorithm>

namespace Chiffres {
    /**
     *
     * @brief Possible states of a Chiffres wallet.
     *
     */
    enum class State {
        /// Deterministic state, every transaction is certain
        Circulation,
        /// Stochastic state, value mutates probabilistically
        Rest
    };


    /**
     *
     * @brief Ethical score associated with an actor or portfolio.
     *
     * This influences volatility and drift during mutation:
     * - Positive values (towards +1) reduce variance and add slight positive drift.
     * - Negative values (towards -1) increase variance and bias towards losses.
     *
     */
    struct EthicsScore {
        /// < Range expected in [-1.0, +1.0].
        double score = 0.0;
    };


    /**
     * @brief Memory of past wallet behavior.
     *
     * This structure accumulates a history of flows and mutations,
     * and biases future stochastic dynamics:
     *
     */
    struct Memory {
        /// amplifies variance in future mutations.
        double volatility_bias = 1.0;
        /// damps shocks, makes mutations gentler.
        double stability_bias = 1.0;
        /// counts the numbers of recorded events.
        std::uint64_t events = 0;
    };

    /**
     *
     * @brief Position within a natural or symbolic cycle.
     *
     * Typical interpretation: a normalized year cycle in [0,1].
     *
     * Example:
     * - 0.0  : Winter solstice (maximum instability for large fortunes).
     * - 0.25 : Spring equinox (balanced state).
     * - 0.5  : Summer solstice (peak expansion).
     * - 0.75 : Autumn equinox (contraction/balance).
     *
     */
    struct CyclePhase {
        /// < Normalized cycle position, [0,1].
        double phase = 0.0;
    };


    /**
     *
     * @class Chiffre
     *
     * @brief Core abstraction of the Chiffres monetary system.
     *
     * A Chiffres wallet is a living value container with two fundamental modes:
     * - In circulation, transactions are exact and deterministic.
     * - At rest, the value undergoes probabilistic mutations governed by:
     *   * Ethical influence (EthicsScore)
     *   * Natural cycles (CyclePhase)
     *   * Collective field feedback (Ether)
     *   * Its own memory of past behaviors (Memory)
     *
     * The class encapsulates both deterministic accounting and stochastic dynamics.
     *
     */
    class Chiffre {
    public:
        /**
         *
         * @brief Construct a wallet with an initial amount.
         *
         * @param initial Starting balance.
         */
        explicit Chiffre(double initial = 0.0);

        /**
         *
         * @brief Spend from the wallet (deterministic).
         *
         * @param amount Positive amount to subtract.
         *
         * @throws std::invalid_argument if amount < 0.
         *
         */
        void spend(double amount);

        /**
         *
         * @brief Receive into the wallet (deterministic).
         *
         * @param amount Positive amount to add.
         *
         * @throws std::invalid_argument if amount < 0.
         *
         */
        void receive(double amount);

        /**
         *
         * @brief Trigger a mutation when the wallet is at rest.
         *
         * Applies a stochastic multiplicative factor to the current balance.
         * The distribution is log-normal and influenced by:
         * - EthicsScore (stability/destabilization, drift bias)
         * - CyclePhase (time-based variance modulation)
         * - Memory (feedback from past events)
         * - Ether (collective field density, self-regulation)
         *
         * @param ethics Ethical score of the actor.
         * @param cycle  Position within the cycle of time/nature.
         * @return The delta applied to the balance (positive = gain, negative = loss).
         *
         * @note If the wallet is not in State::Rest, returns 0.0 and does nothing.
         *
         */
        double mutate(const EthicsScore &ethics, const CyclePhase &cycle);

        /// Set the current wallet state (Circulation or Rest).
        void set_state(State state) noexcept;

        /// Get current state.
        [[nodiscard]] State state() const noexcept;

        /// Get current balance.
        [[nodiscard]] double total() const noexcept;

        /// Access memory snapshot (read-only).
        [[nodiscard]] const Memory &memory() const noexcept;

        /**
         *
         * @brief Record a deterministic flow (called internally by spend/receive).
         *
         * Updates memory biases depending on:
         * - The direction of the flow (incoming/outgoing).
         * - The magnitude of the transaction.
         *
         * @param amount   Absolute amount of the flow.
         * @param incoming True if it is an incoming transaction.
         *
         */
        void record_flow(double amount, bool incoming);

    private:
        /**
         *
         * @brief Draw the multiplicative mutation factor.
         *
         * The factor is drawn from a log-normal distribution parameterized by:
         * - Memory (volatility and stability biases)
         * - EthicsScore (stabilizing/destabilizing effects)
         * - CyclePhase (variance boost depending on cycle position)
         * - Ether (global density, collective adjustment)
         *
         * @param ethics Ethical score context.
         * @param cycle  Cycle phase context.
         *
         * @return Multiplicative factor applied to the current balance.
         *
         */
        [[nodiscard]] double draw_mutation_factor(const EthicsScore &ethics, const CyclePhase &cycle) const;

        /// < Current wallet state.
        State state_ = State::Circulation;

        /// < Current balance.
        double total_;

        /// < Behavioral memory.
        Memory mem_;

        /// Shared RNG engine for stochastic processes.
        static inline std::mt19937_64 rng{std::random_device{}()};
    };
}
