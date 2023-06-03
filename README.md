# TGEngine
### Heavy W.I.P, do not use for now.
TGEngine is a game engine for the development of terminal based games, it aims to provide developers with the ability to focus entirely on developing their games, leaving all the 'lower level' functionality like rendering, animating, input, and audio to be handled by TGEngine.

### Important
* TGE does not work with C++ right now, but it will as soon as the core functionality is implemented and I can move on to Windows and C++ compatibility. I hope to be able to create a proper C++ class wrapper for TGE as well, since it just feels a bit weird to use C++ with TGE at all given that everything is more or less built on structs and function pointers, which could all be replaced with C++ classes for a more native feeling C++ experience.
* The whole engine is currently also header only, I find this gives me a more enjoyable development experience, stable releases will likely *not* be header only.


#### Linux Dependencies:
* ncurses if using the TGE Input Handler


#### Windows Dependencies:
* There is no Windows support yet, this will come once TGE is functional enough to develop games with.
