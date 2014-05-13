#include <gtk/gtk.h>

static void toggle( GtkWidget *widget,
                    gchar    **option ) {
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
		*option = "on";
	else
		*option = "";
}

static void run( GtkWidget *widget,
          gchar    **option ) {
	//g_print("run with option %s\n", *option);
	gtk_main_quit();
	char *prog = "./test";
	char *argv[]={prog, *option, NULL};
	execv(argv[0], argv);
}

int main( int   argc,
          char *argv[] ) {
	GtkWidget *window, *box, *check, *button, *sep;
	gchar *option = "";
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	box = gtk_vbox_new(FALSE, 0);
	
	// OPTION CHECKBOX
	check = gtk_check_button_new_with_label("option");
	g_signal_connect(check, "toggled",
		G_CALLBACK(toggle), &option);
	gtk_widget_show(check);
	gtk_box_pack_start(GTK_BOX(box), check, TRUE, TRUE, 0);
	
	// SEPARATOR
	sep = gtk_hseparator_new();
	gtk_widget_show(sep);
	gtk_box_pack_start(GTK_BOX(box), sep, FALSE, TRUE, 5);
	
	// RUN BUTTON
	button = gtk_button_new_with_label("run");
	g_signal_connect(button, "clicked",
		G_CALLBACK(run), &option);
	gtk_widget_show(button);
	gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
	
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
