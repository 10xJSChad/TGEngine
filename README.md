# TGEngine
### Heavy W.I.P, do not use for now.
TGEngine is a game engine for the development of terminal based games, it aims to provide developers with the ability to focus entirely on developing their games, leaving all the 'lower level' functionality like rendering, animating, input, and audio to be handled by TGEngine.


#### Linux Dependencies:
* ncurses if using the TGE Input Handler

#### Windows Dependencies:
* There is no Windows support yet, this will come once TGE is functional enough to develop games with.


## Important!
* TGE does not work with C++ right now, but it will as soon as the core functionality is implemented and I can move on to Windows and C++ compatibility. I hope to be able to create a proper C++ class wrapper for TGE as well, since it just feels a bit weird to use C++ with TGE at all given that everything is more or less built on structs and function pointers, which could all be replaced with C++ classes for a more native feeling C++ experience.
* The whole engine is currently also header only, I find this gives me a more enjoyable development experience, stable releases will likely *not* be header only.

## Contributor Information
* The naming is currently all over the place and frankly a bit too inconsistent for my liking, but I've decided to not get hung up in all of that, so I'm kind of just letting it go for now until TGE is stable enough to develop a few demo games.
* I use macros *extensively*, please do not rewrite the macros into functions for no reason other than believing macros are inherently bad. I know there are a lot of people who despise them, but I personally do not and see no reason to stop using them the way I do throughout TGE.
* Do not add more dependencies.

### Style
Please try to keep your style as consistent with the already existing TGE style as possible, the style is very simple and there are basically only a couple of things to keep in mind.

#### Functions
**Declaration**
```c
void my_function(int arg1, int arg2);
```

**Definition**
```c
void
my_function(
    int arg1,
    int arg2)
{
  // code
}
```


#### Switch statements
Keep switch statements in this style, you may use one line cases if they're very short.
```c
switch(some_flag)
{
case FLAG_ONE:
    some_code();
    break;
   
case FLAG_TWO:
    some_more_code();
    break;
    
case default:
    break;
}
```

#### Everything else should never have the opening bracket on a new line!
**Valid Example**
```c
void
my_function(
    int arg1,
    int arg2)
{
  if (some_condition) {
    // code
  }
}
```

**INVALID Example**
```c
void
my_function(
    int arg1,
    int arg2)
{
  if (some_condition) 
  {
    // code
  }
}
```
