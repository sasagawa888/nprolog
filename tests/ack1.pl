
ack(M,N,X) :-
cinline($ //ackermann function
          int a(int m, int n){
              if(m==0) return(n+1);
              else if(n==0) return(a(m-1,1));
              else return(a(m-1,a(m,n-1)));
          }
          int m = Jget_int(Jderef(varM,th));
          int n = Jget_int(Jderef(varN,th));
          int res = a(m,n);
          Junify(varX,Jmakeint(res),th);
          return(Jexec_all(rest,Jget_sp(th),th)); $).