#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static GtkWidget *text_view;

static void print_hello(GtkWidget *widget, gpointer data) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    GtkTextIter end;
    FILE *fp;
    char path[1035];

    // Execute a command and open the output for reading.
    fp = popen("ls", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    // Clear the buffer
    gtk_text_buffer_set_text(buffer, "", -1);

    // Read the output a line at a time and append it to the text buffer
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(buffer, &end, path, -1);
    }

    // Close the file pointer
    pclose(fp);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *scrolled_window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "MiniOS File Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    button = gtk_button_new_with_label("List Directory");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);

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
