# AtFirst

# Common
Please do as follows:

```
sudo make install
```

Some libraries need to be compiled. They use a C wrapper and will not work unless compiled. 
Please do as follows:

```
make prolog
```

By default, the installation is kept light by compiling without the -flto option. To enable faster performance with -flto, please recompile as follows:

```
sudo make clean
sudo make install USE_FLTO=1

```

To enable GDB with -g -O0 option.

```
sudo make clean
sudo make install USE_GDB=1

```

# Dosuments
This document provides an overview of many documents. Please read it first.

![UserManual](MANUAL.md)
This is the user manual for N-Prolog.

![Chacker](CHECKER.md)
This is a description of the Prolog code checker library using static analysis.

![CLPFD](CLPFD.md)
This is a description of the CLP(FD) library.

![Compiler](COMPILER.md)
This is a description of the N-Prolog compiler.

![Curl](CURL.md)
This is a description of the HTTPS functionality with encryption using curl.

![DCG](DCG.md)
This is a description of the DCG library.

![Edlog](EDLOG.md)
This is a description of Edlog, a CUI editor dedicated to N-Prolog.

![History](HISTORY.md)
This is the development history of N-Prolog.

![JSON](JSON.md)
This is a description of the JSON library.

![List](LIST.md)
This is a description of the List library.

![Module](MODULE.md)
This is a description of the module functionality in N-Prolog.

![MultipleWorld](MPW.md)
This is a description of Professor Hideyuki Nakashima's multiple world mechanism.

![OpenGL](OPENGL.md)
This is a library for interfacing with OpenGL.

![Parallel1](PARA1.md)
This is a description of the distributed parallel features in N-Prolog.

![Parallel2](PARA2.md)
This is a description of the multi-thread parallel features in N-Prolog.

![Plot](PLOT.md)
This is a library for interfacing with Gnuplot.

![Python](PYTHON.md)
This is a library for using TensorFlow via Python.

![Math](MATH.md)
This is a description of the Math library.

![SuperSet](SUPERSET.md)
This is a description of ISO-style predicates and other modern extended predicates.

![TCL/TK](TCLTK.md)
This is a library for interfacing with Tcl/Tk.

![TCP/IP](TCPIP.md)
This is a description of extended predicates for TCP/IP communication.

![Unicode](UNICODE.md)
This is a description of how Unicode is handled in N-Prolog.

![WiringPI](WIRINGPI.md)
On Raspberry Pi, predicates for WiringPi are installed. This is their description.
