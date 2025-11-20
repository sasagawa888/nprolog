Simple Graphics API using /dev/fb0

This is a simple graphics system utilizing /dev/fb0. It is implemented as a built-in function. Below are the available functions and their specifications.

To use this feature, you need to switch to a physical terminal. You can switch by pressing CTRL+ALT+F3. To return to your original session, press CTRL+ALT+F7.

![](graph0.png)

You need to use sudo when starting it.

```
sudo npl
```

The default font on the TTY is small and hard to read. Therefore, please change the settings as follows next.

```
sudo dpkg-reconfigure console-setup
```
- UTF8
- Terminus
- 16*32

![](graph1.png)
![](graph2.png)


```
% Initialize graphics
gr_open :- 
    % Open the framebuffer
    true.  % Return true if successful, false otherwise

% Close graphics
gr_close :-
    % Close the framebuffer
    true.

% Clear the screen with a specified color
gr_cls(Color) :-
    % Color can be black, blue, red, magenta, green, cyan, yellow, white
    % Screen clearing operation
    true.

% Draw a single pixel
gr_pset(X, Y, Color) :-
    integer(X), integer(Y),
    % Pixel drawing operation
    true.

% Draw a circle
gr_circle(CX, CY, R, Color) :-
    integer(CX), integer(CY), integer(R),
    % Circle drawing operation
    true.
gr_circle(CX, CY, R, Color, fill) :-
    integer(CX), integer(CY), integer(R),
    % Circle drawing with fill
    true.

% Draw a rectangle
gr_rect(X0, Y0, X1, Y1, Color) :-
    integer(X0), integer(Y0), integer(X1), integer(Y1),
    % Rectangle drawing operation
    true.
gr_rect(X0, Y0, X1, Y1, Color, fill) :-
    integer(X0), integer(Y0), integer(X1), integer(Y1),
    % Rectangle drawing with fill
    true.

% Draw a line
gr_line(X0, Y0, X1, Y1, Color) :-
    integer(X0), integer(Y0), integer(X1), integer(Y1),
    % Line drawing operation
    true.
```