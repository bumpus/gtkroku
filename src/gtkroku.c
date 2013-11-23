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

void
on_remote_button_press (GtkButton *button, gpointer user_data)
{
	printf("Button Pressed\n", user_data.);
}


void
on_remote_button_release (GtkButton *button, gpointer user_data)
{
	printf("Button Released\n");
}


