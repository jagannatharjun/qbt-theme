@echo off

set ThemeDir=mumble-theme
set IconsDir=mumble-icons
set ThemeName=mumble-dark

pip install -r requirements.txt

pushd %ThemeDir%\source
    qtsass -o ..\Dark.qss Dark.scss
popd

python make-resource.py -base-dir %ThemeDir% ^
                        -find-files ^
                        -config dark-config.json ^
                        -output %ThemeName% ^
                        -icons-dir %IconsDir% ^
                        -style dark.qss 

