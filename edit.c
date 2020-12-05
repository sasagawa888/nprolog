#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include "npl.h"


//----editor----
void setcolor(int n){
        switch(n){
                case 0: ESCFBLACK; break;
                case 1: ESCFRED; break;
                case 2: ESCFGREEN; break;
                case 3: ESCFYELLOW; break;
                case 4: ESCFBLUE; break;
                case 5: ESCFMAGENTA; break;
                case 6: ESCFCYAN; break;
                case 7: ESCFWHITE; break;
                default: ESCFWHITE; break;
        }
        return;
}


int getch(){
    struct termios oldt,newt;
    int ch;

    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return(ch);
}

//------------REPL read-line-----------------
void display_buffer(){
    int col,type;

    ESCMVLEFT(left_margin);
    ESCCLSL;
    col = 0;

    while(buffer[col][0] != EOL &&
          buffer[col][0] != NUL){

          if(ed_incomment != -1 && line >= ed_incomment){ //comment #|...|#
             ESCBOLD;
             setcolor(ed_comment_color);
             while(buffer[col][0] != EOL &&
                   buffer[col][0] != NUL){
                       printf("%c", buffer[col][0]);
                       col++;
                       if(buffer[col-2][0] == '|' &&
                          buffer[col-1][0] == '#'){
                             ed_incomment = -1;
                             ESCRST;
                             ESCFORG;
                             break;
                       }
             }
             ESCRST;
             ESCFORG;
         }
         else if(buffer[col][0] == ' ' ||
                 buffer[col][0] == '(' ||
                 buffer[col][0] == ')' ||
                 buffer[col][0] == '[' ||
                 buffer[col][0] == ']' ||
                 buffer[col][0] == '{' ||
                 buffer[col][0] == '}' ||
                 buffer[col][0] == ',' ||
                 buffer[col][0] == ';' ||
                 buffer[col][0] == '.' ){
            printf("%c", buffer[col][0]);
            col++;
         }
         else{
            type = check_token_buffer(col);
            if(type == 1){//operator
                ESCBOLD;
                setcolor(ed_operator_color);
                while(buffer[col][0] != ' ' &&
                      buffer[col][0] != '(' &&
                      buffer[col][0] != ')' &&
                      buffer[col][0] != '[' &&
                      buffer[col][0] != ']' &&
                      buffer[col][0] != ',' &&
                      buffer[col][0] != ';' &&
                      buffer[col][0] != '.' &&
                      buffer[col][0] != '\'' &&
                      buffer[col][0] != NUL &&
                      buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                }
                ESCRST;
                ESCFORG;
                }
                else if(type == 2){//builtin
                        ESCBOLD;
                    setcolor(ed_builtin_color);
                    while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != '[' &&
                          buffer[col][0] != ']' &&
                          buffer[col][0] != ',' &&
                          buffer[col][0] != ';' &&
                          buffer[col][0] != '.' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                        }
                        ESCRST;
                        ESCFORG;
                }
                else if(type == 3){// '...'
                    ESCBOLD;
                    setcolor(ed_quote_color);
                    printf("%c", buffer[col][0]);
                    col++;
                    while(buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                        if(buffer[col-1][0] == '\'')
                            break;
                   }
                   ESCRST;
                   ESCFORG;

               }
               else if(type == 4){// coment %
                   ESCBOLD;
                   setcolor(ed_comment_color);
                   while(buffer[col][0] != NUL &&
                         buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 5){
                   ESCBOLD;
                   setcolor(ed_extended_color);
                   while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != '[' &&
                          buffer[col][0] != ']' &&
                          buffer[col][0] != ',' &&
                          buffer[col][0] != ';' &&
                          buffer[col][0] != '.' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                        printf("%c", buffer[col][0]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 6){ //function
                   ESCBOLD;
                   setcolor(ed_function_color);
                   while(isalpha(buffer[col][0]) ||
                         buffer[col][0] == '_'   ||
                         isdigit(buffer[col][0]) ){
                        printf("%c", buffer[col][0]);
                        col++;
                   }
                   ESCRST;
                   ESCFORG;
               }
               else if(type == 7){ //comment /*...*/
                   ESCBOLD;
                   setcolor(ed_function_color);
                   ed_incomment = line;
                   while(buffer[col][0] != EOL &&
                         buffer[col][0] != NUL){
                             printf("%c", buffer[col][0]);
                             col++;
                             if(buffer[col-2][0] == '/' &&
                                buffer[col-1][0] == '*'){
                                 ed_incomment = -1;
                                 ESCRST;
                                 ESCFORG;
                                 break;
                             }
                   }
               }
               else{
                    while(buffer[col][0] != ' ' &&
                          buffer[col][0] != '(' &&
                          buffer[col][0] != ')' &&
                          buffer[col][0] != ',' &&
                          buffer[col][0] != ';' &&
                          buffer[col][0] != '.' &&
                          buffer[col][0] != NUL &&
                          buffer[col][0] != EOL){
                       printf("%c", buffer[col][0]);
                       col++;
                    }
               }
            }
        }
    ESCRST;
    return;
}

int check_token_buffer(int col){
    char str[BUFSIZE];
    int pos,i;

    pos = 0;
    if(buffer[col][0] == '\'')
        return(3); //quote token
    else if(buffer[col][0] == '%')
       return(4); //comment token
    else if(isalpha(buffer[col][0])){
       while(isalpha(buffer[col][0])  ||
             buffer[col][0] == '_' ||
             isdigit(buffer[col][0])){
          str[pos] = buffer[col][0];
          col++;
          pos++;
        }
        str[pos] = NUL;
        // for raspberry GCC to avoid fleeze 'setup' word
        if(str[0] == 's' &&
           str[1] == 'e' &&
           str[2] == 't' &&
           str[3] == 'u' &&
           str[4] == 'p' &&
           str[5] == NUL)
            return(0);
    }
    else if(buffer[col][0] == '_'){ //atom
       while(isalpha(buffer[col][0])  ||
             buffer[col][0] == '_' ||
             isdigit(buffer[col][0])){
          str[pos] = buffer[col][0];
          col++;
          pos++;
        }
        str[pos] = NUL;
    }
    else if(isatomch(buffer[col][0])){ //operator
       while(isatomch(buffer[col][0])){
          str[pos] = buffer[col][0];
          col++;
          pos++;
       }
       str[pos] = NUL;
       if(str[0] == '/' && str[1] == '*')
          return(7); //comment /*...*/
    }
    str[pos] = NUL;
    if(pos == 0) //null token
        return(0);

    for(i=0; i<OPERATOR_NUMBER; i++){
        if(strcmp(operator[i],str) == 0){
            return(1); //operator token
        }
    }
    for(i=0; i<BUILTIN_NUMBER; i++){
        if(strcmp(builtin[i],str) == 0){
            return(2); //builtin token
        }
    }
    for(i=0; i<COMPILED_NUMBER; i++){
        if(strcmp(compiled[i],str) == 0){
            return(2); //compiled token same as builtin
        }
    }
    for(i=0; i<EXTENDED_NUMBER; i++){
        if(strcmp(extended[i],str) == 0){
            return(5); //extended token
        }
    }
    for(i=0; i<FUNCTION_NUMBER; i++){
        if(strcmp(function[i],str) == 0){
            return(6); //function token
        }
    }
    return(0);
}



int findlparen_buffer(int col){
    int nest;

    col--;
    nest = 0;
    while(col >= 0){
        if(buffer[col][0] == '(' && nest == 0)
            break;
        else if(buffer[col][0] == ')')
            nest++;
        else if(buffer[col][0] == '(')
            nest--;

        col--;
    }
    return(col);
}

int findrparen_buffer(int col){
    int nest,limit;

    col++;
    nest = 0;
    for(limit=0;limit<BUFSIZE;limit++)
        if(buffer[limit][0] == 0)
            break;

    while(col <= limit){
        if(buffer[col][0] == ')' && nest == 0)
            break;
        else if(buffer[col][0] == '(')
            nest++;
        else if(buffer[col][0] == ')')
            nest--;

        col++;
    }
    if(col > limit)
       return(-1);
    else
       return(col);
}

int findlbracket_buffer(int col){
    int nest;

    col--;
    nest = 0;
    while(col >= 0){
        if(buffer[col][0] == '[' && nest == 0)
            break;
        else if(buffer[col][0] == ']')
            nest++;
        else if(buffer[col][0] == '[')
            nest--;

        col--;
    }
    return(col);
}

int findrbracket_buffer(int col){
    int nest,limit;

    col++;
    nest = 0;
    for(limit=0;limit<BUFSIZE;limit++)
        if(buffer[limit][0] == 0)
            break;

    while(col <= limit){
        if(buffer[col][0] == ']' && nest == 0)
            break;
        else if(buffer[col][0] == '[')
            nest++;
        else if(buffer[col][0] == ']')
            nest--;

        col++;
    }
    if(col > limit)
       return(-1);
    else
       return(col);
}


void emphasis_rparen_buffer(int col){
    int pos;

    if(buffer[col][0] != '(')
        return;
    pos = findrparen_buffer(col);
    if(pos < 0)
        return;

    ESCMVLEFT(count_col_buffer(col)+left_margin);
    ESCBCYAN;
    printf("(");
    ESCBORG;
    ESCMVLEFT(count_col_buffer(pos)+left_margin);
    ESCBCYAN;
    printf(")");
    ESCBORG;
    ed_rparen_col = pos;
    ed_lparen_col = col;
    ESCMVLEFT(count_col_buffer(col)+left_margin);
}


void emphasis_lparen_buffer(int col){
    int pos;

    if(buffer[col][0] != ')')
        return;

    pos = findlparen_buffer(col);
    if(pos < 0)
        return;

    ESCMVLEFT(count_col_buffer(col)+left_margin);
    ESCBCYAN;
    printf(")");
    ESCBORG;
    ESCMVLEFT(count_col_buffer(pos)+left_margin);
    ESCBCYAN;
    printf("(");
    ESCBORG;
    ed_rparen_col = col;
    ed_lparen_col = pos;
    ESCMVLEFT(count_col_buffer(col)+left_margin);
}


void emphasis_rbracket_buffer(int col){
    int pos;

    if(buffer[col][0] != '[')
        return;
    pos = findrbracket_buffer(col);
    if(pos < 0)
        return;

    ESCMVLEFT(count_col_buffer(col)+left_margin);
    ESCBCYAN;
    printf("[");
    ESCBORG;
    ESCMVLEFT(count_col_buffer(pos)+left_margin);
    ESCBCYAN;
    printf("]");
    ESCBORG;
    ed_rbracket_col = pos;
    ed_lbracket_col = col;
    ESCMVLEFT(count_col_buffer(col)+left_margin);
}


void emphasis_lbracket_buffer(int col){
    int pos;

    if(buffer[col][0] != ']')
        return;

    pos = findlbracket_buffer(col);
    if(pos < 0)
        return;

    ESCMVLEFT(count_col_buffer(col)+left_margin);
    ESCBCYAN;
    printf("]");
    ESCBORG;
    ESCMVLEFT(count_col_buffer(pos)+left_margin);
    ESCBCYAN;
    printf("[");
    ESCBORG;
    ed_rbracket_col = col;
    ed_lbracket_col = pos;
    ESCMVLEFT(count_col_buffer(col)+left_margin);
}

void reset_paren_bracket_buffer(){
    ed_lparen_col = -1;
    ed_rparen_col = -1;
    ed_lbracket_col = -1;
    ed_rbracket_col = -1;
}

void restore_paren_buffer(int col){

    if(ed_lparen_col != -1){
        ESCMVLEFT(count_col_buffer(ed_lparen_col)+left_margin);
        ESCBORG;
        printf("(");
        ed_lparen_col = -1;
    }
    if(ed_rparen_col != -1){
        ESCMVLEFT(count_col_buffer(ed_rparen_col)+left_margin);
        ESCBORG;
        printf(")");
        ed_rparen_col = -1;
    }
    ESCMVLEFT(count_col_buffer(col)+left_margin);
}


void restore_bracket_buffer(int col){

    if(ed_lbracket_col != -1){
        ESCMVLEFT(count_col_buffer(ed_lbracket_col)+left_margin);
        ESCBORG;
        printf("[");
        ed_lbracket_col = -1;
    }
    if(ed_rbracket_col != -1){
        ESCMVLEFT(count_col_buffer(ed_rbracket_col)+left_margin);
        ESCBORG;
        printf("]");
        ed_rbracket_col = -1;
    }
    ESCMVLEFT(count_col_buffer(col)+left_margin);
}


char *get_fragment_buffer(int col){
    static char str[80];
    int pos;

    while(col >= 0 &&
          buffer[col][0] != ' ' &&
          buffer[col][0] != '(' &&
          buffer[col][0] != ')'){
                col--;
        }
        col++;
        pos = 0;
    while(buffer[col][0] != ' ' &&
          buffer[col][0] != '(' &&
          buffer[col][0] >= ' '){
        str[pos] = buffer[col][0];
        col++;
        pos++;
    }
    str[pos] = NUL;
    return(str);
}


void find_candidate_buffer(int col){
    char* str;
    int i;

    str = get_fragment_buffer(col);
    ed_candidate_pt = 0;
    if(str[0] == NUL)
        return;
    for(i=0;i<OPERATOR_NUMBER;i++){
        if(strstr(operator[i],str) !=NULL && operator[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],operator[i]);
                        ed_candidate_pt++;
        }
    }
    for(i=0;i<BUILTIN_NUMBER;i++){
        if(strstr(builtin[i],str) !=NULL && builtin[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],builtin[i]);
                        ed_candidate_pt++;
        }
    }
    for(i=0;i<COMPILED_NUMBER;i++){
        if(strstr(compiled[i],str) !=NULL && compiled[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],compiled[i]);
                        ed_candidate_pt++;
        }
    }
    for(i=0;i<EXTENDED_NUMBER;i++){
        if(strstr(extended[i],str) !=NULL && extended[i][0] == str[0]){
            strcpy(ed_candidate[ed_candidate_pt],extended[i]);
                        ed_candidate_pt++;
        }
    }
    return;
}

