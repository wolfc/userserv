#include <string.h>

#include <accountopt.h>
#include <debug.h>
#include <plugin.h>
#include <pluginpref.h>
#include <prefs.h>
#include <prpl.h>
#include <version.h>

#define PLUGIN_ID   "userserv"
#define VERSION     "0.2"

static PurplePluginProtocolInfo *irc_info = NULL;

static void
signed_on(PurpleConnection *connection)
{
    PurpleAccount *account;
    const char *username;
    const char *password;
    gchar **usernameTokens;
    gchar *msg;

    account = purple_connection_get_account(connection);

    if(strcmp("prpl-irc", purple_account_get_protocol_id(account)))
        return;

    password = purple_account_get_password(account);

    if(password == NULL)
        return;

    username = purple_account_get_username(account);

    usernameTokens = g_strsplit(username, "@", 2);

    if(purple_account_get_bool(account, PLUGIN_ID "_userserv_auth", 0))
    {
        msg = g_strdup_printf("PRIVMSG USERSERV :login %s %s\r\n", usernameTokens[0], password);
        purple_debug_info("userserv", "sending %s\n", msg);
        irc_info->send_raw(connection, msg, strlen(msg));
        g_free(msg);
    }

    g_strfreev(usernameTokens);
}

static gboolean
plugin_load(PurplePlugin *plugin)
{
    PurplePlugin *prpl;
    PurpleAccountOption *option;
    void *gc_handle;

    prpl = purple_find_prpl("prpl-irc");
    if(!prpl)
        return FALSE;

    irc_info = PURPLE_PLUGIN_PROTOCOL_INFO(prpl);

    gc_handle = purple_connections_get_handle();

    // add configuration options if needed
    option = purple_account_option_bool_new("Enable USERSERV Auth", PLUGIN_ID "_userserv_auth", 0);
    irc_info->protocol_options = g_list_append(irc_info->protocol_options, option);
    /*
    option = purple_account_option_string_new("userserv auth name", PLUGIN_ID "_usauthnick", "");
    irc_info->protocol_options = g_list_append(irc_info->protocol_options, option);
    option = purple_account_option_string_new("userserv password", PLUGIN_ID "_usnickpassword", "");
    purple_account_option_string_set_masked(option, TRUE);
    irc_info->protocol_options = g_list_append(irc_info->protocol_options, option);
    */

    // register callbacks
    purple_signal_connect(gc_handle, "signed-on", plugin,
        G_CALLBACK(signed_on), NULL);

    return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin)
{
    PurplePlugin *prpl;
    PurpleAccountOption *option;
    GList *list;

    prpl = purple_find_prpl("prpl-irc");
    if(!prpl)
        return FALSE;

    irc_info = PURPLE_PLUGIN_PROTOCOL_INFO(prpl);

    // remove configuration options
    list = irc_info->protocol_options;
    while (NULL != list)
    {
        option = (PurpleAccountOption *) list->data;
        if (g_str_has_prefix(purple_account_option_get_setting(option), PLUGIN_ID "_"))
        {
            GList *tmplist = list;
            // Remove from list.
            if (tmplist->prev)
                tmplist->prev->next = tmplist->next;
            if (tmplist->next)
                tmplist->next->prev = tmplist->prev;

            // free allocations
            purple_account_option_destroy(option);
            g_list_free_1(tmplist);

            list = g_list_next(list);
        }
        else
        {
            list = g_list_next(list);
        }
    }

    return TRUE;
}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL, // ui_requirement
    0, // flags
    NULL, // dependencies
    PURPLE_PRIORITY_DEFAULT,

    PLUGIN_ID,
    "userserv", // name
    VERSION,
    "Makes you logon using userserv.", // summary
    "description",
    "Carlo de Wolf <carlo@nerdnet.nl>",
    NULL, // homepage

    plugin_load,
    plugin_unload,
    NULL, // destroy

    NULL, // ui_info
    NULL, // extra_info
    NULL, // prefs_info

    NULL, // actions

    NULL, // reserved1
    NULL, // reserved2
    NULL, // reserved3
    NULL // reserved4
};

static void
init_plugin(PurplePlugin *plugin)
{
}

PURPLE_INIT_PLUGIN(userserv, init_plugin, info)
