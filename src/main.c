/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Adam M. Bumpus 2013 <adam@bump.us>
 * 
 */

#include <config.h>
#include <gtk/gtk.h>
#include "gtkroku.h"


#include <glib/gi18n.h>


int
main (int argc, char *argv[])
{
	Gtkroku *app;
	int status;


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
  app = gtkroku_new ();
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
