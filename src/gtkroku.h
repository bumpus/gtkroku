/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gtkroku.h
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

#ifndef _GTKROKU_
#define _GTKROKU_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTKROKU_TYPE_APPLICATION             (gtkroku_get_type ())
#define GTKROKU_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTKROKU_TYPE_APPLICATION, Gtkroku))
#define GTKROKU_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GTKROKU_TYPE_APPLICATION, GtkrokuClass))
#define GTKROKU_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTKROKU_TYPE_APPLICATION))
#define GTKROKU_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GTKROKU_TYPE_APPLICATION))
#define GTKROKU_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GTKROKU_TYPE_APPLICATION, GtkrokuClass))

typedef struct _GtkrokuClass GtkrokuClass;
typedef struct _Gtkroku Gtkroku;
typedef struct _GtkrokuPrivate GtkrokuPrivate;

struct _GtkrokuClass
{
	GtkApplicationClass parent_class;
};

struct _Gtkroku
{
	GtkApplication parent_instance;

	GtkrokuPrivate *priv;

};

GType gtkroku_get_type (void) G_GNUC_CONST;
Gtkroku *gtkroku_new (void);

/* Callbacks */

G_END_DECLS

#endif /* _APPLICATION_H_ */