int replace_fragment_buffer(char* newstr, int col){
    char* oldstr;
    int m,n;

    oldstr = get_fragment_buffer(col);
    m = strlen(oldstr);
    n = strlen(newstr);
    col--;
    while(m>0){
        backspace_buffer(col);
        m--;
        col--;
    }
    col++;
    while(n>0){
        insertcol_buffer(col);
        buffer[col][0] = *newstr;
        col++;
        newstr++;
        n--;
    }

    return(col);
}

void backspace_buffer(int col){
    int i;

    for(i=col;i<BUFSIZE;i++)
        buffer[i][0] = buffer[i+1][0];
}

void insertcol_buffer(int col){
    int i;

    for(i=BUFSIZE-1;i>col;i--)
        buffer[i][0] = buffer[i-1][0];
}

int count_col_buffer(int x){
    int pysical_col,logical_col;

    pysical_col = 0;
    logical_col = 0;
    while(pysical_col < x){
        if(mode_flag == 0 && iskanji(buffer[pysical_col][0])){
            pysical_col = pysical_col + 2;
            logical_col = logical_col + 2;
        }
        else if(mode_flag == 1 && isUni2(buffer[pysical_col][0])){
            pysical_col = pysical_col + 2;
            logical_col = logical_col + 2;
        }
        else if(mode_flag == 1 && isUni3(buffer[pysical_col][0])){
            pysical_col = pysical_col + 3;
            logical_col = logical_col + 2;
        }
        else if(mode_flag == 1 && isUni4(buffer[pysical_col][0])){
            pysical_col = pysical_col + 4;
            logical_col = logical_col + 2;
        }
        else if(mode_flag == 1 && isUni5(buffer[pysical_col][0])){
            pysical_col = pysical_col + 5;
            logical_col = logical_col + 2;
        }
        else if(mode_flag == 1 && isUni6(buffer[pysical_col][0])){
            pysical_col = pysical_col + 6;
            logical_col = logical_col + 2;
        }
       else{
            pysical_col++;
            logical_col++;
        }
    }
    return(logical_col);
}

