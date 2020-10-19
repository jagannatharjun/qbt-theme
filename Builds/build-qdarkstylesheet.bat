set SCRIPT_DIR=QDarkStyleSheet\qdarkstyle
set ICONS_DIR=icons/nowshed
make-resource.py -base-dir %SCRIPT_DIR%\  -config dark-config.json -dir-prefix qss_icons -output darkstylesheet -icons-dir %ICONS_DIR% -style style.qss rc\* svg\*