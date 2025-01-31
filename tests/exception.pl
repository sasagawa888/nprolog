% verfication tests

:- catch(length([],1.1),error(type_error(integer,1.1),length/2),true).
:- catch(length(a,X),error(type_error(list,a),length/2),true).
:- catch(length([1|2],X),error(type_error(list,[1|2]),length/2),true).
:- catch(length([1],-1),error(domain_error(not_less_than_zero,-1),length/2),true).
:- catch(length([],0,1),error(existence_error(predicate,length/3),length/3),true).
:- catch(length(X,X),error(instantiation_error,length/2),true).

:- catch(repeat(1),error(existence_error(predicate,repeat/1),repeat/1),true).
:- catch(=(1,2,3),error(existence_error(predicate,(=)/3),(=)/3),true).
:- catch(\=(1,2,3),error(existence_error(predicate,(\=)/3),(\=)/3),true).

:- catch(write(X,1),error(instantiation_error,write/2),true).
:- catch(write(1,1),error(domain_error(stream_or_alias,1),write/2),true).
:- catch(display(X,1),error(instantiation_error,display/2),true).
:- catch(display(1,1),error(domain_error(stream_or_alias,1),display/2),true).
:- catch(writeq(X,1),error(instantiation_error,writeq/2),true).
:- catch(writeq(1,1),error(domain_error(stream_or_alias,1),writeq/2),true).

:- catch(nl(1),error(domain_error(stream_or_alias,1),nl/1),true).
:- catch(nl(1,2),error(existence_error(predicate,nl/2),nl/2),true).