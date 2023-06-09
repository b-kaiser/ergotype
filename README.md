# ergotype

A touch typing trainer designed to encourage optimal fingerings. 

## Foundational Ideas

- Typing accuracy leads to typing speed. 
- Optimal fingering depends on the word.
- Any four consecutive keys in a row of a keyboard are a homerow (e.g. `uiop` and  `iop[` on qwerty).
- Homerows can easily be reached and typed (small movements of the wrist are helpful).
- Single hand exercises are useful (not exclusively, of course).

## Build and Run
Depends on ncurses to build. Please open an issue if it doesn't build on your os/machine or you have suggestions on how to improve the building process. As a last resortand you may use `make LOCAL_NCURSES=true` instead of `make` to automatically download and install ncurses locally to `~/.local` and build ergotype against that.

Currently, needs a terminal capable of colors, but that dependency is soon going to be removed. 

```
git clone https://github.com/b-kaiser/ergotype.git
cd ergotype
make 
./ergotype
```
 
## TODOs

- Improve exercises and their order.
- Add exercises with dictionary words.
- Add both-hands exercises.
- Add exercises for speed.
- Make more portable and improve build process.
- Enable different languages and keyboard layouts.
- Get rid of hard-coded stuff in code.
- Clean up code.
