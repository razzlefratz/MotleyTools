/*====================================================================*
 *
 *
 *
 *--------------------------------------------------------------------*/

int main (int argc, char **argv) 

{
	gtk_set_locale ();
	gtk_init (&argc, &argv);
	mainwin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	...gtk_widget_showall (mainwin);
	gtk_main ();
	gtk_exit (0);
}

