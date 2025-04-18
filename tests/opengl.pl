main :-
    glut_init,
    glut_init_display_mode(glut_single),
    glut_init_window_size(400,300),
    glut_init_window_position(200,300),
    glut_create_window('GLUT test'),
    glut_init_display_mode(glut_rgba),
    gl_clear_color(1.0,1.0,1.0,1.0),
    glut_display_func(show),
    glut_main_loop.


show :-
    write(user_output,ok),
    gl_clear(gl_color_buffer_bit),
    gl_color3d(1.0,0.0,0.0),
    gl_begin(gl_line_loop),
    gl_vertex2d(-0.5,-0.5),
    gl_vertex2d(-0.5,0.5),
    gl_vertex2d(0.5,0.5),
    gl_vertex2d(0.5,-0.5),
    gl_end,
    glut_solid_teapot(0.5),
    gl_flush.

