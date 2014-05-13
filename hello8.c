#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

typedef struct opt {
	gchar  *off;
	gchar  *on;
	guint   def;
	gchar **optptr;
} opt;

static void select_frames( GtkWidget *widget,
                           gpointer **data ) {
	//g_print("%p %p\n", data[0], data[1]);
	//GtkWidget *chooser = *(data[0]);
	//GSList** filenames = data[1], i;
	GSList* *i=NULL;
	g_print("%p\n", data[1]);
	*data[1] = gtk_file_chooser_get_uris(GTK_FILE_CHOOSER(*data[0]));
	//g_print("step\n");
	g_print("%p\n", (g_slist_last(*data[1])));
	/*
	for (i=*(data[1]); i; i=i->next) {
		g_print("%p\n", i->data);
	}
	*/
}

static void update_option( GtkWidget *widget,
                           gchar    **o ) {
	*o = (gchar *)gtk_entry_get_text(GTK_ENTRY(widget));
}

static void run( GtkWidget *widget,
                 gchar   *(*option)[] ) {
	gchar *command;
	int i, strsize=0;
	for (i=0; i<10; i++)
		strsize += strlen((*option)[i]);
	strsize += 10; // 9 spaces + \0
	g_print("%d\n", strsize);
	// MALLOC !!
	command = malloc(strsize*sizeof(gchar));
	strcpy(command, (*option)[0]);
	for (i=1; i<10; i++) {
		strcat(command, " ");
		strcat(command, (*option)[i]);
	}
	g_print("$ %s\n", command);
	
	// FORK NEW PROCESS
	system(command);
	free(command);
}

static void progress( GtkWidget      *widget,
                      GtkProgressBar *prog ) {
	gtk_progress_bar_set_fraction(prog,
		gtk_progress_bar_get_fraction(prog)/2);
}

int main( int   argc,
          char *argv[] ) {
	GtkWidget *window, *box, *button, *sep, *chooser;
	GtkWidget *lbl, *prog, *entry, *table;
	
	GSList* filenames;
	g_print("%p\n", &filenames);
	gchar *option[10];
	option[0] = "/usr/bin/gif";
	int i;
	for (i=1; i<11; i++)
		option[i] = "";
	
	gchar *optionlbl[] = {
		"prefix", "first", "last", "step", "suffix",
		"maxsize", "colors", "title (\"\" for no title)", "output"
	};
	
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "gif");
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	box = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 5);
	
	// TITLE
	lbl = gtk_label_new("make animated gif from set of jpg/png frames");
	gtk_label_set_justify(GTK_LABEL(lbl), GTK_JUSTIFY_CENTER);
	gtk_widget_show(lbl);
	gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
	
	// SEPARATOR
	sep = gtk_hseparator_new();
	gtk_widget_show(sep);
	gtk_box_pack_start(GTK_BOX(box), sep, FALSE, TRUE, 5);
	
	// FILE CHOOSER
	chooser = gtk_file_chooser_dialog_new("select frames",
		GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_select_multiple(
		GTK_FILE_CHOOSER(chooser), TRUE);
	// BUTTON
	button = gtk_button_new_with_label("select frames");
	gpointer data[2] = {&chooser, &filenames};
	g_signal_connect(button, "clicked",
		G_CALLBACK(select_frames), data);
	//free(data);
	gtk_widget_show(button);
	gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
	
	// TABLE
	table = gtk_table_new(6, 2, FALSE);
	// ROWS
	for (i=1; i<10; i++) {
		entry = gtk_entry_new();
		g_signal_connect(entry, "changed",
			G_CALLBACK(update_option), &option[i]);
		gtk_widget_show(entry);
		gtk_table_attach_defaults(GTK_TABLE(table), entry,
			0, 1, i-1, i);
		lbl = gtk_label_new(optionlbl[i-1]);
		gtk_widget_show(lbl);
		gtk_table_attach_defaults(GTK_TABLE(table), lbl,
			1, 2, i-1, i);
	}
	gtk_widget_show(table);
	gtk_box_pack_start(GTK_BOX(box), table, TRUE, TRUE, 0);

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
