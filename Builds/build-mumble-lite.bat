@echo off

set ThemeDir=mumble-theme
set ThemeName=mumble-lite

pushd %ThemeDir%\source
    qtsass -o ../Lite.qss Lite.scss
popd

python make-resource.py -base-dir %ThemeDir% ^
                        -find-files ^
                        -output %ThemeName% ^
                        -style lite.qss 

