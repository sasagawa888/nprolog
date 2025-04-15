% library for GNU-plot

cdeclare($#include <stdio.h>
          FILE *gp;$).

open_plot :-
    cinline($gp = popen("gnuplot -persist","w");
              return(Jexec_all(rest,Jget_sp(th),th));$).

send_plot(Msg) :-
    send_plot1(Msg).

send_plot1(Msg) :-
    cinline($fprintf(gp, "%s\n", Jgetname(Jderef(varMsg,th)));
             fflush(gp);
             return(Jexec_all(rest,Jget_sp(th),th));$).

close_plot :-
    cinline($pclose(gp);
             return(Jexec_all(rest,Jget_sp(th),th));$).