int read_line(int flag){
    int c,i,j,k,line;
    static int pos=0,limit=0;

    if(flag == -1){
       pos--;
       return(-1);
    }
    

    if(buffer[pos][0] == 0){
        for(i=9;i>0;i--)
            for(j=0;j<BUFSIZE;j++)
                buffer[j][i] = buffer[j][i-1];

        limit++;
        if(limit >= 10)
            limit = 9;

       for(j=0;j<BUFSIZE;j++)
            buffer[j][0] = 0;

        line = 0;
        ed_lparen_col = -1;
        ed_rparen_col = -1;
        ed_lbracket_col = -1;
        ed_rbracket_col = -1;
        j = 0;
        c = getch();
        loop:
        switch(c){
            case EOL: for(j=0;j<BUFSIZE;j++)
                          if(buffer[j][0] == 0)
                              break;
                      buffer[j][0] = c;
                      restore_paren_buffer(j);
                      printf("%c",c);
                      pos = 0;
                      goto exit;
            case DEL:  if(j <= 0)
                          break;
                      j--;
                      for(k=j;k<BUFSIZE-1;k++)
                          buffer[k][0] = buffer[k+1][0];
                      display_buffer();
                      ESCMVLEFT(count_col_buffer(j)+left_margin);
                      if(ed_rparen_col > i)
                          ed_rparen_col--;
                      if(ed_lparen_col > i)
                          ed_lparen_col--;
                      if(ed_lbracket_col > j)
                          ed_lbracket_col--;
                      if(ed_rbracket_col > j)
                          ed_rbracket_col--;
                      break;
            case 25:  //ctrl+Y
                      up_history:
                      if(limit <= 1)
                         break;
                      if(line >= limit-1)
                         line = limit-2;
                      for(j=0;j<BUFSIZE;j++)
                          buffer[j][0] = buffer[j][line+1];

                      for(j=0;j<BUFSIZE;j++)
                          if(buffer[j][0] == EOL)
                              break;
                      line++;
                      pos = 0;
                      ed_rparen_col = -1;
                      ed_lparen_col = -1;
                      display_buffer();
                      break;
            case 22:  //ctrl+V
                      down_history:
                      if(line <= 1)
                         line = 1;
                      for(j=0;j<BUFSIZE;j++)
                          buffer[j][0] = buffer[j][line-1];
                      for(j=0;j<BUFSIZE;j++)
                          if(buffer[j][0] == EOL)
                              break;
                      line--;
                      pos = 0;
                      ed_rparen_col = -1;
                      ed_lparen_col = -1;
                      display_buffer();
                      break;
            case ESC: c = getch();
                      switch(c){
                          case TAB: find_candidate_buffer(j); //completion
                                    if(ed_candidate_pt == 0)
                                        break;
                                    else if(ed_candidate_pt == 1){
                                        j = replace_fragment_buffer(ed_candidate[0],j);
                                        display_buffer();
                                        ESCMVLEFT(j+left_margin);
                                    }
                                    else{
                                        k = 0;
                                        ESCSCR;
                                        ESCMVLEFT(1);
                                        next:
                                        ESCREV;
                                        for(i=0; i<5; i++){
                                            if(i+k >= ed_candidate_pt)
                                                 break;
                                             printf("%d:%s ", i+1, ed_candidate[i+k]);
                                        }
                                        if(ed_candidate_pt > k+5)
                                            printf("6:more");
                                        ESCRST;
                                        retry:
                                        c = getch();
                                        if(c == ESC)
                                             goto escape;
                                        i = c - '1';
                                        if(ed_candidate_pt > k+5 && i == 5){ //more
                                            k = k+5;
                                            ESCMVLEFT(1);
                                            ESCCLSL;
                                            goto next;
                                        }
                                        if(i+k >= ed_candidate_pt || i < 0)
                                            goto retry;
                                        if(c == EOL)
                                            goto retry;
                                        j = replace_fragment_buffer(ed_candidate[i+k],j);
                                        escape:
                                        ESCMVLEFT(1);
                                        ESCCLSL;
                                        ESCMVU;
                                        ESCMVLEFT(left_margin);
                                        display_buffer();
                                        ESCMVLEFT(j+left_margin);
                                    }
                                    c = getch();
                                    goto loop;
                      }
                      c = getch();
                      switch(c){
                          case UP:   goto up_history;
                          case DOWN: goto down_history;
                          case LEFT:
                                if(j <= 0)
                                     break;
                                 j--;
                                 restore_paren_buffer(j);
                                 restore_bracket_buffer(j);
                                 emphasis_lparen_buffer(j);
                                 emphasis_rparen_buffer(j);
                                 emphasis_lbracket_buffer(j);
                                 emphasis_rbracket_buffer(j);
                                 ESCMVLEFT(count_col_buffer(j)+left_margin);
                                 break;

                          case RIGHT:
                                 if(buffer[j][0] == 0)
                                    break;
                                 j++;
                                 restore_paren_buffer(j);
                                 restore_bracket_buffer(j);
                                 emphasis_lparen_buffer(j);
                                 emphasis_rparen_buffer(j);
                                 emphasis_lbracket_buffer(j);
                                 emphasis_rbracket_buffer(j);
                                 ESCMVLEFT(count_col_buffer(j)+left_margin);
                                 break;

                      }
                      break;

            default:  
                    //limit terminal width
                    if(buffer[ed_width-6][0] != 0){
                        c = getch();
                        goto loop;
                    }

                    if(mode_flag == 0 && iskanji(c)){
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-2][0];
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(ed_rparen_col >= j-2)
                            ed_rparen_col = ed_rparen_col + 2;
                        if(ed_lparen_col >= j-2)
                            ed_lparen_col = ed_rparen_col + 2;
                        if(ed_rbracket_col >= j-2)
                            ed_rbracket_col = ed_rbracket_col + 2;
                        if(ed_lbracket_col >= j-2)
                            ed_lbracket_col = ed_rbracket_col + 2;
                    }
                    else if(mode_flag == 1 && isUni2(c)){
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-2][0];
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(ed_rparen_col >= j-2)
                            ed_rparen_col = ed_rparen_col + 2;
                        if(ed_lparen_col >= j-2)
                            ed_lparen_col = ed_rparen_col + 2;
                        if(ed_rbracket_col >= j-2)
                            ed_rbracket_col = ed_rbracket_col + 2;
                        if(ed_lbracket_col >= j-2)
                            ed_lbracket_col = ed_rbracket_col + 2;
                    }
                    else if(mode_flag == 1 && isUni3(c)){
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-3][0];
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(ed_rparen_col >= j-3)
                            ed_rparen_col = ed_rparen_col + 3;
                        if(ed_lparen_col >= j-3)
                            ed_lparen_col = ed_rparen_col + 3;
                        if(ed_rbracket_col >= j-3)
                            ed_rbracket_col = ed_rbracket_col + 3;
                        if(ed_lbracket_col >= j-3)
                            ed_lbracket_col = ed_rbracket_col + 3;
                    }
                    else if(mode_flag == 1 && isUni4(c)){
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-4][0];
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(ed_rparen_col >= j-4)
                            ed_rparen_col = ed_rparen_col + 4;
                        if(ed_lparen_col >= j-4)
                            ed_lparen_col = ed_rparen_col + 4;
                        if(ed_rbracket_col >= j-4)
                            ed_rbracket_col = ed_rbracket_col + 4;
                        if(ed_lbracket_col >= j-4)
                            ed_lbracket_col = ed_rbracket_col + 4;
                    }
                    else if(mode_flag == 1 && isUni5(c)){
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-5][0];
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(ed_rparen_col >= j-5)
                            ed_rparen_col = ed_rparen_col + 5;
                        if(ed_lparen_col >= j-5)
                            ed_lparen_col = ed_rparen_col + 5;
                        if(ed_rbracket_col >= j-5)
                            ed_rbracket_col = ed_rbracket_col + 5;
                        if(ed_lbracket_col >= j-5)
                            ed_lbracket_col = ed_rbracket_col + 5;
                    }
                    else if(mode_flag == 1 && isUni6(c)){
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-6][0];
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        c = getch();
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(ed_rparen_col >= j-6)
                            ed_rparen_col = ed_rparen_col + 6;
                        if(ed_lparen_col >= j-6)
                            ed_lparen_col = ed_rparen_col + 6;
                        if(ed_rbracket_col >= j-6)
                            ed_rbracket_col = ed_rbracket_col + 6;
                        if(ed_lbracket_col >= j-6)
                            ed_lbracket_col = ed_rbracket_col + 6;
                    }
                    else{
                        for(k=BUFSIZE-1;k>j;k--)
                            buffer[k][0] = buffer[k-1][0];
                        buffer[j++][0] = c;
                        display_buffer();
                        reset_paren_bracket_buffer();
                        if(c == '(' || c == ')' || c == '[' || c == ']'){
                            emphasis_lparen_buffer(count_col_buffer(j-1));
                            emphasis_rparen_buffer(count_col_buffer(j-1));
                            emphasis_lbracket_buffer(count_col_buffer(j-1));
                            emphasis_rbracket_buffer(count_col_buffer(j-1));
                        }
                        else{
                            if(ed_rparen_col >= j-1)
                                ed_rparen_col++;
                            if(ed_lparen_col >= j-1)
                                ed_lparen_col++;
                            if(ed_rbracket_col >= j-1)
                                ed_rbracket_col++;
                            if(ed_lbracket_col >= j-1)
                                ed_lbracket_col++;
                        }
                    }
                    ESCMVLEFT(count_col_buffer(j)+left_margin);

        }
        c = getch();
        goto loop;
        pos=0;
    }
   exit:
   return(buffer[pos++][0]);
}
