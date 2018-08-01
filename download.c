#include <gtk/gtk.h>
#include <vte/vte.h>
#include "download.h"

static void download_cb (download_t *dl) {
    g_message("downloading: %s\n", gtk_entry_get_text(
                GTK_ENTRY(dl->textbox)));
    download_song(gtk_entry_get_text(GTK_ENTRY(dl->textbox)), 
                      dl->download_status_term);
}

download_t* download_new() {
    download_t *download;
    download = g_malloc0(sizeof(download_t));

    /* create a new window, and set its title */
    download->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (download->window), "Window");
    gtk_container_set_border_width (GTK_CONTAINER (download->window), 10);

    download->grid = gtk_grid_new ();

    /* Pack the container in the window */
    gtk_container_add (GTK_CONTAINER (download->window), download->grid);

    download->textbox = gtk_entry_new();
    gtk_grid_attach (GTK_GRID (download->grid), download->textbox, 0, 0, 1, 1);

    download->button = gtk_button_new_with_label("download");
    gtk_grid_attach( GTK_GRID(download->grid), download->button, 1, 0, 1, 1);

    download->download_status_term = vte_terminal_new();
    gtk_grid_attach( GTK_GRID(download->grid), download->download_status_term,
             0, 1, 2, 1);

    gtk_widget_show_all(download->window);

    g_signal_connect_swapped(download->button, "clicked", 
            G_CALLBACK (download_cb), (gpointer)download);
}

gboolean add_text_to_term(GIOChannel *src, GIOCondition cond, gpointer term) {
    char c;
    if(cond == G_IO_IN) {
        g_io_channel_read_chars(src, &c, 1, NULL, NULL);

        //add carriage return before line feed
        if(c == '\n') {
            char cr = '\r';
            vte_terminal_feed(term, &cr, 1);
        }

        vte_terminal_feed(term, &c, 1);
        return TRUE;
    } else {
        g_critical("Wrong condition in add_text_to_buffer");
        return FALSE;
    }
}

void download_song(const char *name, GtkWidget *term) {
    char lastarg[100];
    gchar *argv[] = {"/usr/bin/youtube-dl", "-x", NULL, NULL};

    sprintf(lastarg, "ytsearch:%s", name);
    argv[2] = lastarg;

    GPid pid;
    gint chl_std_out;
    GIOChannel *io;
    
    gboolean ret;
    GError *err = NULL;

    //run the download and save stdout to a pipe
    if(TRUE != g_spawn_async_with_pipes (NULL,
                                          argv,
                                          NULL,
                                          G_SPAWN_DEFAULT,
                                          NULL,
                                          NULL,
                                          &pid,
                                          NULL,
                                          &chl_std_out,
                                          NULL,
                                          &err)) {
        g_critical("error in spawning: %s", err->message);
    }

    io = g_io_channel_unix_new(chl_std_out);

    //when there is new data in the pipe, add it to the terminal
    g_io_add_watch(io, G_IO_IN, add_text_to_term, (gpointer)term);
}
