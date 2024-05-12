#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <gtk/gtk.h>
#include "system.h"
#include "common.h"

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("Hello, World!\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    button = gtk_button_new_with_label("Hello, World!");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    gtk_container_add(GTK_WINDOW(window), button);

    gtk_widget_show_all(window);
}

void run_gtk_application(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
}

void run_command_line_interface() {
    int pid, fd;
    SYMBOL term;

    printf("[MiniOS SSU] Hello, World!\n");
    print_prompt();

    char *path;

    while(1) {
        printf("[SSU OS 8팀] (종료를 원하시면 exit를 입력해주세요.) :");
        term = parse(&pid, FALSE, NULL);

        if (term != S_AMP && pid != 0) {
            waitfor(pid);
        }

        if (term == S_NL) {
            print_prompt();
        }

        for (fd = 3; fd < MAXFD; fd++) {
            close(fd);
        }
    }
}

int main(int argc, char **argv) {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        run_gtk_application(argc, argv);
    } else if (pid > 0) { // Parent process
        run_command_line_interface();
        wait(NULL); // Wait for the GTK application to finish
    } else {
        fprintf(stderr, "Failed to fork.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
