typedef struct download{
    GtkWidget *window;

    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *textbox;
    GtkWidget *download_status_term;
} download_t;

void download_song(const char *name, GtkWidget *term);
download_t *download_new(void);
