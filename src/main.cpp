#include <assert.h>
#include <gtk/gtk.h>

static void
add_tuple_icon(const char *path, const char *name)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    int width, height;
    gdk_pixbuf_get_file_info(path, &width, &height);
    gtk_icon_theme_add_builtin_icon(name, width, pixbuf);
    g_object_unref(G_OBJECT(pixbuf));
}

GtkApplication *app;
GtkWidget *window;
GtkWidget *header;
GtkWidget *box;

GtkWidget *tag_team;
gulong tag_handler = 0;

GtkWidget *multi;
gulong multi_handler = 0;

GtkWidget *paint;
gulong paint_handler = 0;

static void
toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    GtkWidget *widgets[3] = { tag_team, multi, paint };
    gulong handlers[3] = { tag_handler, multi_handler, paint_handler };
    GtkWidget *toggled = GTK_WIDGET(togglebutton);

    for (size_t i = 0; i < 3; ++i) {
        if (widgets[i] != toggled) {
            // When calling set_active, the 'toggled' signal will get triggered so
            // we must disable and reenable the signal when one of our buttons is
            // clicked
            g_signal_handler_block(widgets[i], handlers[i]);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widgets[i]), FALSE);
            g_signal_handler_unblock(widgets[i], handlers[i]);
        }
    }
}

static void
activate(GtkApplication *app, gpointer user_data)
{
    (void)user_data;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Toolbar Example");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    header = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Call with mikey@tuple.app");

    // TODO: off?
    gtk_header_bar_set_has_subtitle(GTK_HEADER_BAR(header), FALSE);

    add_tuple_icon("/home/spence/code/tuple/linuxapp/resources/icons/dual-click.svg", "tuple-multi-cursor");
    add_tuple_icon("/home/spence/code/tuple/linuxapp/resources/icons/single.svg", "tuple-tag-team");
    add_tuple_icon("/home/spence/code/tuple/linuxapp/resources/icons/paint-cursor.svg", "tuple-paint");

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_style_context_add_class(gtk_widget_get_style_context(box), "linked"); // 'linked' will make the buttons look like they're connected together

    tag_team = gtk_toggle_button_new();
    gtk_container_add(GTK_CONTAINER(tag_team), gtk_image_new_from_icon_name("tuple-tag-team", GTK_ICON_SIZE_BUTTON));
    gtk_container_add(GTK_CONTAINER(box), tag_team);
    tag_handler = g_signal_connect(tag_team, "toggled", G_CALLBACK(toggled), NULL);
    g_assert(tag_handler);

    multi = gtk_toggle_button_new();
    gtk_container_add(GTK_CONTAINER(multi), gtk_image_new_from_icon_name("tuple-multi-cursor", GTK_ICON_SIZE_BUTTON));
    gtk_container_add(GTK_CONTAINER(box), multi);
    multi_handler = g_signal_connect(multi, "toggled", G_CALLBACK(toggled), NULL);
    g_assert(multi_handler);

    paint = gtk_toggle_button_new();
    gtk_container_add(GTK_CONTAINER(paint), gtk_image_new_from_icon_name("tuple-paint", GTK_ICON_SIZE_BUTTON));
    gtk_container_add(GTK_CONTAINER(box), paint);
    paint_handler = g_signal_connect(paint, "toggled", G_CALLBACK(toggled), NULL);
    g_assert(paint_handler);

    // Set tag team to on
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(tag_team), TRUE);

    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), box);

    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    int status;

    app = gtk_application_new("app.tuple.app", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

