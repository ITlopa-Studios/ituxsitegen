/*
 * Copyright (C) 2025 ITlopa
 *
 * This file is part of ItuxSiteGen.
 *
 * ItuxSiteGen is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * ItuxSiteGen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
*/
#ifdef __unix
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>

#ifndef _
#define _(string) gettext(string)
#endif

static struct termios orig_termios;

// Restore original terminal settings on exit
void restore_termios() {tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);}

static void handle_sigint(int sig) {
    (void)sig;
    restore_termios();
    _exit(128 + SIGINT);
}

void press_any_key(const char *msg) {
    struct termios t;
    unsigned char ch;

    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("tcgetattr");
        return;
    }
    atexit(restore_termios);
    signal(SIGINT, handle_sigint);

    t = orig_termios;
    // Disable canonical mode and echo so a single keypress is read immediately
    t.c_lflag &= ~(ICANON | ECHO);
    // read() returns after one byte
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &t) == -1) {
        perror("tcsetattr");
        return;
    }

    if (msg) printf("%s", msg);
    fflush(stdout);

    if (read(STDIN_FILENO, &ch, 1) <= 0) {
        return;
    }

    // restore_termios will be called at exit or explicitly below
    restore_termios();
}
void __pause() {
    press_any_key(_("Press any key to continue..."));
}
#else
#include <stdlib.h>

#ifndef _
#define _(string) (string)
#endif

void __pause()
{
    system("pause");
}
#endif
