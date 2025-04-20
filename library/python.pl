% library for tensorflow with python

cdeclare($#include <stdio.h>$).
cdeclare($char command[STRSIZE];
          char str[STRSIZE];
          char substr[STRSIZE];
          FILE *fp;$).

send_python(File,Res) :-
    cinline($strcpy(command,"python3 ");
             strcat(command,Jgetname(Jderef(varFile,th)));
             printf("%s",command);
             fp = popen(command, "r");
             if (fp == NULL) {return NO;}
             str[0] = '\0';
             while(fgets(substr, sizeof(substr), fp) != NULL){
                strcat(str,substr);
             }
             pclose(fp);
             printf("%s",str);
             if(Junify(varRes,Jmakestr(str),th)==YES)
             return(Jexec_all(rest,Jget_sp(th),th));$).

