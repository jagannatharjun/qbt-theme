@echo off

set ThemeDir=QDarkStyleSheet\qdarkstyle
set IconsDir=icons\nowshed

python make-resource.py -base-dir %ThemeDir% ^
                        -config dark-config.json ^
                        -dir-prefix qss_icons ^
                        -output darkstylesheet ^
                        -icons-dir %IconsDir% ^
                        -style style.qss rc\* svg\*

