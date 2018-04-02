typedef struct download{
    GtkWidget *window;

    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *textbox;
    GtkWidget *download_status_view;
} download_t;

void download_song(const char *name, GtkTextBuffer *buff);
download_t *download_new(void);
