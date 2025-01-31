% verfication tests

:- catch(length([],1.1),error(type_error(integer,1.1),length/2),true).
:- catch(length(a,X),error(type_error(list,a),length/2),true).
:- catch(length([1|2],X),error(type_error(list,[1|2]),length/2),true).
:- catch(length([1],-1),error(domain_error(not_less_than_zero,-1),length/2),true).
:- catch(length([],0,1),error(existence_error(predicate,length/3),length/3),true).
:- catch(length(X,X),error(instantiation_error,length/2),true).

:- catch(repeat(1),error(existence_error(predicate,repeat/1),repeat/1),true).