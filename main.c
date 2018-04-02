#include <gtk/gtk.h>
#include "download.h"

int main(int argc, char **argv) {
    download_t *download;
    //GtkApplication *app;
    //int status;

    /*
    app = gtk_application_new ("com.github.b-raffai.guitar-practise",
            G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    */
    gtk_init(&argc, &argv);
    download = download_new();
    gtk_main();

    return 0;
}
