#!/bin/bash
# =
#
# -
apt-get install libgd-gd2-perl
/usr/bin/perl -MCPAN -e 'install "PatchReader"'
/usr/bin/perl -MCPAN -e 'install "Date::Format"'
/usr/bin/perl -MCPAN -e 'install "Mail::Mailer"'
/usr/bin/perl -MCPAN -e 'install "MIME::Parser"'
/usr/bin/perl -MCPAN -e 'install "XML::Twig"'
/usr/bin/perl -MCPAN -e 'install "Image::Magick"'
/usr/bin/perl -MCPAN -e 'install "GD"'
/usr/bin/perl -MCPAN -e 'install "GD::Text"'
/usr/bin/perl -MCPAN -e 'install "GD::Text::Align"'
/usr/bin/perl -MCPAN -e 'install "Chart::Base"'
/usr/bin/perl -MCPAN -e 'install "GD::Graph"'
/usr/bin/perl -MCPAN -e 'install "AppConfig"'
/usr/bin/perl -MCPAN -e 'install "Template"'
