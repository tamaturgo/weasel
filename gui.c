#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "weasel.h"

static GtkWidget *stack;
static GtkWidget *alph_entry;
static GtkWidget *target_entry;
static GtkWidget *target_label;
static GtkWidget *seq_label;
static GtkWidget *gen_label;
static GtkWidget *back_button;
static GtkWidget *done_info;

static char *alphv;
static int alphc;
static char *target;
static char *seq;
static int len;
static char *copies[COPY_COUNT];
static int genc;

static void
set_matched_text(GtkLabel *label, char *text, int match[])
{
	int i;
	char *cur = (char*) calloc(2, sizeof(char)),
		 *formatted = (char*) calloc(1024, sizeof(char));

	strcat(formatted, "<big><tt>");

	for (i = 0; text[i] != '\0'; i++) {
		cur[0] = text[i];

		if (match[i]) {
			strcat(formatted, "<span color=\"green\">");
			strcat(formatted, cur);
			strcat(formatted, "</span>");
		} else {
			strcat(formatted, cur);
		}
	}

	strcat(formatted, "</tt></big>");

	gtk_label_set_markup(label, formatted);
	free(formatted);
}

static void
update_genc_view()
{
	char formatted[50];

	sprintf(formatted, "<small>Gen: %d</small>", ++genc);
	gtk_label_set_markup(GTK_LABEL(gen_label), formatted);
}

static void
back_to_form(GtkWidget *widget, gpointer data)
{
	gtk_widget_set_sensitive(back_button, FALSE);
	gtk_widget_hide(done_info);
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "form");
}

static gboolean
weasel_update(gpointer data)
{
	int i, val,
		best_val = 0, best_i = 0,
		*match;

	for (i = 0; i < COPY_COUNT; i++) {
		strcpy(copies[i], seq);
		modseq(copies + i, alphc, alphv, MUTATE_CHANCE);

		/* Compare the current copy */
		val = seqcmp(copies[i], target);

		if (val > best_val) {
			best_val = val;
			best_i = i;
		}
	}

	strcpy(seq, copies[best_i]);

	match = seqcmpa(seq, strlen(seq), target);

	set_matched_text(GTK_LABEL(target_label), target, match);
	set_matched_text(GTK_LABEL(seq_label), seq, match);

	update_genc_view();

	if (best_val == len) {
		gtk_widget_set_sensitive(back_button, TRUE);
		gtk_widget_show(done_info);
		return FALSE;
	}

	return TRUE;
}

static void
exec_weasel(GtkWidget *widget, gpointer data)
{
	int *match, i;

	alphv = (char*) gtk_editable_get_text(GTK_EDITABLE(alph_entry));
	alphc = strlen(alphv);

	target = (char*) gtk_editable_get_text(GTK_EDITABLE(target_entry));
	len = strlen(target);
	seq = genseq(len, alphc, alphv);

	for (i = 0; i < COPY_COUNT; i++)
		copies[i] = (char*) malloc((len + 1) * sizeof(char));

	match = seqcmpa(seq, strlen(seq), target);

	genc = 0;
	gtk_label_set_markup(GTK_LABEL(gen_label), "<small>Gen: 0</small>");
	
	set_matched_text(GTK_LABEL(target_label), target, match);
	set_matched_text(GTK_LABEL(seq_label), seq, match);

	gtk_stack_set_visible_child_name(GTK_STACK(stack), "exec");
	g_timeout_add_seconds(1, G_SOURCE_FUNC(weasel_update), NULL);
}

static void
create_form(GtkStack *stack)
{
	GtkWidget *box;
	GtkWidget *go_button;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
	gtk_stack_add_named(stack, box, "form");

	alph_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(alph_entry), "ABCDEFGHIJKLMNOPQRSTUVWXYZ ");
	gtk_box_append(GTK_BOX(box), alph_entry);

	target_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(target_entry), "METHINKS IT IS LIKE A WEASEL");
	gtk_box_append(GTK_BOX(box), target_entry);

	go_button = gtk_button_new_with_label("GO");
	g_signal_connect(go_button, "clicked", G_CALLBACK(exec_weasel), NULL);
	gtk_widget_set_halign(go_button, GTK_ALIGN_CENTER);
	gtk_box_append(GTK_BOX(box), go_button);
}

static void
create_exec(GtkStack *stack)
{
	GtkWidget *grid;
	GtkWidget *box;
	GtkWidget *done_label;

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	//gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
	gtk_stack_add_named(stack, box, "exec");

	seq_label = gtk_label_new("");
	gtk_box_append(GTK_BOX(box), seq_label);

	target_label = gtk_label_new("");
	gtk_box_append(GTK_BOX(box), target_label);

	gen_label = gtk_label_new("<small>Gen: 0</small>");
	gtk_label_set_use_markup(GTK_LABEL(gen_label), TRUE);
	gtk_box_append(GTK_BOX(box), gen_label);

	back_button = gtk_button_new_with_label("Back");
	g_signal_connect(back_button, "clicked", G_CALLBACK(back_to_form), NULL);
	gtk_widget_set_halign(back_button, GTK_ALIGN_CENTER);
	gtk_box_append(GTK_BOX(box), back_button);
	gtk_widget_set_sensitive(back_button, FALSE);

	/* Setup a "done feedback" */

	done_label = gtk_label_new("Done!");

	done_info = gtk_info_bar_new();
	gtk_info_bar_set_message_type(GTK_INFO_BAR(done_info), GTK_MESSAGE_WARNING);
	gtk_info_bar_add_child(GTK_INFO_BAR(done_info), done_label);
	gtk_info_bar_add_button(GTK_INFO_BAR(done_info), "OK", GTK_RESPONSE_OK);
	g_signal_connect(GTK_INFO_BAR(done_info), "response",
					 G_CALLBACK(gtk_widget_hide), NULL);
	gtk_box_append(GTK_BOX(box), done_info);
	gtk_widget_hide(done_info);
}

static void
activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *form_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Weasel");
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

	stack = gtk_stack_new();
	gtk_window_set_child(GTK_WINDOW(window), stack);

	create_form(GTK_STACK(stack));
	create_exec(GTK_STACK(stack));

	gtk_window_present(GTK_WINDOW(window));
}

int
main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	srand(time(NULL));

	app = gtk_application_new("weasel.gui", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
