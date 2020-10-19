set SCRIPT_DIR=BreezeStyleSheets
set ICONS_DIR=icons/nowshed
make-resource.py -base-dir %SCRIPT_DIR%\ -find-files -output breeze-dark  -config dark-config.json -icons-dir %ICONS_DIR% -style dark.qss 