cdeclare($#include <GL/glut.h>$).

clibrary($-lglut -lGLU -lGL -L/usr/local/include/$).

glut_init :- 
    cinline($int argc = 0;
             char *argv;
             glutInit(&argc, argv);
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_init_display_mode_single :-
    cinline($glutInitDisplayMode(GLUT_SINGLE);
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_init_display_mode_rgba :-
    cinline($glutInitDisplayMode(GLUT_RGBA);
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_init_display_mode(glut_single) :-
    glut_init_display_mode_single.
glut_init_display_mode(glut_rgba) :-
    glut_init_display_mode_rgba.

glut_init_window_size(Hight,Width) :-
    cinline($glutInitWindowSize(Jget_int(Jderef(varHight,th)),Jget_int(Jderef(varWidth,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_init_window_position(Hight,Width) :-
    cinline($glutInitWindowPosition(Jget_int(Jderef(varHight,th)),Jget_int(Jderef(varWidth,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).
    
glut_create_window(X) :-
    cinline($glutCreateWindow(Jgetname(Jderef(varX,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_clear_color(X1,Y1,X2,Y2) :-
    cinline($glClearColor(Jget_flt(Jderef(varX1,th)),Jget_flt(Jderef(varY1,th)),
                          Jget_flt(Jderef(varX2,th)),Jget_flt(Jderef(varY2,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_display_func(X) :-
    cinline($displayfunc = Jmakepred(Jgetname(Jderef(varX,th)));
             glutDisplayFunc(display_callback);
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_mouse_func(X) :-
    cinline($mousefunc = Jmakepred(Jgetname(Jderef(varX,th)));
            glutMouseFunc(mouse_callback);
            return(Jexec_all(rest,Jget_sp(th),th));$). 


glut_main_loop :-
    cinline($glutMainLoop();
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_clear(gl_color_buffer_bit) :-
    gl_clear1.
    
gl_clear1 :-
    cinline($glClear(GL_COLOR_BUFFER_BIT);
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_color3d(R,G,B) :-
    cinline($glColor3d(Jget_flt(Jderef(varR,th)),
                       Jget_flt(Jderef(varG,th)),
                       Jget_flt(Jderef(varB,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).


gl_begin1(X) :-
    cinline($glBegin(Jgetname(Jderef(varX,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_begin(gl_line_loop) :-
    gl_begin1('GL_LINE_LOOP').
gl_begin(gl_points) :-
    gl_begin1('GL_POINTS').
gl_begin(gl_lines) :-
    gl_begin1('GL_LINES').
gl_begin(gl_line_strip) :-
    gl_begin1('GL_LINE_STRIP').
gl_begin(gl_tryangles) :-
    gl_begin1('GL_TRIANGLES').
gl_begin(gl_quads) :-
    gl_begin1('GL_QUADS').
gl_begin(gl_tryangle_strip) :-
    gl_begin1('GL_TRIANGLE_STRIP').
gl_begin(gl_quad_strip) :-
    gl_begin1('GL_QUAD_STRIP').
gl_begin(gl_tryangle_fan) :-
    gl_begin1('GL_TRIANGLE_FAN').
gl_begin(gl_polygon) :-
    gl_begin1('GL_POLYGON').
gl_begin(X) :-
    gl_error(gl_begin,X).

gl_error(P,O) :-
    format(user_output,$error ~A ~O$,[P,O]),
    fail.

gl_vertex2d(X,Y) :-
    cinline($glVertex2d(Jget_flt(Jderef(varX,th)),Jget_flt(Jderef(varY,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_vertex3d(X,Y,Z) :-
    cinline($glVertex3d(Jget_flt(Jderef(varX,th)),
                        Jget_flt(Jderef(varY,th)),
                        Jget_flt(Jderef(varZ,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).



gl_vertex4d(X1,X2,X3,X4) :-
    cinline($glVertex4d(Jget_flt(Jderef(varX1,th)),
                        Jget_flt(Jderef(varX2,th)),
                        Jget_flt(Jderef(varX3,th)),
                        Jget_flt(Jderef(varX4,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_solid_cube(X) :-
    cinline($glutSolidCube(Jget_flt(Jderef(varX,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$). 
                
glut_solid_sphere(X,Y,Z) :-
    cinline($glutSolidSphere(Jget_flt(Jderef(varX,th)),
                             Jget_flt(Jderef(varY,th)),
                             Jget_flt(Jderef(varZ,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_solid_torus(X1,X2,X3,X4) :-
    cinline($glutSolidTorus(Jget_flt(Jderef(varX1,th)),
                            Jget_flt(Jderef(varX2,th)),
                            Jget_flt(Jderef(varX3,th)),
                            Jget_flt(Jderef(varX4,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_solid_icosahedron :-
    cinline($glutSolidIcosahedron();
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_solid_octahedron :-
    cinline($glutSolidOctahedron();
             return(Jexec_all(rest,Jget_sp(th),th));$).


glut_solid_tetrahedron :-
    cinline($glutSolidTetrahedron();
            return(Jexec_all(rest,Jget_sp(th),th));$).


glut_solid_dodecahedron :-
    cinline($glutSolidDodecahedron();
             return(Jexec_all(rest,Jget_sp(th),th));$).


glut_solid_cone(X1,X2,X3,X4) :-    
    cinline($glutSolidCone(Jget_flt(Jderef(varX1,th)),
                           Jget_flt(Jderef(varX2,th)),
                           Jget_flt(Jderef(varX3,th)),
                           Jget_flt(Jderef(varX4,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

glut_solid_teapot(X) :-
    cinline($glutSolidTeapot(Jget_flt(Jderef(varX,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$). 


gl_end :-
    cinline($glEnd();
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_flush :-
    cinline($glFlush();
             return(Jexec_all(rest,Jget_sp(th),th));$).

gl_finish :-
    cinline($glFinish();
             return(Jexec_all(rest,Jget_sp(th),th));$).
