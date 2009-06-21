/*	$calcurse: vars.c,v 1.15 2009/06/21 18:16:23 culot Exp $	*/

/*
 * Calcurse - text-based organizer
 * Copyright (c) 2004-2008 Frederic Culot
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
 * Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Send your feedback or comments to : calcurse@culot.org
 * Calcurse home page : http://culot.org/calcurse
 *
 */

#include <stdlib.h>
#include <string.h>

#include "i18n.h"
#include "calendar.h"
#include "custom.h"
#include "wins.h"
#include "keys.h"
#include "mem.h"
#include "vars.h"

/*
 * variables to store window size
 */
int col = 0, row = 0;

/* variable to tell if the terminal supports color */
bool colorize = false;

/*
 * To tell if curses interface was launched already or not (in that case
 * calcurse is running in command-line mode).
 * This is useful to konw how to display messages on the screen.
 */
ui_mode_e ui_mode = UI_CMDLINE;

/*
 * variables to store calendar names
 */
int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
char *monthnames[12] = {
  N_("January"),
  N_("February"),
  N_("March"),
  N_("April"),
  N_("May"),
  N_("June"),
  N_("July"),
  N_("August"),
  N_("September"),
  N_("October"),
  N_("November"),
  N_("December")
};

char *daynames[8] = {
  N_("Sun"),
  N_("Mon"),
  N_("Tue"),
  N_("Wed"),
  N_("Thu"),
  N_("Fri"),
  N_("Sat"),
  N_("Sun")
};

/* 
 * variables to store data path names, which are initialized in
 * io_init() 
 */
char path_dir[] = "";
char path_todo[] = "";
char path_apts[] = "";
char path_conf[] = "";
char path_notes[] = "";
char path_keys[] = "";
char path_lock[] = "";

/* Variable to handle pads. */
struct pad_s apad;

/* Variable to store notify-bar settings. */
struct nbar_s nbar;

/*
 * Variables init 
 */
void
vars_init (conf_t *conf)
{
  char *PATH_VI = "/usr/bin/vi";
  char *PATH_LESS = "/usr/bin/less";
  char *ed, *pg;

  /* Variables for user configuration */
  conf->confirm_quit = true;
  conf->confirm_delete = true;
  conf->auto_save = true;
  conf->periodic_save = 0;
  conf->skip_system_dialogs = false;
  conf->skip_progress_bar = false;
  (void)strncpy (conf->output_datefmt, "%D", 3);
  conf->input_datefmt = 1;

  /* Default external editor and pager */
  ed = getenv ("VISUAL");
  if (ed == NULL || ed[0] == '\0')
    ed = getenv ("EDITOR");
  if (ed == NULL || ed[0] == '\0')
    ed = PATH_VI;
  conf->editor = ed;

  pg = getenv ("PAGER");
  if (pg == NULL || pg[0] == '\0')
    pg = PATH_LESS;
  conf->pager = pg;

  wins_set_layout (1);

  calendar_set_first_day_of_week (MONDAY);

  /* Pad structure to scroll text inside the appointment panel */
  apad.length = 1;
  apad.first_onscreen = 0;

  /* Attribute definitions for color and non-color terminals */
  custom_init_attr ();

  /* Start at the current date */
  calendar_init_slctd_day ();
}
