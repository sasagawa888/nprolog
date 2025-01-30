% verfication tests

:- catch(length([],1.1),error(type_error(integer,1.1),length/2),true).
