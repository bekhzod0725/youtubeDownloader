#include "gui.h"

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


GuiT			*gui;
GtkBuilder 		*builder;
QualiT			**quality;
cstring 		title;

void gui_init(int * argc, char *** argv) {

	title = malloc(129*sizeof(char));
	gui = malloc(sizeof(GuiT));
	quality = malloc(35*sizeof(QualiT));
    gtk_init (argc, argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, GUIPATH, NULL);

    gui->window		= GTK_WIDGET (gtk_builder_get_object (builder, 	"wMain"));
    gui->qualBox	= GTK_COMBO_BOX(gtk_builder_get_object(builder, 	"qualBox"));
    gui->outTxt 	= GTK_ENTRY(gtk_builder_get_object(builder, 		"txtOut"));
    gui->urlTxt 	= GTK_ENTRY(gtk_builder_get_object(builder, 		"txtUrl"));
    gui->txtResults = GTK_TEXT_VIEW(gtk_builder_get_object(builder, 	"txtResults"));
    gui->txtBuffer  = gtk_text_buffer_new(NULL);
}

void gui_run() {
	gtk_text_view_set_buffer(gui->txtResults,gui->txtBuffer);

	gtk_builder_connect_signals (builder, NULL);

//  g_object_unref (G_OBJECT (builder));

	gtk_widget_show (gui->window);
	gtk_main ();
}

void _parse_output(gchar * string) {
		GError *error = NULL;
		GRegex *regex;
		GMatchInfo *matches;

		regex = g_regex_new (REGEX, 0, 0, &error);

		if (error)
		{
			g_error ("%s", error->message);
			g_error_free (error);
		}
		else
		{
			gboolean result;

			result = g_regex_match (regex, string, 0, &matches); /* XXX */
//			printf("%d\n",result);
			if (result)
			{
//				updating = FALSE;

				const gchar *link = gtk_entry_get_text (GTK_ENTRY (gui->urlTxt));

//				gchar *buffer;
//				gchar *caption;
				gchar *percent;
				gchar *size;
				gchar *size_unit;
				gchar *speed;
				gchar *speed_unit;
				gchar *minutes;
				gchar *seconds;
				gdouble downloaded;
				gdouble fraction;

				percent = g_match_info_fetch (matches, 1);
				size = g_match_info_fetch (matches, 2);
				size_unit = g_match_info_fetch (matches, 3);
				speed = g_match_info_fetch (matches, 4);
				speed_unit = g_match_info_fetch (matches, 5);
				minutes = g_match_info_fetch (matches, 6);
//				seconds = g_match_info_fetch (matches, 7);

//				caption = g_strdup_printf ("Downloading <b>%s</b>.\n%s alrededor de <b>%s</b> %s y <b>%s</b> %s a <b>%s%s</b>.",
//				                           link, minutes, minutes, minutes, seconds, seconds, speed, speed_unit);

				fraction = g_strtod (percent, NULL) / 100.0;
				downloaded = g_strtod (size, NULL) * fraction;
//				gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (ui->progress), fraction);
//				buffer = g_strdup_printf ("Descargados %.02g%s de %s%s (%s%%)", downloaded, size_unit, size, size_unit, percent);
//				gtk_progress_bar_set_text (GTK_PROGRESS_BAR (ui->progress), buffer);

//				gtk_label_set_markup (GTK_LABEL (ui->label), caption);
//				printf("Downloading <b>%s</b>.\n%s alrededor de <b>%s</b> %s y <b>%s</b> %s a <b>%s%s</b>.",
//				                           link, minutes, minutes, minutes, seconds, seconds, speed, speed_unit);
//				printf("Descargados %.02g%s de %s%s (%s%%)", downloaded, size_unit, size, size_unit, percent);
				printf("Completed %s of %s%s in %s%s ETA %s\n", percent, size, size_unit, speed, speed_unit, minutes);
//				g_free (caption);
//				g_free (buffer);
				g_free (percent);
				g_free (size);
				g_free (size_unit);
				g_free (speed);
				g_free (speed_unit);
				g_free (minutes);
//				g_free (seconds);

				while (gtk_events_pending ())
				{
					gtk_main_iteration ();
				}
			} else {
				printf("%s", string);
			}

			g_match_info_matches (matches);
		}

		g_regex_unref (regex);
}

gboolean _output_watch(GIOChannel *channel, GIOCondition cond, gpointer user_data) {
	gchar *string;
	size_t size;

	if(cond == G_IO_HUP) {
		g_io_channel_unref(channel);
		return(FALSE);
	}
	g_io_channel_read_line(channel, &string, &size, NULL, NULL);
	_parse_output(string);
//	printf("%s\n",string);
	g_free(string);
	return(TRUE);
}

