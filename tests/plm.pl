A = 1+2*3;


GOTO START;
HALT;

SUMSQUARE: PROCEDURE (A,B) ADDRESS;
    DECLARE (A,B) ADDRESS;
    RETURN A*A+B*B;
END SUMSQUARE;

START: B = B+SUMSQUARE(A,B);

DO CASE A<>0;
    C = C+1;
    C = C*2;
END;

DO WHILE A>0;
    C = C+1;
    C = C*2;
    IF C=1 THEN D = C;
    ELSE
    DO; 
        A = 1;
        B = 2;
    END;
END;












