#pragma once
#include <algorithm>

namespace Chiffres {

    /**
     *
     * @class Ether
     *
     * @brief Collective monetary field in the Chiffres system.
     *
     * Ether represents the "atmosphere" of value shared by all Chiffres.
     * It reacts to individual gains and losses, and in turn influences
     * the probability space of all future mutations.
     *
     * Core principles:
     * - When a wallet gains in rest, Ether is "consumed" → density decreases,
     *   value of all Chiffres increases slightly (rarer field).
     * - When a wallet loses in rest, Ether "dissolves" → density increases;
     *   The value of all Chiffres decreases slightly (thicker field).
     *
     * Ether acts as a global coupling mechanism: no mutation is purely individual.
     * The system becomes organically self-regulating.
     *
     */
    class Ether {
    public:
        /**
         *
         * @brief Access the unique global instance (Meyers' singleton).
         *
         * @return Reference to the Ether instance.
         *
         * @note Ether is unique by design. All wallets share the same field.
         *
         */
        static Ether &instance();

        /**
         *
         * @brief Get current Ether density.
         *
         * @return Current density in [min_density, max_density].
         *
         * - 1.0 is neutral density (baseline).
         * - <1.0 means Ether has been consumed (rarer, boosting value).
         * - >1.0 means Ether has thickened (abundant, reducing value).
         *
         */
        [[nodiscard]] double density() const noexcept;

        /**
         *
         * @brief Consume Ether when a gain occurs.
         *
         * @param amount Positive gain value (will be clamped).
         *
         * Consuming reduces Ether density, bounded by min_density.
         *
         * This makes Chiffres globally scarcer → positive drift.
         *
         */
        void consume(double amount) noexcept;

        /**
         *
         * @brief Dissolve Ether when a loss occurs.
         *
         * @param amount Positive loss value (will be clamped).
         *
         * Dissolving increases Ether density, bounded by max_density.
         *
         * This makes Chiffres globally thicker → negative drift.
         *
         */
        void dissolve(double amount) noexcept;

    private:

        /// Minimum density bound (absolute rarity limit).
        static constexpr double min_density = 0.50;

        /// Maximum density bound (absolute abundance limit).
        static constexpr double max_density = 2.00;

        /// Sensitivity coefficient (how strongly Ether reacts per unit amount).
        static constexpr double k = 1e-6;

        /// Normalization cap (avoids extreme effects for very large amounts).
        static constexpr double cap = 1e12;

        /// Current Ether density (initialized neutral).
        double density_ = 1.0;
    };
}
