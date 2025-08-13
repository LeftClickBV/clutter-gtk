#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>
#include <webkit2/webkit2.h>

#define WINWIDTH   400
#define WINHEIGHT  400

static ClutterActor *
create_gtk_actor (void)
{
  ClutterActor  *gtk_actor;
  GtkWidget     *bin, *web_view;

  gtk_actor = gtk_clutter_actor_new ();

  web_view = GTK_WIDGET (webkit_web_view_new ());
  webkit_web_view_load_uri (WEBKIT_WEB_VIEW (web_view), "https://roomguide.info");

  bin = gtk_clutter_actor_get_widget (GTK_CLUTTER_ACTOR (gtk_actor));
  gtk_container_add (GTK_CONTAINER (bin), web_view);

  gtk_widget_show_all (bin);

  return gtk_actor;
}


int
main (int argc, char *argv[])
{
  ClutterActor    *stage, *actor;
  ClutterColor     stage_color = { 0x61, 0x64, 0x8c, 0xff };
  GtkWidget       *window, *clutter;
  GtkWidget       *vbox;

  if (gtk_clutter_init_with_args (&argc, &argv, NULL, NULL, NULL, NULL) != CLUTTER_INIT_SUCCESS)
    g_error ("Unable to initialize GtkClutter");

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  gtk_container_add (GTK_CONTAINER (window), vbox);

  clutter = gtk_clutter_embed_new ();
  gtk_box_pack_start (GTK_BOX (vbox), clutter, TRUE, TRUE, 0);

  stage = gtk_clutter_embed_get_stage (GTK_CLUTTER_EMBED (clutter));
  clutter_actor_set_background_color (stage, &stage_color);

  actor = create_gtk_actor();
  clutter_actor_add_child(stage, actor);

  gtk_widget_show_all (window);

  gtk_main();

  return 0;
}
