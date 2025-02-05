@echo off

set ThemeDir=BreezeStyleSheets
set IconsDir=icons/nowshed
set ThemeName=breeze-dark

python make-resource.py -base-dir %ThemeDir% ^
                        -find-files ^
                        -output %ThemeName% ^
                        -config dark-config.json ^
                        -icons-dir %IconsDir% ^
                        -style dark.qss 
