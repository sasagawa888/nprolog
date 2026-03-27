
ex13(forall(x,
  imply(p(x),
    exist(y,
      and(imply(q(x,y), p(a)),
          imply(q(y,a), p(x)))
)))).