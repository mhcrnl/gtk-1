#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

typedef struct opt {
	gchar *off;
	gchar *on;
	guint def;
	gchar **optptr;
} opt;

static void toggle( GtkWidget *widget,
                    gpointer **option ) {
	opt *o = (opt *)option;
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
		*o->optptr = o->on;
	else
		*o->optptr = o->off;
}

static void init_check( GtkWidget *widget,
                        gpointer **option ) {
	opt *o = (opt *)option;
	if (o->def == 1)
		*o->optptr = o->off;
	else
		gtk_toggle_button_set_active(
			GTK_TOGGLE_BUTTON(widget), TRUE);
		// calls toggle which points optptr at on;
		// pointing it here would make it end up
		// pointing at off after the toggle call.
}

static void run( GtkWidget *widget,
                 gchar   *(*option)[7] ) {
	gchar command[200];
	strcpy(command, (*option)[0]);
	int i;
	for (i=1; i<6; i++) {
		strcat(command, " ");
		strcat(command, (*option)[i]);
	}
	g_print("%s\n", command);
	
	// FORK NEW PROCESS
	system(command);
}

static void out( GtkWidget *widget,
                 GtkLabel  *label ) {
	gtk_label_set_text(label, "out!");
}

static void progress( GtkWidget      *widget,
                      GtkProgressBar *prog ) {
	gtk_progress_bar_set_fraction(prog,
		gtk_progress_bar_get_fraction(prog)/2);
}

int main( int   argc,
          char *argv[] ) {
	GtkWidget *window, *box, *hbox, *check;
	GtkWidget *button, *sep, *lbl, *frame;
	GtkWidget *prog, *entry, *table;
	gchar *option[7];
	option[0] = "/usr/bin/gif";
	option[6] = NULL;
	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "stabilizer");
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	box = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 5);
	
	// TITLE
	lbl = gtk_label_new("stabilizer for a jpg/png set of frames\nwith bruteforce testing on a rectangle\nfor a given testing spread");
	gtk_label_set_justify(GTK_LABEL(lbl), GTK_JUSTIFY_CENTER);
	gtk_widget_show(lbl);
	gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
	
	// SEPARATOR
	sep = gtk_hseparator_new();
	gtk_widget_show(sep);
	gtk_box_pack_start(GTK_BOX(box), sep, FALSE, TRUE, 5);
	
	// TABLE
	table = gtk_table_new(6, 2, FALSE);
	// ROWS
	// 1
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 0, 1);
	lbl = gtk_label_new("prefix");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 0, 1);
	// 2
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 1, 2);
	lbl = gtk_label_new("first");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 1, 2);
	// 3
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 2, 3);
	lbl = gtk_label_new("last");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 2, 3);
	// 4
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 3, 4);
	lbl = gtk_label_new("step");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 3, 4);
	// 5
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 4, 5);
	lbl = gtk_label_new("suffix");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 4, 5);
	// 6
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 5, 6);
	lbl = gtk_label_new("maxsize");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 5, 6);
	// 7
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 6, 7);
	lbl = gtk_label_new("colors");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 6, 7);
	// 8
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 7, 8);
	lbl = gtk_label_new("title");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 7, 8);
	// 9
	entry = gtk_entry_new();
	gtk_widget_show(entry);
	gtk_table_attach_defaults(GTK_TABLE(table), entry,
		0, 1, 8, 9);
	lbl = gtk_label_new("output file");
	gtk_widget_show(lbl);
	gtk_table_attach_defaults(GTK_TABLE(table), lbl,
		1, 2, 8, 9);
	
	gtk_widget_show(table);
	gtk_box_pack_start(GTK_BOX(box), table, TRUE, TRUE, 0);
	
	// OPTIONS
	// 1
	opt o1 = {"off", "on", 1, &option[1]};
	check = gtk_check_button_new_with_label("option1");
	g_signal_connect(check, "toggled",
		G_CALLBACK(toggle), (gpointer)&o1);
	init_check(check, (gpointer)&o1); //activate default value
	gtk_widget_show(check);
	gtk_box_pack_start(GTK_BOX(box), check, TRUE, TRUE, 0);
	// 2
	opt o2 = {"off", "on", 1, &option[2]};
	check = gtk_check_button_new_with_label("option2");
	g_signal_connect(check, "toggled",
		G_CALLBACK(toggle), (gpointer)&o2);
	init_check(check, (gpointer)&o2); //activate default value
	gtk_widget_show(check);
	gtk_box_pack_start(GTK_BOX(box), check, TRUE, TRUE, 0);
	// 3
	opt o3 = {"off", "on", 1, &option[3]};
	check = gtk_check_button_new_with_label("option3");
	g_signal_connect(check, "toggled",
		G_CALLBACK(toggle), (gpointer)&o3);
	init_check(check, (gpointer)&o3); //activate default value
	gtk_widget_show(check);
	gtk_box_pack_start(GTK_BOX(box), check, TRUE, TRUE, 0);
	// 4
	opt o4 = {"off", "on", 1, &option[4]};
	check = gtk_check_button_new_with_label("option4");
	g_signal_connect(check, "toggled",
		G_CALLBACK(toggle), (gpointer)&o4);
	init_check(check, (gpointer)&o4); //activate default value
	gtk_widget_show(check);
	gtk_box_pack_start(GTK_BOX(box), check, TRUE, TRUE, 0);
	// 5
	opt o5 = {"off", "on", 2, &option[5]};
	check = gtk_check_button_new_with_label("option5 (def on)");
	g_signal_connect(check, "toggled",
		G_CALLBACK(toggle), (gpointer)&o5);
	init_check(check, (gpointer)&o5);
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
	
	// SEPARATOR
	sep = gtk_hseparator_new();
	gtk_widget_show(sep);
	gtk_box_pack_start(GTK_BOX(box), sep, FALSE, TRUE, 5);
	
	// HBOX
	hbox = gtk_hbox_new(FALSE, 0);
	
	// OUT BUTTON
	button = gtk_button_new_with_label("out");
	// OUT LABEL
	lbl = gtk_label_new("");
	g_signal_connect(button, "clicked",
		G_CALLBACK(out), GTK_LABEL(lbl));
	gtk_widget_show(button);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);	
	gtk_widget_show(lbl);
	// OUT FRAME
	frame = gtk_frame_new("out");
	gtk_container_add(GTK_CONTAINER(frame), lbl);
	gtk_widget_show(frame);
	gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, 0);
	gtk_widget_show(hbox);
	gtk_box_pack_start(GTK_BOX(box), hbox, TRUE, TRUE, 0);
	
	// SEPARATOR
	sep = gtk_hseparator_new();
	gtk_widget_show(sep);
	gtk_box_pack_start(GTK_BOX(box), sep, FALSE, TRUE, 5);
	
	// PROGRESS BAR
	prog = gtk_progress_bar_new();
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog), 1);
	g_signal_connect(button, "clicked",
		G_CALLBACK(progress), GTK_PROGRESS_BAR(prog));
	gtk_widget_show(prog);
	gtk_box_pack_start(GTK_BOX(box), prog, TRUE, TRUE, 0);
	
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
