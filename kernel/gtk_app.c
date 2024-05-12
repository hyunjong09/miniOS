#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include <dirent.h>

static GtkWidget *image;

static void on_file_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gchar *file_path;
        gtk_tree_model_get(model, &iter, 0, &file_path, -1);

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(file_path, 200, 200, TRUE, NULL);
        if (pixbuf) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
            g_object_unref(pixbuf);
        }

        g_free(file_path);
    }
}

static void create_and_fill_model(GtkWidget *tree_view) {
    GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
    g_object_unref(store);

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, ent->d_name, -1);
        }
        closedir(dir);
    }
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    GtkWidget *tree_view = gtk_tree_view_new();
    GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);

    gtk_window_set_title(GTK_WINDOW(window), "MiniOS File Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // 파일 리스트 설정
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Files", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    create_and_fill_model(tree_view);

    // 이미지 위젯 설정
    image = gtk_image_new();
    gtk_widget_set_size_request(image, 200, 200);

    gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(tree_view), TRUE);
    g_signal_connect(tree_view, "row-activated", G_CALLBACK(on_file_activated), NULL);

    gtk_container_add(GTK_CONTAINER(scroll_window), tree_view);
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox), scroll_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), hbox);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
