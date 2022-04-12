
SCRIPT_DIR=mumble-theme
export PATH=$PATH:$HOME/.local/bin # Add ~/.local/bin to path incase qtsass is only installed for user
pushd $SCRIPT_DIR/source
qtsass -o ../Dark.qss Dark.scss
popd
rm -rf mumble-icons
mkdir mumble-icons
python fill-icons.py nowshed #4B9CD3 mumble-icons
# for /r icons/nowshed/ %%i in (*.svg) do powershell -Command "(gc %%~dpnxi) -replace '#4285f4', '#6a1b9a' | Out-File -encoding ASCII mumble-icons/%%~nxi"
python make-resource.py -base-dir $SCRIPT_DIR/ -find-files -config dark-config.json -icons-dir mumble-icons -output mumble-dark-nowshed-recolored -style dark.qss 
rm -rf mumble-icons
python make-resource.py -base-dir $SCRIPT_DIR/ -find-files -config dark-config.json -icons-dir icons/nowshed -output mumble-dark-nowshed -style dark.qss 
