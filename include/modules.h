/*****************************************************************************
 * modules.h : Module management functions.
 *****************************************************************************
 * Copyright (C) 2001 VideoLAN
 * $Id: modules.h,v 1.60 2002/08/15 12:11:15 sam Exp $
 *
 * Authors: Samuel Hocevar <sam@zoy.org>
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/*****************************************************************************
 * Module #defines.
 *****************************************************************************/

/* Number of tries before we unload an unused module */
#define MODULE_HIDE_DELAY 50
#define MODULE_SHORTCUT_MAX 10

/* The module handle type. */
#ifdef SYS_BEOS
typedef int     module_handle_t;
#else
typedef void *  module_handle_t;
#endif

/*****************************************************************************
 * module_bank_t: the module bank
 *****************************************************************************
 * This variable is accessed by any function using modules.
 *****************************************************************************/
struct module_bank_t
{
    VLC_COMMON_MEMBERS

    module_symbols_t symbols;
};

/*****************************************************************************
 * Module description structure
 *****************************************************************************/
struct module_t
{
    VLC_COMMON_MEMBERS

    /*
     * Variables set by the module to identify itself
     */
    char *psz_longname;                           /* Module descriptive name */

    /*
     * Variables set by the module to tell us what it can do
     */
    char *psz_program;        /* Program name which will activate the module */

    char *pp_shortcuts[ MODULE_SHORTCUT_MAX ];    /* Shortcuts to the module */

    char *psz_capability;                                      /* Capability */
    int   i_score;                              /* Score for each capability */
    u32   i_cpu;                                /* Required CPU capabilities */

    vlc_bool_t b_submodule;                          /* Is this a submodule? */

    /* Callbacks */
    int  ( * pf_activate )   ( vlc_object_t * );
    void ( * pf_deactivate ) ( vlc_object_t * );

    /*
     * Variables set by the module to store its config options
     */
    module_config_t *p_config;             /* Module configuration structure */
    unsigned int     i_config_items;        /* number of configuration items */
    unsigned int     i_bool_items;            /* number of bool config items */

    /*
     * Variables used internally by the module manager
     */
    /* Plugin-specific stuff */
    module_handle_t     handle;                             /* Unique handle */
    char *              psz_filename;                     /* Module filename */

    vlc_bool_t          b_builtin;  /* Set to true if the module is built in */

    /*
     * Symbol table we send to the module so that it can access vlc symbols
     */
    module_symbols_t *p_symbols;
};

/*****************************************************************************
 * Exported functions.
 *****************************************************************************/
#define module_InitBank(a)     __module_InitBank(VLC_OBJECT(a))
void  __module_InitBank        ( vlc_object_t * );
#define module_LoadMain(a)     __module_LoadMain(VLC_OBJECT(a))
void  __module_LoadMain        ( vlc_object_t * );
#define module_LoadBuiltins(a) __module_LoadBuiltins(VLC_OBJECT(a))
void  __module_LoadBuiltins    ( vlc_object_t * );
#define module_LoadPlugins(a)  __module_LoadPlugins(VLC_OBJECT(a))
void  __module_LoadPlugins     ( vlc_object_t * );
#define module_EndBank(a)      __module_EndBank(VLC_OBJECT(a))
void  __module_EndBank         ( vlc_object_t * );
#define module_ResetBank(a)    __module_ResetBank(VLC_OBJECT(a))
void  __module_ResetBank       ( vlc_object_t * );

#define module_Need(a,b,c) __module_Need(VLC_OBJECT(a),b,c)
VLC_EXPORT( module_t *, __module_Need, ( vlc_object_t *, const char *, const char * ) );
#define module_Unneed(a,b) __module_Unneed(VLC_OBJECT(a),b)
VLC_EXPORT( void, __module_Unneed, ( vlc_object_t *, module_t * ) );

