SCRIPT_DIR=mumble-theme
export PATH=$PATH:$HOME/.local/bin # Add ~/.local/bin to path incase qtsass is only installed for user
pushd $SCRIPT_DIR/source
qtsass -o ../Lite.qss Lite.scss
popd
make-resource.py -base-dir $SCRIPT_DIR/ -find-files -output mumble-lite -style lite.qss 