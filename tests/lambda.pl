% lambda tests
test(identity) :- reduce([l(x,x), a], a).
test(constant) :- reduce([l(x,y), a], y).
test(nested1)  :- reduce([l(x, l(y, x)), a], l(y1, a)).
test(nested2)  :- reduce([[l(x, l(y, x)), a], b], a).
test(non_app)  :- reduce(a, a).
test(lambda_only) :- reduce(l(x, x), l(x, x)).
test(app_in_arg) :- reduce([l(x, [x, z]), [l(y, y), a]], [a, z]).
test(shadowing) :- reduce([l(x, l(x, x)), a], l(x1, x1)).
