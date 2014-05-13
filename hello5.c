#include <gtk/gtk.h>

static gboolean destroy_event( GtkWidget *widget,
                               GdkEvent  *event,
                               gpointer   data ) {
	gtk_main_quit();
	return FALSE;
}

void gtk_table_attach_def( GtkTable  *table,
                           GtkWidget *widget,
                           guint l, guint r,
                           guint t, guint d ) {
	gtk_table_attach(table, widget, l, r, t, d,
		GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 5, 5);
}

static void press_button( GtkWidget *widget,
                          gpointer   data ) {
	g_print("button %d was pressed\n", (gint) data);
}

int main( int   argc,
          char *argv[] ) {
	GtkWidget *window, *table, *button, *label;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect_swapped(window, "delete-event",
		G_CALLBACK(destroy_event), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	table = gtk_table_new(2, 3, FALSE);
	label = gtk_label_new("label 1");
	gtk_table_attach_def(GTK_TABLE(table), label, 0, 1, 0, 1);
	gtk_widget_show(label);
	button = gtk_button_new_with_label("button 1");
	g_signal_connect(button, "clicked",
		G_CALLBACK(press_button), (gpointer) 1);
	gtk_table_attach_def(GTK_TABLE(table), button, 1, 2, 0, 1);
	gtk_widget_show(button);
	label = gtk_label_new("label 2");
	gtk_table_attach_def(GTK_TABLE(table), label, 0, 1, 1, 2);
	gtk_widget_show(label);
	button = gtk_button_new_with_label("button 2");
	g_signal_connect(button, "clicked",
		G_CALLBACK(press_button), (gpointer) 2);
	gtk_table_attach_def(GTK_TABLE(table), button, 1, 2, 1, 2);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("quit");
	gtk_table_attach_def(GTK_TABLE(table), button, 0, 2, 2, 3);
	g_signal_connect_swapped(button, "clicked",
		G_CALLBACK(destroy_event), NULL);
	gtk_widget_show(button);
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show(table);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
