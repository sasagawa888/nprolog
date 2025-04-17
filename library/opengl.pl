cdeclare($#include <GL/glut.h>$).

clibrary($-lglut -lGLU -lGL -L/usr/local/include/$).

glut_init :- 
    cinline($int argc = 0;
             char *argv;
             glutInit(&argc, argv);
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_init_display_mode1 :-
    cinline($glutInitDisplayMode(GLUT_SINGLE);
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_init_display_mode(glut_single) :-
    glut_init_display_mode1.

glut_init_window_size(Hight,Width) :-
    cinline($glutInitWindowSize(Jget_int(Jderef(varHight,th)),Jget_int(Jderef(varWidth,th)));$).

glut_init_window_position(Hight,Width) :-
    cinline($glutInitWindowPosition(Jget_int(Jderef(varHight,th)),Jget_int(Jderef(varWidth,th)));$).
    
glut_create_window(X) :-
    cinline($glutCreateWindow(Jgetname(Jderef(varX,th)));$).

gl_clear_colot(X1,Y1,X2,Y2) :-
    cinline($glClearColor(Jget_flt(Jderef(varX1,th)),Jget_flt(Jderef(varY1,th)),
                          Jget_flt(Jderef(varX2,th)),Jget_flt(Jderef(varY2,th)));$).

/*
glut_display_func(X) :-
    cinline($displayfunc = Jcons(Jderef(varX,th),NIL);
             glutDisplayFunc(display_callback);$).

glut_mouse_func(X) :-
    cinlie($mousefunc = Fcons(X,NIL);
            glutMouseFunc(mouse_callback);$). 
*/


glut_main_loop :-
    cinline($glutMainLoop();$).

gl_clear(gl_color_buffer_bit) :-
    gl_clear1.
    
gl_clear1 :-
    cinline($glClear(GL_COLOR_BUFFER_BIT);$).

gl_color3d(R,G,B) :-
    cinline($glColor3d(Jget_flt(Jderef(varR,th)),
                       Jget_flt(Jderef(varG,th)),
                       Jget_flt(Jderef(varB,th)));$).


/*


(defun gl:begin (x)
    (cond ((eq x 'gl-line-loop) (c-lang "glBegin(GL_LINE_LOOP);"))
          ((eq x 'gl-points) (c-lang "glBegin(GL_POINTS);"))
          ((eq x 'gl-lines) (c-lang "glBegin(GL_LINES);"))
          ((eq x 'gl-line-strip) (c-lang "glBegin(GL_LINE_STRIP);"))
          ((eq x 'gl-triangles) (c-lang "glBegin(GL_TRIANGLES);"))
          ((eq x 'gl-quads) (c-lang "glBegin(GL_QUADS);"))
          ((eq x 'gl-triangle-strip) (c-lang "glBegin(GL_TRIANGLE_STRIP);"))
          ((eq x 'gl-quad-strip) (c-lang "glBegin(GL_QUAD_STRIP);"))
          ((eq x 'gl-triangle-fan) (c-lang "glBegin(GL_TRIANGLE_FAN);"))
          ((eq x 'gl-polygon) (c-lang "glBegin(GL_POLYGON);"))
          (t (error "gl:begin" x))))

  

(defun gl:vertex2d (x y)
    (c-lang "glVertex2d(Fgetflt(X),Fgetflt(Y));"))

(defun gl:vertex3d (x y z)
    (c-lang "glVertex3d(Fgetflt(X),Fgetflt(Y),Fgetflt(Z));"))

(defun gl:vertex4d (x1 x2 x3 x4)
    (c-lang "glVertex4d(Fgetflt(X1),Fgetflt(X2),Fgetflt(X3),Fgetflt(X4));"))

(defun glut:solid-cube (x)
    (c-lang "glutSolidCube(Fgetflt(X));")) 

(defun glut:solid-sphere (x y z)
    (c-lang "glutSolidSphere(Fgetflt(X),Fgetflt(Y),Fgetflt(Z));"))

(defun glut:solid-torus (x1 x2 x3 x4)
    (c-lang "glutSolidTorus(Fgetflt(X1),Fgetflt(X2),Fgetflt(X3),Fgetflt(X4));")) 

(defun glut:solid-icosahedron ()
    (c-lang "glutSolidIcosahedron();"))

(defun glut:solid-octahedron ()
    (c-lang "glutSolidOctahedron();"))

(defun glut:solid-tetrahedron ()
    (c-lang "glutSolidTetrahedron();"))

(defun glut:solid-dodecahedron ()
    (c-lang "glutSolidDodecahedron();"))

(defun glut:solid-cone (x1 x2 x3 x4)    
    (c-lang "glutSolidCone(Fgetflt(X1),Fgetflt(X2),Fgetflt(X3),Fgetflt(X4));"))

(defun glut:solid-teapot (x)
    (c-lang "glutSolidTeapot(Fgetflt(X));")) 

(defun gl:end ()
    (c-lang "glEnd();"))

(defun gl:flush ()
    (c-lang "glFlush();"))

(defun gl:finish ()
    (c-lang "glFinish();"))
*/