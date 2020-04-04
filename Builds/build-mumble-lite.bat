set SCRIPT_DIR=mumble-theme
set PATH=%PATH%;C:\Users\Prince\Downloads\Compressed\qtsass_0.2.2_win64;
pushd %SCRIPT_DIR%\source
qtsass -o ../Lite.qss Lite.scss
popd
make-resource.py -base-dir %SCRIPT_DIR%\ -find-files -output mumble-lite -style lite.qss 