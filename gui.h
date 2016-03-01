#include <glib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define YDLPATH "/usr/bin/youtube-dl"
//#define GUIPATH "/usr/share/gtk-youtube-dl/ui/gtkview.builder"
#define GUIPATH "gtkview.builder"
//#define REGEX "^.*\][ ]*([0-9.%]*) of ([0-9.]+)([Mk]) " \
//              "at +([0-9.]{2})([Mk]/s) ETA 0?([0-9]{1,2}):0?([0-9]{1,2}).*$"
#define REGEX "^.*\][ ]*([0-9.%]*) of ([0-9.]*)([MK]).* at ([0-9.]*)([MKiB]*).* ETA ([0-9:]*).*$"

typedef char * cstring;
typedef struct {int value;
				  cstring format;
				  cstring size;} QualiT;
typedef struct {GtkWidget *window;
				  GtkComboBox *qualBox;
				  GtkEntry *outTxt;
				  GtkEntry *urlTxt;
				  GtkTextView	*txtResults;
				  GtkTextBuffer *txtBuffer;} GuiT;


void gui_init(int *, char ***);
void gui_run();
void on_wMain_destroy (GtkObject *, gpointer);
void on_btnSearch_clicked (GtkWidget *, gpointer);
void on_btnChoose_clicked (GtkWidget *, gpointer);
void on_btnSave_clicked (GtkWidget *, gpointer);
void on_btnExit_clicked (GtkWidget *, gpointer);
void on_qualBox_changed (GtkWidget *, gpointer);