void _get_with_gspawn(const cstring url, cstring outname, int index) {
		pid_t pid;
		gchar * oarg = "-o";
		gchar * farg = "-f";
		gchar * carg = "-c";
//		gchar *buffer = malloc(128*sizeof(char));
		gchar value[5];
		sprintf(value, "%d%c", quality[index]->value,'\0');

//		gchar *command[] = {YDLPATH, farg, value, oarg, outname, carg,
//								(gchar *) url, NULL};
//		cstring *command = "";
//		sprintf( *command, "/usr/bin/youtube-dl -c -f %d -o %s", quality[index]->value, url);
//		gchar *command = "/usr/bin/youtube-dl -c -f 18 "
//				"-o \"/home/theimpaler/Videos/Alizee - J'ai Pas Vingt Ans - (Stars a Domicile - TF1).mp4\" "
//				"http://www.youtube.com/watch?v=rCwHOAI_OQk";
//		gchar *command[] = {YDLPATH, "-o", "/home/theimpaler/Videos/Alizee - J'ai Pas Vingt Ans - (Stars a Domicile - TF1).mp4",
//							"-c", "http://www.youtube.com/watch?v=rCwHOAI_OQk", NULL};
//		exit(0);
		gchar *command[] = {YDLPATH, oarg, outname, carg, url, farg, value, NULL};
		gint status;
		gint st_out;
		gint st_err;
		GError *err;
		printf("%s\n", *command);
		status = g_spawn_async_with_pipes(NULL,command,NULL, G_SPAWN_DO_NOT_REAP_CHILD,
									NULL, NULL, &pid, NULL, &st_out, &st_err, &err);
		if (!status) printf("Error occured\n");
//		g_child_watch_add(pid,(GChildWatchFunc) child_watch, NULL);

		GIOChannel *outchan = g_io_channel_unix_new(st_out);
//		GIOChannel *errchan = g_io_channel_unix_new(st_err);

		g_io_add_watch(outchan, G_IO_IN | G_IO_HUP, (GIOFunc) _output_watch, NULL);
//		g_io_add_watch (errchan, G_IO_IN | G_IO_HUP, (GIOFunc) _output_watch, NULL);
	//	g_io_add_watch (error_channel, G_IO_IN | G_IO_HUP, (GIOFunc) error_watch, ui);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void on_wMain_destroy (GtkObject *object, void * user_data)
{
    gtk_main_quit ();
}

void on_btnSearch_clicked (GtkWidget *widget, void * user_data) {
	puts("\nFunction on_btnSearch_clicked:");

	if (!strcmp((const char *)gtk_entry_get_text(gui->urlTxt),"")) puts("Empty URL provided");
	else puts((const char *)gtk_entry_get_text(gui->urlTxt));


	if (strcmp((const char *)gtk_entry_get_text(gui->urlTxt),"")) {
		int size,k;
		GtkListStore* list_store;
		GtkCellRenderer* renderer;
		GtkTreeIter iter;

		gtk_cell_layout_clear(GTK_CELL_LAYOUT(gui->qualBox));
		list_store = gtk_list_store_new ( 1 , GTK_TYPE_STRING);
		gtk_combo_box_set_model(GTK_COMBO_BOX(gui->qualBox), GTK_TREE_MODEL(list_store));
		renderer = gtk_cell_renderer_text_new();
		gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(gui->qualBox), renderer, 0x01);
		gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(gui->qualBox), renderer, "text", 0, NULL);

		gtk_widget_set_sensitive(widget,0x00);
		get_format((const char *)gtk_entry_get_text(gui->urlTxt), &size);
		printf("Got format. Size: %d\n", size);
//		cstring format[size];
		puts("Format info:");
		for (k=0; k<size; ++k) {
			cstring format = malloc(35*sizeof(char));
			sprintf(format,"%d: %s [%s]%c",quality[k]->value,quality[k]->format, quality[k]->size,'\0');
			GtkTreeIter * iter;
			gtk_list_store_append(list_store, &iter);
			gtk_list_store_set(list_store, &iter, 0, format,-1);
			free(format);
		}
	//    cstring filename = malloc(257*sizeof(char));
		get_title((const char *) gtk_entry_get_text(gui->urlTxt), &title);
		printf("%s.%s\n",title,quality[0]->format);
	//    sprintf(filename,"%s.%s", title, quality[0]->format);

		gtk_combo_box_set_active(GTK_COMBO_BOX(gui->qualBox),0);

		gtk_widget_set_sensitive(widget,0x01);
		//http://www.youtube.com/watch?v=SniIBm-PWUM
	}

}

void on_btnChoose_clicked (GtkWidget *widget, void *user_data) {
	GtkWidget* dialog;

	dialog = GTK_WIDGET(gtk_builder_get_object(builder, "dlgFile"));

	gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog),
							(const char *) gtk_entry_get_text(GTK_ENTRY(gui->outTxt)));

	if (gtk_dialog_run(GTK_DIALOG(dialog)) == 1) {
		char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gtk_entry_set_text(GTK_ENTRY(gui->outTxt),filename);
	}
	gtk_widget_hide(dialog);
//	gtk_widget_destroy(dialog);
}

void on_btnSave_clicked (GtkWidget *widget, void * user_data) {
	gtk_widget_set_sensitive(widget, 0x00);

	cstring url     = (cstring) gtk_entry_get_text(GTK_ENTRY(gui->urlTxt));
	cstring outname = (cstring) gtk_entry_get_text(GTK_ENTRY(gui->outTxt));
	int index = gtk_combo_box_get_active(GTK_COMBO_BOX(gui->qualBox));

//	get_file(url, outname, index);
	_get_with_gspawn(url,outname, index);

	gtk_widget_set_sensitive(widget, 0x01);
}

void on_btnExit_clicked (GtkWidget *widget, void * user_data) {
    gtk_main_quit ();
}

void on_qualBox_changed (GtkWidget *widget, void * user_data) {
	int index;
	index = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	cstring filename = malloc(128 * sizeof(char));
	sprintf(filename,"%s.%s", title, quality[index]->format);

	gtk_entry_set_text(GTK_ENTRY(gui->outTxt),filename);
	free(filename);
}
