% library for tensorflow with python

cdeclare($#include <stdio.h>$).
cdeclare($char command[STRSIZE];
          char response[STRSIZE]
          char result[128];$).

send_python(File,Res) :-
    cinline($strcpy(command,"python3 ");
             strcat(command,Jgetname(Jderef(File,th)));
             FILE *fp = popen(command, "r");
             if (fp == NULL) {return NO;}
             response[0] = '\0';
             while (fgets(result, sizeof(result), fp) != NULL) {
                strcat(response,result);
             }
             fclose(fp);
             if(Junify(Res,Jmakestr(response))==YES)
             return(Jexec_all(rest,Jget_sp(th),th));$).

