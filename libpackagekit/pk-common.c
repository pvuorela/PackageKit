/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif /* HAVE_UNISTD_H */

#include <glib/gi18n.h>

#include "pk-debug.h"
#include "pk-common.h"

/**
 * pk_filter_check_part:
 **/
gboolean
pk_filter_check_part (const gchar *filter)
{
	if (filter == NULL) {
		return FALSE;
	}
	if (strlen (filter) == 0) {
		return FALSE;
	}
	if (strcmp (filter, "none") == 0) {
		return TRUE;
	}
	if (strcmp (filter, "installed") == 0) {
		return TRUE;
	}
	if (strcmp (filter, "~installed") == 0) {
		return TRUE;
	}
	if (strcmp (filter, "devel") == 0) {
		return TRUE;
	}
	if (strcmp (filter, "~devel") == 0) {
		return TRUE;
	}
	if (strcmp (filter, "gui") == 0) {
		return TRUE;
	}
	if (strcmp (filter, "~gui") == 0) {
		return TRUE;
	}
	return FALSE;
}

/**
 * pk_filter_check:
 **/
gboolean
pk_filter_check (const gchar *filter)
{
	gchar **sections;
	guint i;
	guint length;
	gboolean ret;

	if (filter == NULL) {
		pk_warning ("filter null");
		return FALSE;
	}
	if (strlen (filter) == 0) {
		pk_warning ("filter zero length");
		return FALSE;
	}

	/* split by delimeter ';' */
	sections = g_strsplit (filter, ";", 0);
	length = g_strv_length (sections);
	ret = FALSE;
	for (i=0; i<length; i++) {
		/* only one wrong part is enough to fail the filter */
		if (strlen (sections[i]) == 0) {
			goto out;
		}
		if (pk_filter_check_part (sections[i]) == FALSE) {
			goto out;
		}
	}
	ret = TRUE;
out:
	g_strfreev (sections);
	return ret;
}

/**
 * pk_string_id_split:
 *
 * You need to use g_strfreev on the returned value
 **/
gchar **
pk_string_id_split (const gchar *id, guint parts)
{
	gchar **sections = NULL;

	if (id == NULL) {
		pk_warning ("ident is null!");
		goto out;
	}

	/* split by delimeter ';' */
	sections = g_strsplit (id, ";", 0);
	if (g_strv_length (sections) != parts) {
		pk_warning ("ident '%s' is invalid (sections=%d)", id, g_strv_length (sections));
		goto out;
	}

	/* name has to be valid */
	if (strlen (sections[0]) == 0) {
		pk_warning ("ident first section is empty");
		goto out;
	}

	/* all okay, phew.. */
	return sections;

out:
	/* free sections and return NULL */
	if (sections != NULL) {
		g_strfreev (sections);
	}
	return NULL;
}

/**
 * pk_string_id_strcmp:
 **/
gboolean
pk_string_id_strcmp (const gchar *id1, const gchar *id2)
{
	if (id1 == NULL || id2 == NULL) {
		pk_warning ("string id compare invalid '%s' and '%s'", id1, id2);
		return FALSE;
	}
	return (strcmp (id1, id2) == 0);
}

/**
 * pk_string_id_equal:
 * only compare first sections, not all the data
 **/
gboolean
pk_string_id_equal (const gchar *id1, const gchar *id2, guint parts, guint compare)
{
	gchar **sections1;
	gchar **sections2;
	gboolean ret = FALSE;
	guint i;

	if (id1 == NULL || id2 == NULL) {
		pk_warning ("package id compare invalid '%s' and '%s'", id1, id2);
		return FALSE;
	}
	if (compare > parts) {
		pk_warning ("compare %i > parts %i", compare, parts);
		return FALSE;
	}
	if (compare == parts) {
		pk_debug ("optimise to strcmp");
		return pk_string_id_strcmp (id1, id2);
	}

	/* split, NULL will be returned if error */
	sections1 = pk_string_id_split (id1, parts);
	sections2 = pk_string_id_split (id2, parts);

	/* check we split okay */
	if (sections1 == NULL) {
		pk_warning ("string id compare sections1 invalid '%s'", id1);
		goto out;
	}
	if (sections2 == NULL) {
		pk_warning ("string id compare sections2 invalid '%s'", id2);
		goto out;
	}

	/* only compare preceeding sections */
	for (i=0; i<compare; i++) {
		if (strcmp (sections1[i], sections2[i]) != 0) {
			goto out;
		}
	}
	ret = TRUE;

out:
	g_strfreev (sections1);
	g_strfreev (sections2);
	return ret;
}

