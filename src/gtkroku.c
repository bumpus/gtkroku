/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtkroku.c
 * Copyright (C) 2013 Adam M. Bumpus <adam@bump.us>
 * 
 * gtkRoku is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtkRoku is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "gtkroku.h"

#include <glib/gi18n.h>

/*defines for the valid buttons on a roku remote*/
#define REMOTE_Home "Home"
#define REMOTE_Rev "Rev"
#define REMOTE_Fwd "Fwd"
#define REMOTE_Play "Play"
#define REMOTE_Select "Select"
#define REMOTE_Left "Left"
#define REMOTE_Right "Right"
#define REMOTE_Down "Down"
#define REMOTE_Up "Up"
#define REMOTE_Back "Back"
#define REMOTE_InstantReplay "InstantReplay"
#define REMOTE_Info "Info"

/*for Development purposes, hardcode the address for my
 * family room roku player. I'll implement the automatic detection
 * and a drop down selector for if I find more than one later*/

/*TODO: Find and replace all the ROKU_ADDRESS items once detection is implemented*/
#define ROKU_ADDRESS "192.168.0.16"
#define ROKU_ADDRESS_PORT 8060


/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/gtkroku.ui" */
#define UI_FILE "src/gtkroku.ui"
#define TOP_WINDOW "gtkRokuWindow"


G_DEFINE_TYPE (Gtkroku, gtkroku, GTK_TYPE_APPLICATION);


/* Define the private structure in the .c file */
#define GTKROKU_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GTKROKU_TYPE_APPLICATION, GtkrokuPrivate))

struct _GtkrokuPrivate
{
	/* ANJUTA: Widgets declaration for gtkroku.ui - DO NOT REMOVE */
};


/* Create a new window loading a file */
static void
gtkroku_new_window (GApplication *app,
                           GFile        *file)
{
	GtkWidget *window;

	GtkBuilder *builder;
	GError* error = NULL;

	GtkrokuPrivate *priv = GTKROKU_GET_PRIVATE(app);

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, app);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }

	
	/* ANJUTA: Widgets initialization for gtkroku.ui - DO NOT REMOVE */

	g_object_unref (builder);
	
	
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	if (file != NULL)
	{
		/* TODO: Add code here to open the file in the new window */
	}
	gtk_widget_show_all (GTK_WIDGET (window));
}


/* GApplication implementation */
static void
gtkroku_activate (GApplication *application)
{
  gtkroku_new_window (application, NULL);
}

static void
gtkroku_open (GApplication  *application,
                     GFile        **files,
                     gint           n_files,
                     const gchar   *hint)
{
  gint i;

  for (i = 0; i < n_files; i++)
    gtkroku_new_window (application, files[i]);
}

static void
gtkroku_init (Gtkroku *object)
{

}

static void
gtkroku_finalize (GObject *object)
{

	G_OBJECT_CLASS (gtkroku_parent_class)->finalize (object);
}

static void
gtkroku_class_init (GtkrokuClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = gtkroku_activate;
	G_APPLICATION_CLASS (klass)->open = gtkroku_open;

	g_type_class_add_private (klass, sizeof (GtkrokuPrivate));

	G_OBJECT_CLASS (klass)->finalize = gtkroku_finalize;
}

Gtkroku *
gtkroku_new (void)
{
	g_type_init ();

	return g_object_new (gtkroku_get_type (),
	                     "application-id", "org.gnome.gtkroku",
	                     "flags", G_APPLICATION_HANDLES_OPEN,
	                     NULL);
}

const gchar* get_button_type(GtkButton *button, gpointer user_data)
{
	const gchar* text = gtk_button_get_label (button);
	if (g_str_equal (text, _("Back")))
		return REMOTE_Back;

	if (g_str_equal (text, _("Home")))
		return REMOTE_Home;

	if (g_str_equal (text, _(">>")))
		return REMOTE_Fwd;

	if (g_str_equal (text, ("<<")))
		return REMOTE_Rev;

	if (g_str_equal (text, _("||>")))
		return REMOTE_Play;

	if (g_str_equal (text, _("OK")))
		return REMOTE_Select;

	if (g_str_equal (text, _("Left")))
		return REMOTE_Left;

	if (g_str_equal (text, _("Right")))
		return REMOTE_Right;

	if (g_str_equal (text, _("Down")))
		return REMOTE_Down;

	if (g_str_equal (text, _("Up")))
		return REMOTE_Up;

	if (g_str_equal (text, _("IR")))
		return REMOTE_InstantReplay;

	if (g_str_equal (text, _("*")))
		return REMOTE_Info;

	/*All Else failing, return a null terminator*/
	return '\0';
}

int
http_post_command(gchar* command)
{
	printf("Sending %s", command);
}

void
on_remote_button_press (GtkButton *button, gpointer user_data)
{
	const gchar* command = get_button_type(button, user_data);
	char http_request[256] = "POST /keydown/";
	strcat(http_request, command);
	strcat(http_request, " HTTP/1.1\r\n\r\n");
	http_post_command(http_request);
}

void
on_remote_button_release (GtkButton *button, gpointer user_data)
{
	const gchar* command = get_button_type(button, user_data);
	char http_request[256] = "POST /keyup/";
	strcat(http_request, command);
	strcat(http_request, " HTTP/1.1\r\n\r\n");
	http_post_command(http_request);
}

