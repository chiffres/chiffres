# Chiffres – A Sentient Economic System

> *“Value is alive. Certain in circulation, mutable at rest.
> A cosmic gamble influenced by ethics, cycles, and collective memory.”*

[documentation](https://chiffres.github.io/chiffres/)

##  Vision

**Chiffres** is not just a currency – it is a **living system**.
Unlike traditional money (stable when hoarded, inert when circulating), Chiffres reverses the paradigm:

* **Circulation = Certainty**
  When you spend or receive, the value is exact. 100 Chiffres spent = 100 Chiffres received.
  But *how* you spend matters:
   * **Local good** → stabilizes your Chiffres.
   * **Risky project** → makes them more volatile in the future.
     Thus, the currency **remembers how it has circulated**.
* **Rest = Gamble**
  When hoarded, Chiffres enter a quantum-like state.
  Their value mutates unpredictably according to:
   * **Ethics / GEMs** (virtuous actions stabilize, destructive ones destabilize).
   * **Cycles of Time** (solstices, seasons, years).
   * **Weights / Elements** (small fortunes = wind/water, large fortunes = earth/fire).
   * **Collective Ether** (if many stagnate, all are dragged down; if all circulate, everyone rises).

## Core Principles

1. **Circulation as Memory**
   * Spending leaves an imprint. The past of your Chiffres influences their volatility.
2. **GEMs as Catalysts**
   * Linked to concrete actions (planting a tree, donating, collaborating).
   * Reduce losses or amplify gains in the cosmic gamble.
3. **Temporal Cycles**
   * Mutations follow natural rhythms.
   * At the winter solstice, great fortunes face monumental risks.
   * At equinoxes, the system seeks balance.
4. **The Collective Ether**
   * Gains “consume” the Ether (making Chiffres rarer, everyone benefits).
   * Losses “dissolve” into the Ether (making it thicker, everyone loses a bit).
   * When too many stagnate, the value decreases → inciting action.
5. **Symbolic Weights**
   * **Light weights (small sums):** wind, water – fast, playful, changeable.
   * **Heavy weights (large sums):** earth, fire – slow, transformative, existential.
6. **Council of Chiffres (Governance)**
   * Open assembly adjusting parameters (mutation frequency, Ether weights).
   * Decisions themselves are gambles – they may backfire if the Ether shifts.

## Technical Overview

* **Language:** C++20
* **Core:** `Chiffres` (wallets that mutate) + `Ether` (collective field)
* **States:**
   * `Circulation` (deterministic transactions)
   * `Rest` (stochastic mutation via log-normal distribution)
* **Modifiers:**
   * `EthicsScore` → \[-1, +1]
   * `CyclePhase` → \[0,1) annual phase
   * `Memory` → volatility/stability biases
   * `GEMs` (planned extension)

## Build & Run

```bash
git clone https://github.com/chiffres/chiffres
cd chiffres
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/chiffres_demo
```

## Example

```c++
#include <Chiffres.h>
#include <iostream>

int main() {
    Chiffres wallet(1000.0);

    wallet.receive(200.0);  // certainty
    wallet.spend(50.0);

    wallet.set_state(State::Rest);
    EthicsScore ethics{+0.6}; // good actions
    CyclePhase cycle{0.0};    // winter solstice

    double delta = wallet.mutate(ethics, cycle);
    std::cout << "Mutation: " << delta
              << " | Total: " << wallet.total() << "\n";
}
```

## Roadmap

* [x] Core engine (`Circulation`, `Rest`, `Ether`, `Memory`)
* [ ] GEMs / Catalysts
* [ ] Temporal cycles (calendar integration)
* [ ] Elemental Weights (linking fortunes to nature)
* [ ] Council of Chiffres (governance layer)
* [ ] Visualization / Simulation tools

## License

AGPL-3.0 – free to use, share, and improve.

If you build upon Chiffres, share it back with the community