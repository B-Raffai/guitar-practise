#include <gtk/gtk.h>

static void
download_cb (GtkWidget *widget,
        gpointer   data) {

    const char format[] = "youtube-dl -x 'ytsearch:%s'";

    char cmd[sizeof(format) + 100];
    snprintf(cmd, sizeof(cmd), format, gtk_entry_get_text(data));
    system(cmd);
    g_message("downloading: %s\n", gtk_entry_get_text(data));
}

static void
activate (GtkApplication *app,
        gpointer        user_data) {
    GtkWidget *window;

    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *textbox;
    GtkEntryBuffer buffer;

    /* create a new window, and set its title */
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    grid = gtk_grid_new ();

    /* Pack the container in the window */
    gtk_container_add (GTK_CONTAINER (window), grid);

    textbox = gtk_entry_new();
    gtk_grid_attach (GTK_GRID (grid), textbox, 0, 0, 1, 1);

    button = gtk_button_new_with_label ("download");
    g_signal_connect (button, "clicked", G_CALLBACK (download_cb), textbox);
    gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

    gtk_widget_show_all (window);
}

    int
main (int    argc,
        char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("com.github.b-raffai.guitar-practise",
            G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