/***************************************************************************
 ***                          MAKE CHECK TESTS                           ***
 ***************************************************************************/
#ifdef PK_BUILD_TESTS
#include <libselftest.h>

void
libst_common (LibSelfTest *test)
{
	gboolean ret;
	gchar **array;
	const gchar *temp;

	if (libst_start (test, "PkCommon", CLASS_AUTO) == FALSE) {
		return;
	}

	/************************************************************
	 ****************          string_id         ****************
	 ************************************************************/
	libst_title (test, "test pass 1");
	array = pk_string_id_split ("foo", 1);
	if (array != NULL) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}
	g_strfreev (array);

	/************************************************************/
	libst_title (test, "test pass 2");
	array = pk_string_id_split ("foo;moo", 2);
	if (array != NULL) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}
	g_strfreev (array);

	/************************************************************/
	libst_title (test, "test pass 3");
	array = pk_string_id_split ("foo;moo;bar", 3);
	if (array != NULL) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}
	g_strfreev (array);

	/************************************************************/
	libst_title (test, "test fail under");
	array = pk_string_id_split ("foo;moo", 1);
	if (array == NULL) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	/************************************************************/
	libst_title (test, "test fail over");
	array = pk_string_id_split ("foo;moo", 3);
	if (array == NULL) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	/************************************************************/
	libst_title (test, "test fail missing first");
	array = pk_string_id_split (";moo", 2);
	if (array == NULL) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	/************************************************************/
	libst_title (test, "id strcmp pass");
	ret = pk_string_id_strcmp ("moo;0.0.1;i386;fedora", "moo;0.0.1;i386;fedora");
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	/************************************************************/
	libst_title (test, "id strcmp fail");
	ret = pk_string_id_strcmp ("moo;0.0.1;i386;fedora", "moo;0.0.2;i386;fedora");
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal pass (same)");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "moo;0.0.1;i386;fedora", 4, 3);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal pass (parts==match)");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "moo;0.0.1;i386;fedora", 4, 4);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal pass (different)");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "moo;0.0.1;i386;data", 4, 3);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal fail1");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "moo;0.0.2;x64;fedora", 4, 3);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal fail2");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "gnome;0.0.2;i386;fedora", 4, 3);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal fail3");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "moo;0.0.3;i386;fedora", 4, 3);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	libst_title (test, "id equal fail (match too high)");
	ret = pk_string_id_equal ("moo;0.0.1;i386;fedora", "moo;0.0.3;i386;fedora", 4, 5);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, NULL);
	}

	/************************************************************
	 ****************          FILTERS         ******************
	 ************************************************************/
	temp = NULL;
	libst_title (test, "test a fail filter (null)");
	ret = pk_filter_check (temp);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "passed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "";
	libst_title (test, "test a fail filter ()");
	ret = pk_filter_check (temp);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "passed the filter '%s'", temp);
	}

	/************************************************************/
	temp = ";";
	libst_title (test, "test a fail filter (;)");
	ret = pk_filter_check (temp);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "passed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "moo";
	libst_title (test, "test a fail filter (invalid)");
	ret = pk_filter_check (temp);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "passed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "moo;foo";
	libst_title (test, "test a fail filter (invalid, multiple)");
	ret = pk_filter_check (temp);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "passed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "gui;;";
	libst_title (test, "test a fail filter (valid then zero length)");
	ret = pk_filter_check (temp);
	if (ret == FALSE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "passed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "none";
	libst_title (test, "test a pass filter (none)");
	ret = pk_filter_check (temp);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "failed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "gui";
	libst_title (test, "test a pass filter (single)");
	ret = pk_filter_check (temp);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "failed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "devel;~gui";
	libst_title (test, "test a pass filter (multiple)");
	ret = pk_filter_check (temp);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "failed the filter '%s'", temp);
	}

	/************************************************************/
	temp = "~gui;~installed";
	libst_title (test, "test a pass filter (multiple2)");
	ret = pk_filter_check (temp);
	if (ret == TRUE) {
		libst_success (test, NULL);
	} else {
		libst_failed (test, "failed the filter '%s'", temp);
	}

	libst_end (test);
}
#endif

