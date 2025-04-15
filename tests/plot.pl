foo :-
    open_plot,
    send_plot($set title "sin cos curve"$),
    send_plot($set xlabel "x"$),
    send_plot($set ylabel "y"$),
    send_plot($set xtics 1$),
    send_plot($set ytics 0.5$),
    send_plot($plot sin(x),cos(x)$),
    close_plot.