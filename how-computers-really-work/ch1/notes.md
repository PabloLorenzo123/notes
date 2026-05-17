# Definition of computer
A machine that can be programmable. ex: laptop, server, phone even a microwave. it's a machine that can follow instructions, and those instructions can be programmed.

# Differeance between Analog and Digital.
Analog tools use analogies to describe or to measure physical attributes such as weight, temperature and distance. e.g the scale number isn't the body's mass, is a representation of it. The termometer mark isn't the temperature, it's a representation of it, representation we then use to meausure the attribute. These tools use at its core an analogy, the termometer use the mercury volume which is affected by temperatura to represent the temperature.

On the other hand, digital means represent something not based on analogy, but based on something with a finite set of values. Computers are digital tools, everything is a series of 0s and 1s.

Engineers may use the word analog wrong, the may call something analog simply because it is not digital.

## CHATGPT observation
Your understanding is mostly correct, but a few parts can be sharpened and made more precise — especially the definition of *analog*.

The key idea is:

* **Analog** = representation through a continuously varying physical quantity.
* **Digital** = representation through discrete values (finite states/symbols).

A thermometer is a great example because the mercury expands *continuously* with temperature. The height of the mercury is *analogous* to the temperature.

Your notes are already close, but some wording could accidentally imply that “analogy” means “metaphor” or “comparison” in the everyday sense. In engineering, *analog* means that one physical quantity varies in correspondence with another.

A cleaner version of your notes would be:

---

# Difference Between Analog and Digital

Analog systems represent information using continuously varying physical quantities.

For example:

* In a mercury thermometer, the mercury height changes continuously with temperature.
* In an analog scale, the position of the needle changes continuously with weight.

The measurement is not the physical attribute itself, but a representation of it through another physical property that behaves similarly or proportionally.

An analog system therefore works through physical correspondence between quantities.

Digital systems, on the other hand, represent information using discrete values or symbols.

Computers are digital systems because they represent information using finite states — typically 0s and 1s.

Instead of continuously varying values, digital systems encode information into distinct steps or states.

In engineering, people sometimes casually use “analog” to mean “not digital,” although more precisely analog refers to continuous representation.

---

One subtle correction:

> “digital means represent something not based on analogy”

That is *partially* true, but not fully. Digital systems still represent reality — they just do it using discrete symbols instead of continuous physical correspondence.

For example:

* A digital thermometer still represents temperature.
* But instead of mercury height continuously changing, it converts the temperature into numbers like `25°C`.

So the real distinction is:

* **continuous vs discrete representation**
* not “representation vs no representation.”

Your intuition is definitely on the right track though. The first chapter of How Computers Really Work is trying to build exactly that mental model.

## Numeric systems.
Decimal (digits), Binary (bits) and hexadecimal, octals were explored. Binary numers cna use the rpefix 0b, and hexadecimal 0x. these are position based numbers.

Hexadecimal is useful, because it's easy to convert from hexadecimal to binary and viceversa. because each nibble (4 bits) of a byte (8 bits) corresponds to a hexadecimal digit. by hexadecimal being shorter and easier to convert to binary, its preffered to work with over decimal system for engineers.

ex: 11110000 -> hexadecimal: F0 (instant), now from binary to decimal you better bring a calculator or do mental math.

